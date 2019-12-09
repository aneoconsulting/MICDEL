#ifndef LOGGED_SLICE_VIEW_TRAIT_H_
#define LOGGED_SLICE_VIEW_TRAIT_H_

#include "../Interface/slice_view_trait.hpp"
#include "log_manager.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<slice_view_trait> {

        template <typename Tcontainer>
        struct trait : slice_view_trait<Tcontainer> {

            template <Uint Dim, typename TIndexValue>
            auto slice_view(const TIndexValue& index_value)
            {
                LOG("slice_view<Dim = ", Dim, ">(index = ", index_value, ")");
                return slice_trait<Tcontainer>::template slice<Dim>(index_value);
            }

        };

    };

}

#endif