#ifndef N_INDEXED_EIGEN_MATRIX_SLICE_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_SLICE_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/slice_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Details/n_indexed_helper.hpp"

namespace NIndexedContainer {


	//	Slice only make sense for matrix

	template <
		typename Tcontent,
		typename Trow_index, typename Tcolumn_index,
		typename Ttrait_list, typename TPropertieList>
	struct slice_trait<n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>> {

		template <Size_t Dim, typename Tindex>
		auto slice(const Tindex& index_value)
		{
		    using Tcontainer =
		            n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>;
		    using Tslice = slice_type_t <Dim, Tcontainer>;

			auto& storage = self()->_storage;

			if constexpr (Dim == 0) {				//	Rows
				return Tslice{storage(index_value, Eigen::all)};
			}
			else if constexpr (Dim == 1) {	 		//	Columns
				return Tslice{storage(Eigen::all, index_value)};
			}
			else {
				static_assert(
					always_false<Tcontent>,
					"Eigen matrix can only be sliced on dim in [0, 1]");
			}
		}

	private:
		DEFINE_SELF
	};

}



#endif

