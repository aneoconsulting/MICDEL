#ifndef N_INDEXED_MAP_TUPLE_APPLY_TRAIT_H_
#define N_INDEXED_MAP_TUPLE_APPLY_TRAIT_H_

#include "../../Interface/apply_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct apply_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        template <typename Tfunc>
        void apply(Tfunc f)
        {
            auto& storage = self()->_storage;

            for (auto& pair : storage)
                f(pair.second);
        }

    private:
        DEFINE_SELF
    };

}

#endif