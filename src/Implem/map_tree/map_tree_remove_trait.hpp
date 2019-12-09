#ifndef MAP_TREE_REMOVE_TRAIT_H_
#define MAP_TREE_REMOVE_TRAIT_H_

#include "../../Interface/remove_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct remove_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		void remove(const T_first_index& first_index, const T_next_indexes& ...next_index)
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {
				auto& storage = self()->_storage;
				storage.erase(first_index);
			}
			else {
				auto& storage = self()->_storage;
				auto it = storage.find(first_index);

				if (it != storage.end()) {
					it->second.remove(next_index...);

					// Avoid empty branch
					if (it->second._storage.empty())
						storage.erase(it);
				}
			}
		}

	private:
		DEFINE_SELF
	};

} /* namespace NIndexedContainer */

#endif
