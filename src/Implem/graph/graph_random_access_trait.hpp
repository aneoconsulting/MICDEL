#ifndef GRAPH_RANDOM_ACCESS_TRAIT_H_
#define GRAPH_RANDOM_ACCESS_TRAIT_H_

#include <stdexcept>

#include "../../Interface/random_access_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "graph_storage.hpp"

namespace NIndexedContainer {

	template <typename T_content, typename T_trait_list>
	struct random_access_trait<n_indexed<T_content, graph_storage, dynamic_indexes, T_trait_list>> {

		template <typename ...T_indexes>
		T_content& at(const T_indexes& ...indexes)
		{
			return self()->template safe_get_node(indexes...)->_content;
		}
		
		template <typename ...T_indexes>
		T_content& operator()(const T_indexes& ...indexes)
		{
			return self()->template get_node<true>(indexes...)->_content;
		}

	private:
		DEFINE_SELF
	};

} /* namespace n_indexed */

#endif