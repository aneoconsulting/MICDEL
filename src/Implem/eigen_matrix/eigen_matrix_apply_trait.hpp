#ifndef N_INDEXED_EIGEN_MATRIX_APPLY_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_APPLY_TRAIT_H_

#include <algorithm>
#include "eigen_matrix_storage.hpp"
#include "../../Interface/apply_trait.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

    template <
            typename Tcontent,
            typename Tindexes,
            typename Ttrait_list, typename TPropertieList>
    struct apply_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindexes, Ttrait_list, TPropertieList>> {

        template <typename Tfunction>
        void apply(Tfunction func)
        {
            std::for_each(
                        self()->_storage.data(),
                        self()->_storage.data() + self()->_storage.size(),
                        func);
        }

    private:
        DEFINE_SELF
    };

}

#endif