#ifndef LOGGED_ITERABLE_TRAIT_H_
#define LOGGED_ITERABLE_TRAIT_H_

#include "../Interface/iterable_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<iterable_trait> {

        template <typename Tcontainer>
        struct trait : iterable_trait<Tcontainer> {

            auto begin()
            {
                LOG("begin()");
                return iterable_trait<Tcontainer>::begin();
            }

            auto end()
            {
                LOG("end()");
                return iterable_trait<Tcontainer>::end();
            }
        };

    };

}

#endif