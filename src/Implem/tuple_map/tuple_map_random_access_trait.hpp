#ifndef MAP_TUPPLE_RANDOM_ACCESS_TRAIT_H_
#define MAP_TUPPLE_RANDOM_ACCESS_TRAIT_H_

#include "../../Interface/random_access_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "tuple_map_storage.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
    struct random_access_trait<n_indexed<Tcontent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list>> {

        const Tcontent& at(const Tindexes& ...i) const
        {
            return self()->_storage.at(std::make_tuple(i...));
        }

        Tcontent& at(const Tindexes& ...i)
        {
            return self()->_storage.at(std::make_tuple(i...));
        }

        const Tcontent& operator()(const Tindexes& ...i) const
        {
            return self()->_storage[std::make_tuple(i...)];
        }
        
        Tcontent &operator()(const Tindexes& ...i)
        {
            return self()->_storage[std::make_tuple(i...)];
        }

    private:
        DEFINE_SELF
    };

}

#endif
