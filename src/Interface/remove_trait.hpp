#ifndef REMOVE_TRAIT_H_
#define REMOVE_TRAIT_H_

#include <utility>
#include "n_indexed.hpp"

namespace NIndexedContainer {

    template <typename>
    struct remove_trait;

    /**
     * \brief add a method that allow to remove a value at a given index
     * 
     * \tparam T_content Value Type
     * \tparam T_concrete_storage ConcreteStorage type
     * \tparam T_index_list Indexes Types List
     * \tparam T_trait_list traits List
     */
    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename ...T_indexes, typename TraitList, typename T_propertie_list>
    struct remove_trait<n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, TraitList, T_propertie_list>> {
        
        /**
         * \brief Remove a value at a given index, if it exist
         * \param index Indexes of the value going to be removed
         */
        void remove(const T_indexes ...indexes) noexcept;
    };

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename T_trait_list, typename T_propertie_list>
    struct remove_trait<n_indexed<T_content, T_concrete_storage, dynamic_indexes, T_trait_list, T_propertie_list>> {

        /**
         * \brief Remove a value at a given index, if it exist
         * \param index Indexes of the value going to be removed
         */
        template <typename ...T_indexes>
        void remove(const T_indexes& ...indexes) noexcept;
    };

    //


/*
    template <typename Tcontainer, typename = void>
    static constexpr auto implement_remove = false;

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename ...T_indexes, typename TraitList>
    static constexpr auto implement_remove<
            n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, TraitList>,
            std::void_t<decltype(std::declval<n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, TraitList>>().remove(std::declval<T_indexes>()...))>
            > = true;

    template <typename T_content, template <typename, typename> typename T_concrete_storage, typename TraitList>
    static constexpr auto implement_remove<
            n_indexed<T_content, T_concrete_storage, dynamic_indexes , TraitList>> = true;
#ifdef USE_CPP_2A_CONCEPT

    template <typename TContainer>
    concept removable = implement_remove<TContainer>;

#endif

*/

} /* namespace NIndexedContainer */


#endif