#ifndef MAP_TREE_FOREACH_TRAIT_H_
#define MAP_TREE_FOREACH_TRAIT_H_

#include "../../Interface/foreach_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_first_index,typename ...T_next_indexes, typename T_trait_list>
	struct foreach_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		template <typename T_func>
		void foreach(T_func func)
		{
			if constexpr (sizeof...(T_next_indexes)) {
				for (auto& elmt : self()->_storage)
					function(elmt.first, elmt.second);
			}
			else {
				for (auto& elmt : self()->_storage)
					elmt.second.foreach(
						[&](const T_next_indexes& ...indexes, T_content& value)
							{func(elmt.first, indexes..., value); });
			}
		}

	private:
		DEFINE_SELF
	};
} /* namepsace NIndexedContainer */

#endif