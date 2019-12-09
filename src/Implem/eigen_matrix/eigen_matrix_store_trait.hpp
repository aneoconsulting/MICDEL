#ifndef EIGEN_MATRIX_STORE_TRAIT_H_
#define EIGEN_MATRIX_STORE_TRAIT_H_

#include "../../Interface/store_trait.hpp"
#include "beigen_matrix_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <typename Tcontent, typename Tindex, typename TtraitList>
	struct store_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindex, TtraitList>> {

		auto& store() noexcept
		{
			return self()->_storage;
		}

		const auto& store() const noexcept
		{
			return self()->storage;
		}

	private:
		DEFINE_SELF
	};

}

#endif