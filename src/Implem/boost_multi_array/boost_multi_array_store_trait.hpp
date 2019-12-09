#ifndef BOOST_MULTI_ARRAY_STORE_TRAIT_H_
#define BOOST_MULTI_ARRAY_STORE_TRAIT_H_

#include "../../Interface/store_trait.hpp"
#include "boost_multi_array_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <typename Tcontent, typename Tindex, typename TtraitList, typename TPropertieList>
	struct store_trait<n_indexed<Tcontent, boost_multi_array_storage, Tindex, TtraitList, TPropertieList>> {

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