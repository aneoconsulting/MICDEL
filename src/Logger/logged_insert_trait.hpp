#ifndef LOGGED_INSERT_TRAIT_H_
#define LOGGED_INSERT_TRAIT_H_

#include "../Interface/insert_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<insert_trait> {

        template <typename Tcontainer>
        struct trait : insert_trait<Tcontainer> {

            template <typename Tcontent, typename ...TPaths>
            void insert(const Tcontent& value, const TPaths&... paths)
            {
                LOG("insert(value = ", value, ", paths = ? (", sizeof...(TPaths),"))");
                insert_trait<Tcontainer>::insert(value, paths...);
            }

        };

    };

}

#endif