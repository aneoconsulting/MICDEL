#ifndef GRAPH_FILTER_TRAIT_H_
#define GRAPH_FILTER_TRAIT_H_

#include <type_traits>
//#include <optional>

#include "../../Interface/filter_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "graph_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_trait_list>
	struct filter_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {
		
		using NodeType = n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>;

		//	Keep only the union of paths that meet the criterion 
		template <typename T_first_criterion, typename ...T_criteria>
		auto // std::optional<NodeType>
		filter(T_first_criterion&& first_criterion, T_criteria&& ...criteria)
		{
			//	The root node is always in a filter result (it is indexed by '()' )
			NodeType ret{};
			ret._content = self()->_content;
		
			auto& storage = ret.storage();

			//	map source raw_ptr to destination shared_ptr
			T_created_map created_nodes{};
			//bool a_path_did_match = false;

			for (auto& pair : self()->storage()) {
				if (criterion_match(pair.first, first_criterion)) {
					auto child = filter_helper(*(pair.second), created_nodes, std::forward<T_criteria>(criteria)...);

					if (child.second) {
						storage.emplace(pair.first, child.first->second);
						//a_path_did_match = true;
					}
				}
			}

			//if (a_path_did_match)
				return ret;
			//else 
			//	return std::nullopt;
		}

	private:
		using T_created_map = UnorderedMap<const NodeType*, SharedPtr<NodeType>>;
		using T_created_map_it = typename T_created_map::iterator;

		template <typename T_first_criterion, typename ...T_criteria>
		static std::pair<T_created_map_it, bool> 
		filter_helper(const NodeType& node, T_created_map& created_nodes, T_first_criterion&& first_criterion, T_criteria&& ...criteria)
		{
			const auto& nodeStorage = node.storage();

			bool was_created = false;
			T_created_map_it it = created_nodes.end();

			for (const auto& pair : nodeStorage) {

				if (criterion_match(pair.first, std::forward<T_first_criterion>(first_criterion))) {
					auto child = filter_helper(*(pair.second), created_nodes, std::forward<T_criteria>(criteria)...);

					if (!was_created && child.second) {
						was_created = true;
						it = filter_helper(node, created_nodes).first;
					}

					it->second->storage().emplace(pair.first, child.first->second);
				}
			}
				
			return { it, was_created };
		}

		static std::pair<T_created_map_it, bool> filter_helper(const NodeType& node, T_created_map& created_nodes)
		{
			auto cloned_node_it =
				created_nodes.find(&node);

			// If the node have not already been cloned
			if (cloned_node_it == created_nodes.end()) {
				//	Clone the node
				cloned_node_it =
					created_nodes.emplace(&node, std::make_shared<NodeType>()).first;
				
				// Set content
				cloned_node_it->second->_content = node._content;
			}

			return { cloned_node_it, true };	//	True because we are at the end of the path, so the path match the criterion
		}

		DEFINE_SELF
	};

}

#endif





