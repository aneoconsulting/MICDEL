#ifndef N_INDEXED_STORE_TRAIT_H_
#define N_INDEXED_STORE_TRAIT_H_


namespace NIndexedContainer {

	/**
	 * \brief Provide access to the internally used storage structure
	 */
	template <typename Tcontainer>
	struct store_trait {

		auto& store() noexcept;
		const auto& store() const noexcept;

	};

}

#endif