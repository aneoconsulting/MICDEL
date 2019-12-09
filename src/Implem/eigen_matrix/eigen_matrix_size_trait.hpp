#ifndef N_INDEXED_EIGEN_MATRIX_SIZE_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_SIZE_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/size_trait.hpp"
#include "../../Details/impl_helper.hpp"


namespace NIndexedContainer {

	template <
		typename Tcontent,
		typename Tindex,
		typename Ttrait_list, typename TPropertieList>
	struct size_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindex, Ttrait_list, TPropertieList>> {

		auto size() const noexcept
		{
			return self()->_storage.size();
		}

	private:
		DEFINE_SELF
	};

}

#endif