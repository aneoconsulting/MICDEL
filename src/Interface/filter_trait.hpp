#ifndef FILTER_TRAIT_H_
#define FILTER_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

	/**
	 * \struct criterion_all 
	 * \brief A custom criterion used to select all possible indexes in a given dimension
	 */
	struct criterion_all {};

	/**
	 * \brief Provide a filter method
	 */
	template <typename>
	struct filter_trait {

		/**
		 * \brief Build a new container according to criteria on indexes 
		 * 
		 * \param criteria... One criteria per index. Can be either index value or range, predicate or a criterion_all instance
		 * \tparam TCriteria Criteria types
		 * \return A n_indexed container containing the selection (that can be empty if nothing match the criteria)
		 */
		template <typename ...TCriteria>
		auto filter(const TCriteria& ...criteria);
	};



}

#endif