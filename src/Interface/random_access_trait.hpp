#ifndef N_INDEXED_CONTAINER8RANDOM_ACCESS_TRAIT_H_
#define N_INDEXED_CONTAINER8RANDOM_ACCESS_TRAIT_H_

#include "n_indexed.hpp"

namespace NIndexedContainer {

	template <typename T_n_indexed>
	struct random_access_trait;

    /**
     * \struct random_access_trait
     * \brief Provide methods to access (read/create/write) random value in the container given their indexes
     * 
     * \tparam T_content Value Type
     * \tparam T_concrete_storage ConcreteStorage type
     * \tparam T_index_list Indexes Types List
     * \tparam T_trait_list traits List
     */
    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename ...T_indexes, typename T_trait_list, typename T_propertie_list> 
    struct random_access_trait<n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, T_trait_list, T_propertie_list>> {

        /**
         * \brief read random indexed access
         * \param indexes : Value position
         * \return const reference to Value if it exist
         * throw if the element indexed by the indexes doesn't exist
         */
        const T_content& at(const T_indexes& ...indexes) const;

        /**
         * \brief read/write random indexed access
         * \param indexes : Value position
         * \return reference to Value if it exist
         * throw if the element indexed by the indexes doesn't exist
         */
        T_content& at(const T_indexes& ...indexes);

        /**
         * \brief read random indexed access
         * \param indexes : Value position
         * \return const reference to Value
         * create the element indexed by the indexes or throw if it doesn't exist (depending on the concrete storage)
         */
        const T_content& operator() (const T_indexes& ...indexes) const;

        /**
         * \brief read random indexed access
         * \param indexes : Value position
         * \return reference to Value
         * create the element indexed by the indexes or throw if it doesn't exist (depending on the concrete storage)
         */
        T_content& operator() (const T_indexes& ...indexes);
    };

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename T_trait_list, typename T_propertie_list>
    struct random_access_trait<n_indexed<T_content, T_concrete_storage, dynamic_indexes, T_trait_list, T_propertie_list>> {
        
        template <typename ...T_indexes>
        const T_content& at(const T_indexes& ...index) const;

        template <typename ...T_indexes>
        T_content& at(const T_indexes& ...index);

        template <typename ...T_indexes>
        const T_content& operator()(const T_indexes ...indexes) const;

        template <typename ...T_indexes>
        T_content& operator()(const T_indexes ...indexes);
    };
    
} /* namespace NindexedContainer */

#endif /* Random Access Trait */
