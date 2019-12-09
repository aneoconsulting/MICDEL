#ifndef N_INDEXED_EIGEN_MATRIX_FOREACH_TRAIT_H_
#define N_INDEXED_EIGEN_MATRIX_FOREACH_TRAIT_H_

#include "eigen_matrix_storage.hpp"
#include "../../Interface/foreach_trait.hpp"
#include "../../Interface/iterable_trait.hpp"
#include "../../Details/impl_helper.hpp"


namespace NIndexedContainer {

	template <
		typename Tcontent,
		typename Tindexes,
		typename Ttrait_list, typename TPropertieList>
	struct foreach_trait<n_indexed<Tcontent, eigen_matrix_storage, Tindexes, Ttrait_list, TPropertieList>> :
	        require_traits<n_indexed<Tcontent, eigen_matrix_storage, Tindexes, Ttrait_list, TPropertieList>,
	                iterable_trait>{
		
		template <typename Tfunction>
		void foreach(Tfunction function)
		{
			auto& self_ref = *self(); 
			for (const auto& ord : self_ref)
				std::apply(function, ord);
		}

	private:
		DEFINE_SELF
	};
}

#endif