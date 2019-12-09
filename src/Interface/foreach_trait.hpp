#ifndef FOREACH_TRAIT_H_
#define FOREACH_TRAIT_H_

#include <functional>
#include "n_indexed.hpp"

namespace NIndexedContainer {

	template <typename>
	struct foreach_trait {

		/**
		 * \brief Like apply_trait, this apply a function to each Value, called with indexes
		 * \details The function will be called like func(T_indexes ...indexes, T_content& value) for each value ()
		 * 
		 * 
		 * \tparam T_func callable type
		 * \param func The function to apply
		 */
		template <typename T_func>
		void foreach(T_func func);
	};
	
} /* namespace NindexedContainer */

#endif