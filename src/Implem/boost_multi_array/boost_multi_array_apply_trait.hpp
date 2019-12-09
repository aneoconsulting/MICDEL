#ifndef N_INDEXED_BOOST_MULTI_ARRAY_APPLY_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_APPLY_TRAIT_H_

#include <algorithm>
#include "../../Interface/apply_trait.hpp"
#include "boost_multi_array_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

    template <typename TContent, typename ...Tindexes, typename T_trait_list, typename TPropertieList>
    struct apply_trait<n_indexed<TContent, boost_multi_array_storage, indexes<Tindexes...>, T_trait_list, TPropertieList>> {

        template <typename Tfunc>
        void apply(Tfunc func)
        {
            std::for_each(
                    self()->_storage.data(),
                    self()->_storage.data() + self()->_storage.num_elements(),
                    func);
        }

    private:
        DEFINE_SELF
    };

}

#endif