#ifndef GRAPH_SIZE_TRAIT_H_
#define GRAPH_SIZE_TRAIT_H_

#include "graph_storage.hpp"
#include "../../Interface/size_trait.hpp"
#include "../../Details/type_def.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_trait_list>
	struct size_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {

		Size_t size() const noexcept
		{
			Size_t res = 0;
			self()->depth_first_search([&res](const auto&...) {res++; });
			return res;
		}

	private:
		DEFINE_SELF
	};

} /* NIndexedContainer */

#endif // GRAPH_SIZE_TRAIT_H_
