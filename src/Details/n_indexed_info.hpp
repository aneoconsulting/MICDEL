
#ifndef N_INDEXED_INFO_H
#define N_INDEXED_INFO_H

#include "../Interface/n_indexed.hpp"


namespace NIndexedContainer {

    /**
     * \brief Retrieve informations about a n_indexed container
     */
    template <typename Tcontainer>
    struct n_indexed_info;

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename T_index_list, typename T_traitList, typename T_propertie_list>
    struct n_indexed_info<n_indexed<T_content, T_concrete_storage, T_index_list, T_traitList, T_propertie_list>> {
        using content_type = T_content;
        using index = T_index_list;
        using traits_list = T_traitList;
        using properties_list = T_propertie_list;
    };

    template <typename Tcontainer>
    struct n_indexed_info<const Tcontainer> : n_indexed_info<Tcontainer> {};

    template <template <typename> typename Ttrait, typename Tcontainer>
    struct n_indexed_info<Ttrait<Tcontainer>> : n_indexed_info<Tcontainer> {};



}

#endif