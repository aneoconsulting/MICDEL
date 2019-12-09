#ifndef N_INDEXED_BOOST_MULTI_ARRAY_SLICE_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_SLICE_TRAIT_H_

#include "../../Interface/slice_trait.hpp"
#include "../../Details/impl_helper.hpp"
#include "../../Details/n_indexed_helper.hpp"
#include "boost_multi_array_storage.hpp"


namespace NIndexedContainer {

    template <std::size_t Size, Uint Dim, typename Tarray, typename Tindex>
    struct slice_index_helper {
        static auto index(const Tindex& idx)
        {
            using index_range = typename Tarray::index_range;

            if constexpr (Dim == Size - 1)
                   return slice_index_helper<Size - 1, Dim, Tarray, Tindex>::index(idx)[idx];
                else
                    return slice_index_helper<Size - 1, Dim, Tarray, Tindex>::index(idx)[index_range{}];
        }
    };

    template <typename Tarray, Uint Dim, typename Tindex>
    struct slice_index_helper<0, Dim, Tarray, Tindex> {
        static auto index(const Tindex& idx)
        {
            using index_gen = typename Tarray::index_gen;
            return index_gen{};
        }
    };

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct slice_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {

        template <Uint Dim, typename Tindex>
        auto slice(const Tindex& index)
        {
            using TContainer = n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list>;
            using slice_type = slice_type_t <Dim, TContainer>;
            using Tarray = std::decay_t<decltype(self()->_storage)>;

            auto view = self()->_storage[slice_index_helper<sizeof...(Tindexes), Dim, Tarray, Tindex>::index(index)];

            return slice_type{view};
        }

    private:
        DEFINE_SELF
    };

}

#endif

