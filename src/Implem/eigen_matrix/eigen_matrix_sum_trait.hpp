#ifndef EIGEN_MATRIX_SUM_TRAIT_H_
#define EIGEN_MATRIX_SUM_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/sum_trait.hpp"

namespace NIndexedContainer {

	template <
		typename Tcontent,
		typename Tindex,
		typename Ttrait_list, typename TPropertieList>
	struct sum_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>> {

		using Tcontainer = 
			n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>;	

		auto operator+(const Tcontainer& other) const noexcept
		{
			return self()->_storage + other._storage;
		}

	private:
		DEFINE_SELF
	};

}

#endif