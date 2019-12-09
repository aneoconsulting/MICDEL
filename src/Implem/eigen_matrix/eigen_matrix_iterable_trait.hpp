#ifndef N_INDEXED_EIGEN_MATRIX_ITERABLE_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_ITERABLE_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/iterable_trait.hpp"
#include "../../Interface/shape_trait.hpp"
#include "../../Interface/random_access_trait.hpp"
#include "../../Details/tensor_iterator.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <
		typename Tcontent,
		typename Tindex,
		typename Ttrait_list, typename TPropertieList>
	struct iterable_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>> :
		require_traits<n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>,
			shape_trait, random_access_trait> 
	{

		using Tcontainer = 
			n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>;

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