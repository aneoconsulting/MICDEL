#ifndef N_INDEXED_MAP_TUPPLE_STORAGE_TRAIT_H_
#define N_INDEXED_MAP_TUPPLE_STORAGE_TRAIT_H_

#include "../../Interface/n_indexed.hpp"
#include "../../Details/type_def.hpp"

namespace NIndexedContainer {

    template <typename, typename>
    struct map_tuple_storage;

    /**
     * \struct map_tuple_storage
     * \brief Storage that map index tuple to value
     */
    template <typename TContent, typename ...Tindexes, typename Ttrait_list>
    struct map_tuple_storage<n_indexed<TContent, map_tuple_storage, indexes<Tindexes...>, Ttrait_list, storage_properties<>>, storage_tag> {

        using storage_type = Map<Tuple<Tindexes...>, TContent>;

    	template <typename T_another_trait_list>
    	map_tuple_storage(const map_tuple_storage<n_indexed<TContent, map_tuple_storage, indexes<Tindexes...>, T_another_trait_list, storage_properties<>>, storage_tag>& other)
    	: _storage{other._storage}
    	{}

        map_tuple_storage() = default;
        storage_type _storage;
    };

}

#endif
