#ifndef N_INDEXED_EIGEN_MATRIX_STORE_CONV_H_
#define N_INDEXED_EIGEN_MATRIX_STORE_CONV_H_

#include "../../Interface/store_implicit_convertion_trait.hpp"
#include "eigen_matrix_storage.hpp"
#include "../../Details/impl_helper.hpp"

//#define ___TO_FLOAT

namespace NIndexedContainer {


	template <
		typename Tcontent, 
		typename Tindex, 
		typename Ttrait_list, typename TPropertieList>
	struct store_implicit_convertion_trait<n_indexed<Tcontent, eigen_matrix_storage ,Tindex, Ttrait_list, TPropertieList>> {

#ifdef ___TO_FLOAT

		operator auto&() noexcept
		{
			return le_float;
		}

		operator const auto&() const noexcept
		{
			return le_float;
		}
#else
		operator auto&() noexcept
		{
			return self()->_storage;
		}

		operator const auto&() const noexcept
		{
			return self()->_storage;
		}

#endif

	private:
		float le_float;
		DEFINE_SELF
	};

}

#endif

