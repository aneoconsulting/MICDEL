#ifndef N_INDEXED_EIGEN_MATRIX_STORAGE_H_
#define N_INDEXED_EIGEN_MATRIX_STORAGE_H_

#include <Eigen/Core>

#include "../../Interface/n_indexed.hpp"
#include "../../Details/storage_properties_helper.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <typename>
	struct eigen_matrix_storage_type;

	/**
	 * \brief Transform a dimension property into the corresponding Eigen size
	 */
	template <typename Dim>
    static constexpr auto eigen_dim = Eigen::Dynamic;	// default, i.e if Dim==undefined_propertie

    template <auto Dim>
    static constexpr auto eigen_dim<static_dim<Dim>> = Dim;

	template <typename TExtentPropertie>
	struct eigen_matrix_storage_dims;

	template <typename Row, typename Col>
	struct eigen_matrix_storage_dims<dimensions<Row, Col>> {
		static constexpr auto rows = eigen_dim<Row>;
		static constexpr auto columns = eigen_dim<Col>;
	};

	template <typename Row> 
	struct eigen_matrix_storage_dims<dimensions<Row>> {
		static constexpr auto rows = eigen_dim<Row>;
	};

	/**
	 * 	Default behavior : When dimension is unspecified, dynamic is assumed
	 */
	template <>
	struct eigen_matrix_storage_dims<undefined_propertie> {
		static constexpr auto rows = Eigen::Dynamic;
		static constexpr auto columns = Eigen::Dynamic;
	};

	// --

	template <typename Tcontainer, typename TDimensionProperty, typename TStorageTypeProperty>
	struct eigen_matrix_storage_impl;

	template <typename Tcontainer, typename Tag>
	using eigen_matrix_storage = 
		order_storage_properties<
			Tcontainer, Tag,
			eigen_matrix_storage_impl,
			propertie_pattern<type_propertie<dimensions>>,
			propertie_pattern<type_propertie<eigen_matrix_storage_type>>
		>;

	// Matrix : 
	template <
		typename Tcontent, 
		typename Trow_index, typename Tcolumn_index, 
		typename Ttrait_list, typename TPropertieList, typename TDimensionPropertie> 
	struct eigen_matrix_storage_impl<
		n_indexed<Tcontent, eigen_matrix_storage, indexes<Trow_index, Tcolumn_index>, Ttrait_list, TPropertieList>, TDimensionPropertie, undefined_propertie> {

        template <typename ...Targs>
        eigen_matrix_storage_impl(Targs&& ...args)
        : _storage{std::forward<Targs>(args)...}
        {
        }

		Eigen::Matrix<
			Tcontent,
			eigen_matrix_storage_dims<TDimensionPropertie>::rows,
			eigen_matrix_storage_dims<TDimensionPropertie>::columns> _storage;
	};

	// Vector
	template <
		typename Tcontent,
		typename Tindex, 
		typename Ttrait_list, typename TPropertieList, typename TExtentPropertie> 
	struct eigen_matrix_storage_impl<
		n_indexed<Tcontent, eigen_matrix_storage, indexes<Tindex>, Ttrait_list, TPropertieList>, TExtentPropertie, undefined_propertie> {

	    template <typename ...Targs>
	    eigen_matrix_storage_impl(Targs&& ...args)
	    : _storage{std::forward<Targs>(args)...}
        {
        }

		Eigen::Matrix<
			Tcontent,
			eigen_matrix_storage_dims<TExtentPropertie>::rows, 1> _storage;
	};

	// View
	template <
		typename Tcontent, 
		typename Tindex,
		typename Ttrait_list, typename TPropertieList, typename TExtentPropertie, typename TstorageType>
	struct eigen_matrix_storage_impl<
		n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>, TExtentPropertie, eigen_matrix_storage_type<TstorageType>> {

		eigen_matrix_storage_impl(TstorageType&& sto) : _storage{std::move(sto)} {}
		eigen_matrix_storage_impl(eigen_matrix_storage_impl&&) = default;
		eigen_matrix_storage_impl(const eigen_matrix_storage_impl&) = default;

		TstorageType _storage;
	};
	
}

#endif