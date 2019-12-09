#ifndef N_INDEXED_SCALAR_FACTOR_TRAIT_H_
#define N_INDEXED_SCALAR_FACTOR_TRAIT_H_

namespace NIndexedContainer {

    template <typename Tcontainer>
    struct scalar_factor_trait {
    	template <typename TScalar>
    	auto operator*(const TScalar&);
    };

    template <typename TScalar, typename Tcontainer>
    auto operator*(const TScalar& a, const scalar_factor_trait<Tcontainer>& c)
    {
    	return c * a;
    }

}

#endif
