#ifndef INSERT_TRAIT_H_
#define INSERT_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

	template <typename T_container>
	struct insert_trait;

	template <
		typename T_content, 
		template <typename, typename> typename T_concrete_storage, 
		typename T_index, 
		typename T_trait_list, 
		typename T_propertie_list>
	struct insert_trait<n_indexed<T_content, T_concrete_storage, T_index, T_trait_list, T_propertie_list>> {

		/**
		 * \brief insert a node as the end of multiple paths
		 * \details 
		 * 
		 * \param value Node Content
		 * \param paths The paths going to the node being inserted
		 * \tparam TPaths... Paths types (such as tuple)
		 */
		template <typename ...TPaths>
		void insert(const T_content& value, const TPaths&... paths);
	};

}

#endif