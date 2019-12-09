#ifndef N_INDEXED_BOOST_MULTI_ARRAY_SLICE_VIEW_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_SLICE_VIEW_H_

#include "../../Interface/slice_view_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Details/n_indexed_helper.hpp"
#include "boost_multi_array_storage.hpp"

namespace NIndexedContainer {

	template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct slice_view_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {
		
		template <Uint Dim, typename Tindex>
        auto slice_view(const Tindex& index)
        {
            using TContainer = n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list>;
            using Tarray = std::decay_t<decltype(self()->_storage)>;
            using Tarray_slice = typename Tarray::template array_view<sizeof...(Tindexes) - 1>::type;
            using slice_type = 
                insert_or_replace_property_t<
                    slice_type_t <Dim, TContainer>, 
                    type_propertie<boost_multi_array_storage_type>, 
                    boost_multi_array_storage_type<Tarray_slice>>;
            
            auto view = self()->_storage[slice_index_helper<sizeof...(Tindexes), Dim, Tarray, Tindex>::index(index)];

            return slice_type{std::move(view)};
        }

    private:
        DEFINE_SELF
	};

}

#endif