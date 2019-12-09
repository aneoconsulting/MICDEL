#ifndef LOGGED_FOREACH_TRAIT_H_
#define LOGGED_FOREACH_TRAIT_H_

#include "../Interface/foreach_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<foreach_trait> {

        template <typename Tcontainer>
        struct trait : foreach_trait<Tcontainer> {

            template <typename Tfunc>
            void foreach(Tfunc&& func)
            {
                LOG("foreach(func = ?)");
                foreach_trait<Tcontainer>::foreach(std::forward<Tfunc>(func));
            }

        };

    };

}

#endif