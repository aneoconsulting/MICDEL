#ifndef EIGEN_MATRIX_SLICE_VIEW_TRAIT_H
#define EIGEN_MATRIX_SLICE_VIEW_TRAIT_H

#include "../../Interface/slice_view_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "eigen_matrix_storage.hpp"

namespace NIndexedContainer {

	template <
		typename Tcontent,
		typename Trow_index, typename Tcolumn_index,
		typename Ttrait_list, typename TPropertieList>
	struct slice_view_trait <n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>> {

		template <Size_t Dim, typename Tindex>
		auto slice_view(const Tindex& index_value)
		{
			using Tcontainer =
		    	n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>;
		   	
		   	auto& storage = self()->_storage;

		   	if constexpr (Dim == 0) {
		   		using slice_type = 
		   			insert_or_replace_property_t<
		   				slice_type_t<Dim, Tcontainer>,
		   				type_propertie<eigen_matrix_storage_type>,
		   				eigen_matrix_storage_type<std::decay_t<decltype(storage(index_value, Eigen::all))>>>;
		   		return slice_type{storage(index_value, Eigen::all)};
		   	}
		   	else { // Dim == 1
		   		using slice_type = 
		   			insert_or_replace_property_t<
		   				slice_type_t<Dim, Tcontainer>,
		   				type_propertie<eigen_matrix_storage_type>,
		   				eigen_matrix_storage_type<std::decay_t<decltype(storage(Eigen::all, index_value))>>>;
		   		return slice_type{storage(Eigen::all, index_value)};
		   	}
		}

	private:
		DEFINE_SELF
	};

}

#endif