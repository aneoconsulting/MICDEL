#ifndef ORDER_STORAGE_PROPERTIES_H_
#define ORDER_STORAGE_PROPERTIES_H_

#include <type_traits>					// std::conditional
#include "../Interface/n_indexed.hpp"	// storage_properties
#include "../Interface/standard_storage_properties.hpp"
#include "n_indexed_info.hpp"

namespace NIndexedContainer {

	/**
	 * \brief Pattern which match properties holding values 
	 */
	template <template <auto...> typename>
	struct value_propertie;

	/**
	 * \brief Pattern which match properties holding types 
	 */
	template <template <typename...> typename>
	struct type_propertie;

	/**
	 * \brief Check if a pattern match a property type
	 */
	template <typename Template, typename T>
	constexpr auto propertie_match = false;

	template <template <auto...> typename Template, auto ...Values>
	constexpr auto propertie_match<value_propertie<Template>, Template<Values...>> = true;

	template <template <typename...> typename Template, typename ...T>
	constexpr auto propertie_match<type_propertie<Template>, Template<T...>> = true;

	/**
	 * \brief Default properties value
	 */
	struct undefined_propertie;

	/**
	 * \brief A type pair : Template is the searched pattern and Default the default type returned when nothing match
	 */
	template <typename Template, typename Default = undefined_propertie>
	struct propertie_pattern;

	/**
	 * \brief Find the property matching a pattern in a list
	 * \details Return undefined_propertie if nothing match
	 */
	template <typename TPattern, typename TPropertieList>
	struct pick_propertie;

	template <typename Template, typename Default, typename ...TProperties>
	struct pick_propertie<propertie_pattern<Template, Default>, storage_properties<TProperties...>> {
		using type = Default;
	};

	template <typename Template, typename Default, typename Tfirst, typename ...T>
	struct pick_propertie<propertie_pattern<Template, Default>, storage_properties<Tfirst, T...>> {
		using type = 
			std::conditional_t<
				propertie_match<Template, Tfirst>,
				Tfirst,
				typename pick_propertie<propertie_pattern<Template, Default>, storage_properties<T...>>::type>;
	};

	template <typename TPattern, typename TPropertieList>
	using pick_propertie_t = 
		typename pick_propertie<TPattern, TPropertieList>::type;

	/**
	 *	\brief A helper which facilitate the use of properties by reordering them
	 */

	template <
		typename Tcontainer,
		typename Tag,
		template <typename...> typename T_storage_impl, 
		typename ...T_propertie_patterns>
	struct order_storage_properties;

	template <
		typename Tcontainer,
		template <typename...> typename T_storage_impl,
		typename ...T_propertie_patterns>
	struct order_storage_properties<Tcontainer, storage_tag, T_storage_impl, T_propertie_patterns...> :
		T_storage_impl<Tcontainer, pick_propertie_t<T_propertie_patterns, typename n_indexed_info<Tcontainer>::properties_list>...> 
	{
		using T_storage_impl<Tcontainer, pick_propertie_t<T_propertie_patterns, typename n_indexed_info<Tcontainer>::properties_list>...>::T_storage_impl;
	};

	/**
     *  A slice is a container whose one dimension has been removed. Thus, the properties list 
     *  of a slice are not necessarily the same as those of the original container. So we need
     *  a meta function that transform the original container properties list into the slice 
     *  properties list.
     *  
     *  This helper can be specialized for any new user defined properties
     * 
     */
    
    /**
     * \brief Transform a container property into a slice property
     * \tparam Dim the dimension being removed
     * \TPropertie
     */
    template <Size_t Dim, typename TPropertie>
    struct slice_propertie {
        using type = TPropertie;    // by default the slice property is the same
    };

    /**
     * \brief Transform a property list
     */
    template <Size_t Dim, typename TPropertieList>
    struct slice_propertie_list;

    template <Size_t Dim, typename ...TProperties>
    struct slice_propertie_list<Dim, storage_properties<TProperties...>> {
        using type =
                storage_properties<typename slice_propertie<Dim, TProperties>::type...>;
    };

    template <Size_t Dim, typename TPropertieList>
    using slice_propertie_list_t = typename slice_propertie_list<Dim, TPropertieList>::type;

    /**
     *  Here are the properties that need to be transformed when slicing
     */
    
    template <Size_t Dim, typename ...Extents>
    struct slice_propertie<Dim, dimensions<Extents...>> {
        using type = type_list::remove_nth_t <Dim, dimensions<Extents...>>;
    };

	/**
	 * 
	 */

	template <typename TPattern, typename TPropertie, typename TPropertiesList>
	struct properties_list_insert_or_replace;

	template <typename TPattern, typename TPropertie, typename TFirstPropertie, typename ...TNextProperties>
	struct properties_list_insert_or_replace<TPattern, TPropertie, storage_properties<TFirstPropertie, TNextProperties...>> {
		using type = 
			std::conditional_t<
				propertie_match<TPattern, TFirstPropertie>,
				storage_properties<TPropertie, TNextProperties...>,
				type_list::insert_t<TFirstPropertie, typename properties_list_insert_or_replace<TPattern, TPropertie, storage_properties<TNextProperties...>>::type>>;
	};

	template <typename TPattern, typename TPropertie>
	struct properties_list_insert_or_replace<TPattern, TPropertie, storage_properties<>> {
		using type = 
			storage_properties<TPropertie>;
	};

	template <typename TPattern, typename TPropertie, typename TPropertiesList>
	using properties_list_insert_or_replace_t = 
		typename properties_list_insert_or_replace<TPattern, TPropertie, TPropertiesList>::type;


}

#endif