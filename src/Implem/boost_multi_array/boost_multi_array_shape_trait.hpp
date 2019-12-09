#ifndef N_INDEXED_BOOST_MULTI_ARRAY_SHAPE_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_SHAPE_TRAIT_H_

#include "boost_multi_array_storage.hpp"
#include "../../Interface/shape_trait.hpp"
#include "../../Details/type_def.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct shape_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {

        auto shape() const noexcept
        {
            using Textent = std::remove_reference_t<decltype(*(self()->_storage.shape()))>;
            return Span<Textent>{self()->_storage.shape(), sizeof...(Tindexes)};
        }

    private:
        DEFINE_SELF
    };

}

#endif
