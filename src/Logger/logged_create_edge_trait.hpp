#ifndef LOGGED_CREATE_EDGE_TRAIT_H_
#define LOGGED_CREATE_EDGE_TRAIT_H_

#include "../Interface/create_edge_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<create_edge_trait> {

        template <typename Tcontainer>
        struct trait : create_edge_trait<Tcontainer> {

            template <typename T_index, typename TPath1, typename TPath2>
            void create_edge(const T_index& index, const TPath1& path1, const TPath2& path2)
            {
                LOG("Create_edge(?)");
                create_edge_trait<Tcontainer>::create_edge(index, path1, path2);
            }

        };

    };

}

#endif