#ifndef MAP_TREE_SLICE_TRAIT_H_
#define MAP_TREE_SLICE_TRAIT_H_

#include "../../Interface/slice_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Details/type_list.hpp"
#include "../../Details/type_def.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {


	template <typename T_content, typename ...T_indexes, typename T_trait_list>
	struct slice_trait<n_indexed<T_content, map_tree_storage, indexes<T_indexes...>, T_trait_list>> {

		template <Size_t Dim>
		using SliceType =
		        std::conditional_t<
		                sizeof...(T_indexes) == 1 && Dim == 0,
		                T_content,
		                n_indexed<T_content, map_tree_storage, type_list::remove_nth_t<Dim, indexes<T_indexes...>>, T_trait_list>>;

		template <Size_t Dim, typename TIndexSelect>
		auto slice(const TIndexSelect& index_select)
		{
			SliceType<Dim> ret;

			if (helper<Dim>(ret, index_select))
				return ret;
			else
				throw empty_slice_exception{};
		}

		template <Size_t Dim, typename TIndexSelect>
		bool helper(SliceType<Dim>& ret, const TIndexSelect& index_select) const
		{
			const auto& storage = self()->_storage;

			if constexpr (Dim == 0) {
				// Slice is done in this stage (the first index)
				auto it = storage.find(index_select);

				if (it != storage.end()) {
					ret = it->second;
		 			return true;
				}
				else {
					return false;
				}
			}
			else {
				bool slice_was_not_empty = false;
				typename decltype(self()->_storage)::mapped_type::template SliceType<Dim - 1> branch_slice;

				for (const auto& pair : storage) {
					if (pair.second.template helper<Dim - 1>(branch_slice, index_select)) {
						ret._storage[pair.first] = branch_slice;
						slice_was_not_empty = true;
					}
				}
				return slice_was_not_empty;
			}
		}

		DEFINE_SELF
	};

}

#endif