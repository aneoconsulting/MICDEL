#ifndef SIZE_TRAIT_H_
#define SIZE_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

	/**
	 * \struct size_trait
	 * \brief Size method return the number of values contained in the container
	 * 
	 */
	template<typename Tcontainer>
	struct size_trait {

		/**
		 * \return The number of value in this container
		 */
		auto size() const noexcept;
	};

#ifdef USE_CPP_2A_CONCEPT

	template <typename Tcontainer>
	concept sizeable = requires(Tcontainer x)
    {
	    {x.size()};
    };

#endif

} /* NIndexedContainer */

#endif