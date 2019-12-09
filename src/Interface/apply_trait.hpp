#ifndef APPLY_TRAIT_H_
#define APPLY_TRAIT_H_

#include "n_indexed.hpp"
#include <functional>

namespace NIndexedContainer {

    template <typename T_container>
    struct apply_trait {

        /**
         * \brief Apply a function to each value in the container
         * \details The function will be called like : function(T_content& value). The stored values may be modified.
         * \tparam T_func callable type
         * \param function the function to apply
         */
        template <typename T_func>
        void apply(T_func function);
    };


} /* namespace NIndexedContainer */

#endif /* APPLY_TRAIT_H_ */
