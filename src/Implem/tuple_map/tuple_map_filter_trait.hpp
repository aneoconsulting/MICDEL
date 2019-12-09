#ifndef N_INDEXED_MAP_TUPPLE_FILTER_TRAIT_H_
#define N_INDEXED_MAP_TUPPLE_FILTER_TRAIT_H_

#include "../../Interface/filter_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"


namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct filter_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        using ret_type =
            n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>;

        template <typename ...TCriteria>
        auto filter(const TCriteria& ...criteria)
        {
            ret_type ret;
            const auto& storage = self()->_storage;
            static_assert(sizeof...(TCriteria) == sizeof...(Tindexes));

            for (const auto& pair : storage)
                if (index_tuple_match(pair.first, criteria...))
                    ret._storage.insert(pair);

            return ret;
        }

    private:

        template <typename T_index_seq, typename ...TCriteria>
        struct index_tuple_match_helper;

        template <Size_t ...I, typename ...TCriteria>
        struct index_tuple_match_helper<std::integer_sequence<Size_t, I...>, TCriteria...> {

            static auto match(const Tuple<Tindexes...>& value, const TCriteria& ...criteria)
            {
                return (criterion_match(std::get<I>(value), criteria) && ...);
            }

        };

        template <typename ...TCriteria>
        auto index_tuple_match(const Tuple<Tindexes...>& value, const TCriteria& ...criteria)
        {
            return index_tuple_match_helper<
                    std::make_integer_sequence <Size_t, sizeof...(Tindexes)>,
                    TCriteria...>::match(value, criteria...);
        }

        DEFINE_SELF
    };

}

#endif
