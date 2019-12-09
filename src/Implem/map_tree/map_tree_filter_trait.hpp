#ifndef MAP_TREE_FILTER_TRAIT_H_
#define MAP_TREE_FILTER_TRAIT_H_

#include <type_traits>
#include "map_tree_storage.hpp"
#include "../../Interface/filter_trait.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	// Require size_trait

	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct filter_trait<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		template <typename ...TCriteria>
		auto filter( TCriteria&& ...criteria)
		{
			n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list> res;
			filter_impl(res, criteria...);
			return res;
		}

	private:
		template <typename TRes, typename TFirstCriterion, typename ...TNextCriteria>
		void filter_impl(TRes& res, const TFirstCriterion& first_criterion, const TNextCriteria& ...next_criteria)
		{
			auto& storage = self()->_storage;

			// No Criterion
			if constexpr (std::is_same_v<TFirstCriterion, criterion_all>) {
				// n lookup
				for (auto& pair : storage) {
					if constexpr (sizeof...(T_next_indexes) == 0)
						res._storage[pair.first] = pair.second;
					else {
						auto v = pair.second.filter(next_criteria...);
						if (v.size() != 0)
							res._storage[pair.first] = std::move(v);
					}
				}
			}
			// Criterion is an index value
			else if constexpr (std::is_convertible_v<TFirstCriterion, T_first_index>) {
				// log(n) lookup
				auto it = storage.find(first_criterion);
				if (it != storage.end()) {
					if constexpr (sizeof...(T_next_indexes) == 0)
						res._storage[first_criterion] = it->second;
					else {
						auto v = it->second.filter(next_criteria...);
						if (v.size() != 0)
							res._storage[first_criterion] = std::move(v);
					}
				}
			}
			// Criterion is a predicate
			else if constexpr (is_predicate_v<TFirstCriterion, T_first_index>) {
				// n lookup
				for (auto& pair : storage) {
					if (first_criterion(pair.first)) {
						if constexpr (sizeof...(T_next_indexes) == 0)
							res._storage[pair.first] = pair.second;
						else {
							auto v = pair.second.filter(next_criteria...);
							if (v.size() != 0)
								res._storage[pair.first] = std::move(v);
						}
					}
				}
			}
			// Criterion is a range of value
			else if constexpr (is_range_v<TFirstCriterion>) {
				for (const auto& index_value : first_criterion)
					filter_impl(res, index_value, next_criteria...);
			}
			else {
				static_assert(sizeof(TFirstCriterion) == -1, "");
			}
		}
		
		DEFINE_SELF
	};

} /* namespace NIndexedContainer*/

#endif