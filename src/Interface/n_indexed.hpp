#ifndef N_INDEXED_CONTAINER_N_INDEXED_H_
#define N_INDEXED_CONTAINER_N_INDEXED_H_

namespace NIndexedContainer {

    /**
     * \struct indexes
     * \brief Describe static indexation : Indexes count and types are known at compile time
     * \tparam Tindexes... Indexes types
     */
    template <typename... Tindexes>
    struct indexes;

    /**
     * \struct dynamic_indexes
     * \brief Indexes are defined at runtime
     */
	struct dynamic_indexes;

    /**
     * 
     *      Traits List
     * 
     */

    /**
     * \struct traits_holder
     * \brief Trait template list
     */
    template <template <typename> typename... Traits>
    struct traits_holder;

    /**
     * \struct loggged_trait
     * \brief a meta function that enable logging for a given trait
     * \details Should be specialized for any given trait. 
     */
    template <template <typename> typename Ttrait>
    struct logged_trait {
        template <typename Tcontainer>
        using trait = Ttrait<Tcontainer>;
    };

    /**
     * \struct traits
     * \brief Traits type list
     * \details Wrap every trait wither logger when logging is enabled
     * 
     * TODO Doc Macro 
     */
#ifdef N_INDEXED_LOGGING
    template <template <typename> typename...Ttraits>
    using traits = traits_holder<logged_trait<Ttraits>::template trait...>;
#else
    template <template <typename> typename...Ttraits>
    using traits = traits_holder<Ttraits...>;
#endif

    /**
     * \struct storage_tag
     * \brief Only used to differentiate Storage from traits
     */
	struct storage_tag;

    /**
     * \struct storage_properties
     * \brief Type list containing all storage properties. Theses properties are type.
     * 
     * For example a property could be : 
     * 
     * - a policy
     * - a compile time dimension
     * - etc...
     */
    template <typename... T_properties>
    struct storage_properties;

    /**
     * \struct n_indexed
     * \brief n_indexed is the base container interface.  
     * \details
     *  
     *  This interface allow to describe the needed container. A multidimensional container is characterized by : 
     *          
     *  - a stored value type 
     *  - an indexation type
     *  - a storage method : This is a special trait that provide the storage method i.e. the way the container abstract data type is implemented
     *  - features : Theses are described with traits.
     *  - storage properties : Types used to customize the storage behavior
     * 
     * \tparam T_content The Stored Values Type
     * \tparam T_concrete_storage A trait that provide a storage method
     * \tparam T_index_list Describe indexation. Must be of the form indexes<types...> or dynamic_indexes
     * \tparam T_trait_list Requested feature list. Must be of the form traits<traits...>
     */
    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename T_index_list, typename T_trait_list, typename T_propertie_list = storage_properties<>>
    struct n_indexed;

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename T_index_list, template <typename> typename ...T_traits, typename T_propertie_list>
    struct n_indexed<T_content, T_concrete_storage, T_index_list, traits_holder<T_traits...>, T_propertie_list> :
		T_concrete_storage<n_indexed<T_content, T_concrete_storage, T_index_list, traits_holder<T_traits...>, T_propertie_list>, storage_tag>,
		T_traits<n_indexed<T_content, T_concrete_storage, T_index_list, traits_holder<T_traits...>, T_propertie_list>>...
    {
        // Provide default constructor if possible
		n_indexed() = default;

        // Allow copy from container based on the same storage but with different traits
		template <typename T_another_trait_list>
		n_indexed(const n_indexed<T_content, T_concrete_storage, T_index_list, T_another_trait_list, T_propertie_list>& other) :
			T_concrete_storage<n_indexed<T_content, T_concrete_storage, T_index_list, traits_holder<T_traits...>, T_propertie_list>, storage_tag>{other}
		{}

        //  Use storage constructor
        using T_concrete_storage<n_indexed<T_content, T_concrete_storage, T_index_list, traits_holder<T_traits...>, T_propertie_list>, storage_tag>::T_concrete_storage;
    };

} /* namespace NIndexedContainer */

#endif

