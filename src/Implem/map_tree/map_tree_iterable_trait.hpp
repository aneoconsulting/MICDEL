#ifndef MAP_TREE_ITERABLE_ACCESS_TRAIT_H_
#define MAP_TREE_ITERABLE_ACCESS_TRAIT_H_

#include <vector>
#include "../../Interface/iterable_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "map_tree_storage.hpp"

namespace NIndexedContainer {

	template <typename T_n_indexed>
	class tree_map_iterator;

	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	class tree_map_iterator<n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		using T_n_indexed = n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>;
		using T_child = n_indexed<T_content, map_tree_storage, indexes<T_next_indexes...>, T_trait_list>;
		using TStorageIterator = typename Map<T_first_index, T_child>::iterator;
		using TChildIterator = typename T_child::iterator;

		T_n_indexed *_node;
		TStorageIterator _storage_iterator;
		TChildIterator _child_iterator;

	public:
		tree_map_iterator()
		: _node{nullptr} {}

		tree_map_iterator(T_n_indexed& node, TStorageIterator sit, TChildIterator cit)
		: _node{&node}, _storage_iterator{sit}, _child_iterator{cit} {}

		tree_map_iterator(const tree_map_iterator<T_n_indexed>& other) = default;

		auto& operator++() noexcept
		{
			auto& child = _storage_iterator->second;

			if (_child_iterator != child.end())
				++_child_iterator;	// avoid incrementing end iterator
			
			// End of the child branch
			if (_child_iterator == child.end()) {
				auto next_storage_it = std::next(_storage_iterator);

				if (next_storage_it != _node->_storage.end()) {
					_storage_iterator = next_storage_it;
					_child_iterator = _storage_iterator->second.begin();
				}
			}

			return *this;
		}

		auto operator*() const noexcept
		{
			return std::tuple_cat(std::tie(_storage_iterator->first), *_child_iterator);
		}

		bool operator==(const tree_map_iterator<T_n_indexed>& other) const noexcept
		{
			return _storage_iterator == other._storage_iterator &&
					_child_iterator == other._child_iterator &&
					_node == other._node;
		}

		bool operator!=(const tree_map_iterator<T_n_indexed>& other) const noexcept
		{
			return !operator==(other);
		}
	};

	template <typename T_content, typename TIndex, typename T_trait_list>
	struct iterable_trait<n_indexed<T_content, map_tree_storage, indexes<TIndex>, T_trait_list>> {

		using iterator = typename Map<TIndex, T_content>::iterator;

		auto begin() noexcept
		{
			return self()->_storage.begin();
		}
		
		auto end() noexcept
		{
			return self()->_storage.end();
		}

	private:
		DEFINE_SELF
	};

	template <typename T_content, typename T_first_index, typename ...T_next_indexes, typename T_trait_list>
	struct iterable_trait < n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>> {

		using iterator = tree_map_iterator< n_indexed<T_content, map_tree_storage, indexes<T_first_index, T_next_indexes...>, T_trait_list>>;

		auto begin() noexcept
		{
			auto& node = *self();
			auto& storage = node._storage;

			if (storage.empty()) {
				return iterator{};
			}
			else {
				auto node_begin = storage.begin();
				auto& child = node_begin->second;
				auto child_begin = child.begin();

				return iterator{ node, node_begin, child_begin };
			}
		}
		
		auto end() noexcept
		{
			auto& node = *self();
			auto& storage = node._storage;

			if (storage.empty()) {
				return iterator{};
			}
			else {
				auto node_last = --(node._storage.end());
				auto& last_child = node_last->second;
				auto child_end = last_child.end();

				return iterator{ node, node_last, child_end };
			}
		}

	private:
		DEFINE_SELF
	};

	
} /* namespace NIndexedContainer */

#endif // MAP_ITERABLE_ACCESS_TRAIT_H_

