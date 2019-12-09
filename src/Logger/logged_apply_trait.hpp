#ifndef LOGGED_APPLY_TRAIT_H_
#define LOGGED_APPLY_TRAIT_H_

#include "../Interface/apply_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<apply_trait> {

        template <typename Tcontainer>
        struct trait : apply_trait<Tcontainer> {

            template <typename Tfunc>
            void apply(Tfunc func)
            {
                LOG("apply(func = ?)");
                apply_trait<Tcontainer>::apply(func);
            }

        };

    };

}

#endif