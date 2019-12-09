#ifndef N_INDEXED_BOOST_MULTI_ARRAY_FOREACH_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_FOREACH_TRAIT_H_

#include "../../Interface/foreach_trait.hpp"
#include "../../Interface/iterable_trait.hpp"
#include "boost_multi_array_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

    template <typename TContent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct foreach_trait<n_indexed<TContent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> :
            require_traits<n_indexed<TContent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>, iterable_trait> {

        template <typename Tfunc>
        void foreach(Tfunc func)
        {
            for (const auto& ord : *this)
                std::apply(func, ord);
        }
    };

}

#endif
