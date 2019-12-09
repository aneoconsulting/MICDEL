#ifndef N_INDEXED_MAP_TUPPLE_FOREACH_TRAIT_H_
#define N_INDEXED_MAP_TUPPLE_FOREACH_TRAIT_H_

#include "../../Interface/foreach_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct foreach_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {


        template <typename T_func>
        void foreach(T_func func)
        {
            auto& storage = self()->_storage;

            for (auto& pair : storage)
                std::apply(
                        [func, &pair](const Tindexes& ...indexes){ func(indexes..., pair.second); },
                        pair.first);
        }

    private:
        DEFINE_SELF
    };

}

#endif
