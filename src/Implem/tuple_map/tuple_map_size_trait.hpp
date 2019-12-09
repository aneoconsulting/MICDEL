#ifndef N_INDEXED_MAP_TUPLE_SIZE_TRAIT_H_
#define N_INDEXED_MAP_TUPLE_SIZE_TRAIT_H_

#include "../../Interface/size_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct size_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        auto size() const noexcept
        {
            return self()->_storage.size();
        }
    private:
        DEFINE_SELF
    };

}

#endif
