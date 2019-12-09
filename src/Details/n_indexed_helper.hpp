#ifndef N_INDEXED_N_INDEXED_HELPER_H_
#define N_INDEXED_N_INDEXED_HELPER_H_

#include "n_indexed_info.hpp"
#include "storage_properties_helper.hpp"
#include "meta_helper.hpp"
#include "type_list.hpp"

namespace NIndexedContainer {

    /**
     *  \brief Retrieve container type from trait
     */

    template <typename>
    struct trait_container;

    template <template <typename> typename Trait, typename Tcontainer>
    struct trait_container<Trait<Tcontainer>> {
        using type = Tcontainer;
    };

    template <typename T>
    using trait_container_t = typename trait_container<T>::type;

    /**
     *  \struct transform_properties
     *  \brief A helper struct
     *  
     *  \tparam Tcontainer The container whose properties have to be transformed
     *  \tparam TPropertieListModifier A meta function that transform a type list into another
     */
    template <typename Tcontainer, template <typename...> typename TPropertieListModifier>
    struct transform_properties;

    template <
            typename Tcontent,
            template <typename, typename> typename Tstorage,
            typename Tindex, typename TtraitList, typename TPropertieList,
            template <typename...> typename TPropertieListModifier>
    struct transform_properties<n_indexed<Tcontent, Tstorage, Tindex, TtraitList, TPropertieList>, TPropertieListModifier> {
        using type =
            n_indexed<Tcontent, Tstorage, Tindex, TtraitList, typename TPropertieListModifier<TPropertieList>::type>;
    };

    /**
     * \brief A slice type
     */

    template <Size_t Dim, typename Tcontainer>
    struct slice_type;

    template <Size_t Dim, typename Tcontent, template <typename, typename> typename T_concrete_storage, typename ...Tindexes, typename T_traitList, typename T_propertie_list>
    struct slice_type<Dim, n_indexed<Tcontent, T_concrete_storage, indexes<Tindexes...>, T_traitList, T_propertie_list>> {
        using type =
                n_indexed<
                        Tcontent, T_concrete_storage,
                        type_list::remove_nth_t<Dim, indexes<Tindexes...>>,  // Remove nth index
                        T_traitList,
                        slice_propertie_list_t <Dim, T_propertie_list>>;    // Transform storage_properties as needed
    };

    template <Size_t Dim, typename Tcontent, template <typename, typename> typename T_concrete_storage, typename Tindex, typename Ttrait_list, typename T_propertie_list>
    struct slice_type<Dim, n_indexed<Tcontent, T_concrete_storage, indexes<Tindex>, Ttrait_list, T_propertie_list>> {
        using type = Tcontent;  // Slicing a 1-Dimension container is just like getting a value !!!
    };

    template <Size_t Dim, typename Tcontainer>
    using slice_type_t = typename slice_type<Dim, Tcontainer>::type;

    template <typename Tcontainer, typename TProperty>
    using add_property_t = typename
            transform_properties<
                Tcontainer,
                meta_curry<type_list::insert, TProperty>::template type>::type;

    template <typename Tcontainer, typename TPattern, typename TPropertie>
    using insert_or_replace_property_t = typename
            transform_properties<
                Tcontainer,
                meta_curry<properties_list_insert_or_replace, TPattern, TPropertie>::template type>::type;
    //

}

#endif











