#ifndef LOGGED_FILTER_TRAIT_H_
#define LOGGED_FILTER_TRAIT_H_

#include "../Interface/filter_trait.hpp"
#include "log_manager.hpp"
#include "../Details/log_helpers.hpp"

namespace NIndexedContainer {

    template <>
    struct logged_trait<filter_trait> {

        template <typename Tcontainer>
        struct trait : filter_trait<Tcontainer> {

            template <typename ...TCriteria>
            auto filter(const TCriteria& ...criteria)
            {
                LOG("filter(criteria = ", comma(criterion_to_str(criteria)...), ")");
                return filter_trait<Tcontainer>::filter(criteria...);
            }

        };
    };

}

#endif