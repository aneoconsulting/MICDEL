#ifndef MAP_TREE_SIZE_TRAIT_H_
#define MAP_TREE_SIZE_TRAIT_H_

#include "../../Details/type_def.hpp"
#include "../../Interface/size_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct size_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		auto size() const noexcept
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {
				return self()->_storage.size();
			}
			else {
				Size_t res = 0;

				for (auto& elmt : self()->_storage)
					res += elmt.second.size();

				return res;
			}
		}

	private:
		DEFINE_SELF
	};
}

#endif