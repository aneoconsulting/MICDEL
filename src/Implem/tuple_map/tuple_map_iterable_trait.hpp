#ifndef N_INDEXED_MAP_TUPPLE_ITERABLE_TRAIT_H_
#define N_INDEXED_MAP_TUPPLE_ITERABLE_TRAIT_H_

#include "../../Interface/iterable_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {


    template <typename T_storage_iterator>
    struct map_tuple_storage_iterator : T_storage_iterator
    {
        map_tuple_storage_iterator(T_storage_iterator it)
        : T_storage_iterator{it}
        {}

        auto operator*()
        {
            const auto& deref = T_storage_iterator::operator*();
            return std::tuple_cat(deref.first, std::make_tuple(deref.second));
        }
    };

    template <typename T_storage_iterator>
    map_tuple_storage_iterator(T_storage_iterator) -> map_tuple_storage_iterator<T_storage_iterator>;

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct iterable_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        auto begin() noexcept
        {
            return map_tuple_storage_iterator{self()->_storage.begin()};
        }

        auto end() noexcept
        {
            return map_tuple_storage_iterator{self()->_storage.end()};
        }

        auto begin() const noexcept
        {
            return map_tuple_storage_iterator{self()->_storage.begin()};
        }

        auto end() const noexcept
        {
            return map_tuple_storage_iterator{self()->_storage.end()};
        }

    private:
        DEFINE_SELF

    };
}

#endif