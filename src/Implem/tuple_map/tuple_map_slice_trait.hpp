#ifndef N_INDEXED_MAP_TUPPLE_SLICE_TRAIT_H_
#define N_INDEXED_MAP_TUPPLE_SLICE_TRAIT_H_

#include "../../Interface/slice_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"
#include "../../Details/type_list.hpp"
#include "../../Details/tuple_helper.hpp"
#include "../../Details/n_indexed_helper.hpp"

namespace NIndexedContainer {


    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct slice_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        template <Uint Dim, typename Tindex_value>
        auto slice(const Tindex_value& select_value)
        { 
            using Tcontainer = 
                n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>;
            using slice_type =
                slice_type_t<Dim, Tcontainer>;

            auto& storage = self()->_storage;

            slice_type ret;

            bool slice_was_empty = true;
            for (const auto& pair : storage) {
                if (std::get<Dim>(pair.first) == select_value) {
                    ret._storage[tuple_remove_nth<Dim>(pair.first)] = pair.second;
                    slice_was_empty = false;
                }
            }

            if (slice_was_empty)
                throw empty_slice_exception{};

            return ret;
        }

    private:

        DEFINE_SELF
    };



}

#endif
