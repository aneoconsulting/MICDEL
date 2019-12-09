#ifndef LOGGED_REMOVE_TRAIT_H_
#define LOGGED_REMOVE_TRAIT_H_

#include "../Interface/remove_trait.hpp"
#include "log_manager.hpp"
#include "../Details/log_helpers.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<remove_trait> {

        template <typename Tcontainer>
        struct trait : remove_trait<Tcontainer> {

            template <typename ...Tindexes>
            void remove(const Tindexes& ...idx)
            {
                static_assert(type_list::true_for_each_v<is_streamable, type_list::list<Tindexes...>>);
                LOG("remove(", comma(idx...), ")");
                remove_trait<Tcontainer>::remove(idx...);
            }
        };

    };

}

#endif