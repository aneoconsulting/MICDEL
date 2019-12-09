#ifndef MAP_TREE_STORAGE_H_
#define MAP_TREE_STORAGE_H_

#include <map>
#include "../../Interface/n_indexed.hpp"
#include "../../Details/type_def.hpp"

namespace NIndexedContainer {

	/**
	 * \struct map_storage
	 * \brief Recursive Storage implementation using std::map
	 */
	template <typename, typename>
	struct map_tree_storage;

	/**
	 * \brief StorageMap for one index
	 * \details StorageMap for one index is semantically equivalent to an associative array which is here implemented using std::map
	 * 
	 * \tparam T_content Value Type
	 * \tparam T_index Index type
	 * \tparam T_trait_list traits list
	 */
	template <typename T_content, typename T_index, typename T_trait_list>
	struct map_tree_storage<n_indexed<T_content, map_tree_storage, indexes<T_index>, T_trait_list>, storage_tag> {

		map_tree_storage() = default;

		template <typename T_another_trait_list>
		map_tree_storage(const map_tree_storage<n_indexed<T_content, map_tree_storage, indexes<T_index>, T_another_trait_list>, storage_tag>& other) :
			_storage{other._storage}
		{}

		Map<T_index, T_content> _storage;
	};

	/**
	 * \brief StorageMap for several indexes
	 * \details StorageMap for several indexes is semantically equivalent to an associative array that map the first index to a n_indexed Structure with remaining indexes
	 * 
	 * \tparam T_content Value Type
	 * \tparam T_index Indexes types
	 * \tparam T_trait_list traits list
	 */
	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct map_tree_storage < n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>, storage_tag> {

		using T_child = n_indexed<T_content, map_tree_storage, indexes<T_next_indexes...>, T_trait_list>;

		map_tree_storage() = default;

		template <typename T_another_trait_list>
		map_tree_storage(const map_tree_storage<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_another_trait_list>, storage_tag>& other)
		{
			for (const auto& pair : other._storage)
				_storage.emplace(pair);
		}

		Map<T_first_index, T_child> _storage;
	};

} /* NIndexedContainer */

#endif