#ifndef ITERABLE_TRAIT_H_
#define ITERABLE_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

    /**
     * \brief Provide an Iterable interface
     */
    template <typename T_container> 
    struct iterable_trait {

    	/**
    	 * \returns an iterator to the beginning of the container
    	 */
    	auto begin();

    	/**
    	 * \returns an iterator to the end of the container
    	 */
    	auto end();

    }; 

} /* namespace NIndexedContainer */

#endif /* ITERABLE_TRAIT_H_ */