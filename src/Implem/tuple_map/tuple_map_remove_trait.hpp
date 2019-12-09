#ifndef N_INDEXED_MAP_TUPLE_REMOVE_TRAIT_H_
#define N_INDEXED_MAP_TUPLE_REMOVE_TRAIT_H_

#include "../../Interface/remove_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct remove_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        void remove(const Tindexes& ...i)
        {
            self()->_storage.erase(std::make_tuple(i...));
        }

    private:
        DEFINE_SELF
    };

}

#endif
