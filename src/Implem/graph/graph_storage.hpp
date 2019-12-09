#ifndef GRAPH_STORAGE_H_
#define GRAPH_STORAGE_H_

#include <memory>
#include "../../Interface/n_indexed.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Details/type_def.hpp"
#include "../../Details/value_record.hpp"

namespace NIndexedContainer {

	template <typename, typename>
	struct graph_storage;

	/**
	 * \brief Describe a Directed Acyclic Graph
	 * \details Edge are carrying indexes, node are carrying values
	 * 
	 * \tparam T_content Values Type
	 * \tparam T_trait_list Trait List
	 */
	template <typename T_content, typename T_trait_list>
	struct graph_storage<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list, storage_properties<>>, storage_tag> {

		/**
		 * \brief Each Node is itself a n_indexed graph
		 */
		using node_type =
			n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list, storage_properties<>>;

		/**
		 * \brief Each Node map value record (indexes) to other nodes counted refs.
		 */
		using storage_type =
			UnorderedMap <value_record, SharedPtr<node_type>, value_record_hasher>;


		graph_storage() = default;

		/**
		 * \graph deep copy
		 * \details Default generated constructor would do a shallow copy
		 */
		graph_storage(const graph_storage& other)
		: _content{ other._content }
		{
			copyHelper(other);
		}

		/**
		 * \brief Idem, but support container with another trait list 
		 */
		template <typename T_another_trait_list>
		graph_storage(const graph_storage<n_indexed<T_content, graph_storage, dynamic_indexes, T_another_trait_list, storage_properties<>>, storage_tag>& other)
		: _content{ other._content }
		{
			copyHelper(other);
		}

		~graph_storage() = default;

		T_content _content;
		storage_type _storage;

		/**
		 * \brief Storage getter
		 * \details Storage will maybe be constructed on use in the future. If so this getter would avoid big change in the implementation
		 */
		const auto& storage() const noexcept
		{
			return _storage;
		}

		auto& storage() noexcept
		{
			return _storage;
		}

		/**
		 * \brief Find and retrieve a pointer to the node indexed by given indexes
		 * \details If create == true, the node will be created if it doesn't exist, else this return NULL
		 * 
		 * \return a pointer to the node indexed by given indexes
		 */
		template <bool Create, typename T_first_index, typename ...T_next_indexes>
		node_type *get_node(const T_first_index& first_index, const T_next_indexes& ...next_indexes)
		{
			const value_record firstIndexRecord{first_index};
			auto it = storage().find(firstIndexRecord);

			if (it == _storage.end()) {
				if constexpr (Create) {
					it = storage().emplace(
						first_index,
						std::make_shared<node_type>())	// create node
						.first;
				}
				else {
					return nullptr;					
				}
			}

			return it->second->template get_node<Create>(next_indexes...);
		}

		template <bool Create>
		node_type *get_node()
		{
			return self();
		}

		template <bool Create, typename ...T_indexes>
		node_type *get_node(const Tuple<T_indexes...>& path)
		{
			return std::apply(
				[&](const auto& ...indexes) {return this->get_node<Create, T_indexes...>(indexes...); }, path);
		}

		/**
		 * \brief Don't create node, return a valid pointer or throw
		 */
		template <typename ...TArgs>
		node_type *safe_get_node(const TArgs& ...args)
		{
			node_type *node = get_node<false>(args...);

			if (node != nullptr)
				return node;
			else
				throw std::invalid_argument{"Invalid Graph Index"};
		}


		/**
		 * \brief Helper method that apply a function to each node, in depth first search order 
		 */
		template <typename T_func>
		void depth_first_search(T_func func)
		{
			Set<const node_type*> visited_node;
			return depth_search_helper(*self(), func, visited_node);
		}

		template <typename T_func>
		void depth_first_search(T_func func) const
		{
			Set<const node_type*> visited_node;
			return depth_search_helper(*self(), func, visited_node);
		}

	private:

		template <typename T_func, typename T_node>
		static void depth_search_helper(T_node& node, T_func func, Set<const node_type*>& visited_node)
		{
			if (visited_node.find(&node) == visited_node.end()) {
				visited_node.insert(&node);
				func(node);

				const auto& nodeStorage = node.storage();

				for (const auto& pair : nodeStorage)
					depth_search_helper(*(pair.second), func, visited_node);
			}
		}

		template <typename T_another_trait_list>
		void copyHelper(const graph_storage<n_indexed<T_content, graph_storage, dynamic_indexes, T_another_trait_list, storage_properties<>>, storage_tag>& other)
		{
			using other_node_type = n_indexed<T_content, graph_storage, dynamic_indexes, T_another_trait_list, storage_properties<>>;

			// otherdNode -> selfNode
			// Used to know if a given node has already been copied, and where is the copy
			UnorderedMap<const other_node_type*, SharedPtr<node_type>> created_node{};

			other.depth_first_search(
				// For Each other Node
				[this, &created_node](const other_node_type& node) {
				auto cloned_node_it =
					created_node.find(&node);

				auto &cloned_node = (cloned_node_it == created_node.end()) ?
					*(self()) :		// Only the root wasn't registered
					*(created_node.at(&node));

				for (auto& pair : node.storage()) {
					other_node_type* child = pair.second.get();
					auto cloned_child_it = created_node.find(child);

					if (cloned_child_it == created_node.end()) {				// If child have not been copied
						auto cloned_child = std::make_shared<node_type>();		// Create child copy
						cloned_child->_content = child->_content;				// Assign content
						cloned_child_it =										// Record the node as copied
							created_node.insert(std::make_pair(child, std::move(cloned_child))).first;
					}

					// Link the Node
					cloned_node.storage().emplace(pair.first, cloned_child_it->second);
				}
			});
		}

		DEFINE_SELF
	};

}

#endif
