#ifndef LOGGED_RANDOM_ACCESS_TRAIT_H_
#define LOGGED_RANDOM_ACCESS_TRAIT_H_

#include "../Interface/random_access_trait.hpp"
#include "log_manager.hpp"
#include "../Details/log_helpers.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<random_access_trait> {

        template <typename Tcontainer>
        struct trait : random_access_trait<Tcontainer> {

            template <typename ...T>
            auto& at(T&& ...idx)
            {
                static_assert(type_list::true_for_each_v<is_streamable, type_list::list<T...>>);
                LOG("at(", comma(idx...) ,")");
                return random_access_trait<Tcontainer>::at(std::forward<T>(idx)...);
            }

            template <typename ...T>
            const auto& at(T&& ...idx) const
            {
                static_assert(type_list::true_for_each_v<is_streamable, type_list::list<T...>>);
                LOG("at(", comma(idx...), ") const");
                return random_access_trait<Tcontainer>::at(std::forward<T>(idx)...);
            }

            template <typename ...T>
            auto& operator()(const T& ...idx)
            {
                static_assert(type_list::true_for_each_v<is_streamable, type_list::list<T...>>);
                LOG("operator()(", comma(idx...), ")");
                return random_access_trait<Tcontainer>::operator()(idx...);
            }

            template <typename ...T>
            const auto& operator()(const T& ...idx) const
            {
                static_assert(type_list::true_for_each_v<is_streamable, type_list::list<T...>>);
                LOG("operator()(", comma(idx...), ") const");
                return random_access_trait<Tcontainer>::operator()(idx...);
            }

        };
    };

}

#endif