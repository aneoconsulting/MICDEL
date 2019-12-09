#ifndef N_INDEXED_EIGEN_MATRIX_SHAPE_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_SHAPE_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/shape_trait.hpp"
#include "../../Interface/range.hpp"

namespace NIndexedContainer {

    template <
		typename Tcontent,
		typename Trow_index, typename Tcolumn_index,
		typename Ttrait_list, typename TPropertieList>
	struct shape_trait<n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>> {

		auto shape() const noexcept
		{
			return range{self()->_storage.rows(), self()->_storage.cols()};
		}

	private:
		DEFINE_SELF
	};

    template <
            typename Tcontent,
            typename Tindex,
            typename Ttrait_list, typename TPropertieList>
    struct shape_trait<n_indexed<Tcontent, eigen_matrix_storage, indexes<Tindex>, Ttrait_list, TPropertieList>> {

        auto shape() const noexcept
        {
            return range{self()->_storage.row()};
        }

    private:
        DEFINE_SELF
    };



}

#endif
