#ifndef N_INDEXED_SUM_TRAIT_H_
#define N_INDEXED_SUM_TRAIT_H_


namespace NIndexedContainer {

	template <typename Tcontainer>
	struct sum_trait {
		auto operator+(const Tcontainer& ) const noexcept;
	};

}

#endif

