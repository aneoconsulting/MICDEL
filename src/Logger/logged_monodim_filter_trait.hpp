#ifndef LOGGED_MONODIM_FILTER_TRAIT_H_
#define LOGGED_MONODIM_FILTER_TRAIT_H_

#include "../Interface/mono_dim_filter_trait.hpp"
#include "log_manager.hpp"
#include "../Details/log_helpers.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<mono_dim_filter_trait> {

        template <typename Tcontainer>
        struct trait : mono_dim_filter_trait<Tcontainer> {

            template <Size_t Dim, typename TCriterion>
            auto filter_dim(const TCriterion& criterion)
            {
                LOG("filter_dim<Dim = ", Dim, ">(criterion = ", criterion_to_str(criterion) ,")");
                return mono_dim_filter_trait<Tcontainer>::template filter_dim<Dim>(criterion);
            }

        };

    };

}

#endif
