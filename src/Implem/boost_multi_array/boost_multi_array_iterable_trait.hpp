#ifndef N_INDEXED_BOOST_MULTI_ARRAY_ITERABLE_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_ITERABLE_TRAIT_H_

#include "boost_multi_array_storage.hpp"
#include "../../Interface/iterable_trait.hpp"
#include "../../Interface/random_access_trait.hpp"
#include "../../Interface/shape_trait.hpp"
#include "../../Details/tensor_iterator.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct iterable_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> :
            require_traits<
                    n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>,
                    random_access_trait,
                    shape_trait>
    {
        using Tcontainer =
            n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list>;

        auto begin() noexcept
        {
            return tensor_begin(*self());
        }

        auto end() noexcept
        {
            return tensor_end(*self());
        }

        auto begin() const noexcept
        {
            return tensor_begin(*self());
        }

        auto end() const noexcept
        {
            return tensor_end(*self());
        }

    private:
        DEFINE_SELF
    };

}

#endif



