#ifndef LOGGED_SIZE_TRAIT_H_
#define LOGGED_SIZE_TRAIT_H_

#include "../Interface/size_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<size_trait> {

        template <typename Tcontainer>
        struct trait : size_trait<Tcontainer> {

            auto size() const noexcept
            {
                LOG("size()");
                return size_trait<Tcontainer>::size();
            }

        };

    };
}

#endif