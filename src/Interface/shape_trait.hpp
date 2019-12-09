/**
 * \file ShapeTrait.hpp
 * \brief Provide shape function 
 * Provide shape function to get container size among each dimensions.
 */

#ifndef SHAPE_TRAIT_H_
#define SHAPE_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

    template <typename TContainer>
    struct shape_trait{

        /**
         * \details
         * \return Iterable container with size among each dimensions (For tensor)
         */
        auto shape() const noexcept; 
    };

} /* namespace n_indexed */

#endif /* SHAPE_TRAIT_H_T */

