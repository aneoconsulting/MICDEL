#ifndef N_INDEXED_EIGEN_MATRIX_RANDOM_ACCESS_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_RANDOM_ACCESS_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/random_access_trait.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <
		typename Tcontent, 
		typename ...Tindex,
		typename Ttrait_list, typename TPropertieList>
	struct random_access_trait<n_indexed<Tcontent, eigen_matrix_storage, indexes<Tindex...>, Ttrait_list, TPropertieList>> {

		Tcontent& at(const Tindex& ...idx) noexcept
		{
			return self()->_storage(idx...);
		}

		const Tcontent& at(const Tindex& ...idx) const noexcept
		{
			return self()->_storage(idx...);
		}

		Tcontent& operator()(const Tindex& ...idx) noexcept
		{
			return self()->_storage(idx...);
		}

		const Tcontent& operator()(const Tindex& ...idx) const noexcept
		{
			return self()->_storage(idx...);
		}

	private:
		DEFINE_SELF
	};


}

#endif