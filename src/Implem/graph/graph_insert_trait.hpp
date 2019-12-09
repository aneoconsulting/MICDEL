#ifndef GRAPH_INSERT_TRAIT_H_
#define GRAPH_INSERT_TRAIT_H_

#include "../../Interface/insert_trait.hpp"
#include "../../Details/type_def.hpp"
#include "../../Details/tuple_helper.hpp"
#include "graph_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_trait_list>
	struct insert_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {

		template <typename ...TPaths>
		void insert(const T_content& value, const TPaths& ...paths)
		{
			// Create new Node
			auto new_node = std::make_shared<node_type>();
			new_node->_content = value;
			
			// For penultimate node of each path (created if it doesnt exist), Link to new node with last index of path
			(link(value_record{ tuple_last(paths) }, self()->template safe_get_node(tuple_without_last_view(paths)), new_node), ...);
			
		}

	private:
		using node_type = n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>;

		template <typename T_index>
		void link(T_index&& index, node_type *from, SharedPtr<node_type> to)
		{
			from->storage().emplace(std::forward<T_index>(index), to);
		}

		DEFINE_SELF
	};

}

#endif