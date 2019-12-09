#ifndef N_INDEXED_BOOST_MULTI_ARRAY_SIZE_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_SIZE_TRAIT_H_

#include "../../Interface/size_trait.hpp"
#include "boost_multi_array_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct size_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {

        auto size() noexcept
        {
            return self()->_storage.num_elements();
        }


    private:
        DEFINE_SELF
    };

}

#endif
