#ifndef GRAPH_MAKE_EDGE_TRAIT_H_
#define GRAPH_MAKE_EDGE_TRAIT_H_

#include "../../Details/tuple_helper.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Interface/create_edge_trait.hpp"
#include "graph_storage.hpp"

namespace NIndexedContainer {


	template <typename T_content, typename T_trait_list>
	struct create_edge_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {

		template <typename T_index, typename TPath1, typename TPath2>
		void create_edge(const T_index& index, const TPath1& path1, const TPath2& path2)
		{
			auto *node1 = self()->safe_get_node(path1);
			auto *node2_parent = self()->safe_get_node(tuple_without_last_view(path2));
			const auto path2_last_index = tuple_last(path2);

			auto it = node2_parent->storage().find(value_record{ path2_last_index });

			// If node2 does exist
			if (it != node2_parent->storage().end()) {
				auto *node2 = it->second.get();

				// Test if node 1 can be reached from node 2
				// (and thus if a cycle would be created by inserting the edge)
                bool cycle = false;
				node2->depth_first_search(
					[&cycle, node1](const auto& n) { cycle |= (&n == node1); });

				if (cycle)
					throw std::logic_error("Graph : MakeEdgeTrait : A cycle would be created");

				// Finally link node1 to node2
				node1->storage().emplace(index, it->second);
			}
			else 
				throw std::invalid_argument{ "Graph : MakeEdgeTrait : Invalid Graph Index" };
		}

	private:
		DEFINE_SELF
	};

}

#endif