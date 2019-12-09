#ifndef MAP_TREE_APPLY_TRAIT_H_
#define MAP_TREE_APPLY_TRAIT_H_

#include "../../Interface/apply_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {


	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct apply_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		template <typename T_func>
		void apply(T_func function)
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {
				// Call the function T_content 
				for (auto& elmt : self()->_storage)
					function(elmt.second);
			}
			else {
				// Recursively use child apply method
				for (auto& elmt : self()->_storage)
					elmt.second.apply(function);
			}
		}

	private:
		DEFINE_SELF
	};

} /* namespace NIndexedContainer */

#endif 