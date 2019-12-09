#ifndef MAP_TREE_RANDOM_ACCESS_TRAIT_H_
#define MAP_TREE_RANDOM_ACCESS_TRAIT_H_

#include "../../Interface/random_access_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {

	/**
	 * \brief random_access_trait specialization for map_storage
	 * 
	 * \tparam T_content Value Type
	 * \tparam T_first_index First Index type
	 * \tparam T_next_indexes... Following Indexes types (can be empty)
	 * \tparam T_trait_list Trait List
	 */
	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct random_access_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		const T_content& at(const T_first_index& first_index, const T_next_indexes& ...next_indexes) const
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {	
				// Only One Index
				return self()->_storage.at(first_index);
			}
			else {
				// Several Indexes
				return self()->_storage.at(first_index).at(next_indexes...);
			}
		}

		T_content& at(const T_first_index& first_index, const T_next_indexes& ...next_indexes)
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {	
				// Only One Index
				return self()->_storage.at(first_index);
			}
			else {
				// Several Indexes
				return self()->_storage.at(first_index).at(next_indexes...);
			}
		}

		const T_content& operator()(const T_first_index& first_index, const T_next_indexes& ...next_indexes) const
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {	
				// Only One Index
				return self()->_storage[first_index];
			}
			else {
				// Several Indexes
				return self()->_storage[first_index](next_indexes...);
			}
		}

		T_content& operator()(const T_first_index& first_index, const T_next_indexes& ...next_indexes)
		{
			if constexpr (sizeof...(T_next_indexes) == 0) {	
				// Only One Index
				return self()->_storage[first_index];
			}
			else {
				// Several Indexes
				return self()->_storage[first_index](next_indexes...);
			}
		}

	private:
		DEFINE_SELF
	};

} /* namespace NIndexedContainer */


#endif 