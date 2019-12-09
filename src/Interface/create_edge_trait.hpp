#ifndef MAKE_EDGE_TRAIT_H_
#define MAKE_EDGE_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

	template <typename Tcontainer>
	struct create_edge_trait {

		/**
		 * \brief Create an edge carnying *index* between the node given by path1, and the node given by path2. Path are tuple like types.
		 *
		 * \param index Carried by the new edge
		 * \param path1 Path to the first node
		 * \param path2 Path to the second node
		 */
		template <typename T_index, typename TPath1, typename TPath2>
		void create_edge(const T_index& index, const TPath1& path1, const TPath2& path2);
	};

}

#endif