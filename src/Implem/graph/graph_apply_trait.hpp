#ifndef GRAPH_APPLY_TRAIT_H_
#define GRAPH_APPLY_TRAIT_H_

#include "../../Interface/apply_trait.hpp"
#include "graph_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_trait_list>
	struct apply_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {
		
		using node_type = n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>;

		template <typename T_func>
		void apply(T_func function)
		{
			self()->depth_first_search(
				[function](node_type& node) { function(node._content); });
		}

	private:
		DEFINE_SELF
	};

}

#endif // GRAPH_FOREACH_TRAIT_H_
