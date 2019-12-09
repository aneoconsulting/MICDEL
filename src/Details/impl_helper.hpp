#ifndef IMPL_HELPER_H_
#define IMPL_HELPER_H_

#include <type_traits>
#include <iterator>

#include "../Interface/n_indexed.hpp"
#include "../Interface/filter_trait.hpp"             // criterion_all
#include "value_record.hpp"
#include "type_list.hpp"

namespace NIndexedContainer {

	/**
	 * \brief Helper with cast trait to CRTP base struct
	 */
	template <template <typename> typename Trait, typename T_n_indexed>
	auto self_impl(Trait<T_n_indexed> *ref)
	{
		return static_cast<T_n_indexed*>(ref);
	}

	template <template <typename, typename> typename T_concrete_storage, typename T_n_indexed>
	auto self_impl(T_concrete_storage<T_n_indexed, storage_tag> *ref)
	{
		return static_cast<T_n_indexed*>(ref);
	}

	template <template <typename> typename T_trait, typename T_n_indexed>
	auto self_impl_const(const T_trait<T_n_indexed> *ref)
	{
		return static_cast<const T_n_indexed*>(ref);
	}

	template <template <typename, typename> typename T_concrete_storage, typename T_n_indexed>
	auto self_impl_const(const T_concrete_storage<T_n_indexed, storage_tag> *ref)
	{
		return static_cast<const T_n_indexed*>(ref);
	}

    /**
     * \brief Provide a shortcut to define the self method
     */

#define DEFINE_SELF								\
	auto self() {return self_impl(this);}		\
	auto self() const {return self_impl_const(this);}


    /**
	 * \brief insert a trait in a trait list
	 */
	template <template <typename> typename Trait, typename Trait_list>
	struct add_trait;

	template <template <typename> typename Trait, template <typename> typename ...Traits>
    struct add_trait<Trait, traits_holder<Traits...>> {
        using type = traits_holder<Trait, Traits...>;
    };

    template <template <typename> typename Trait, typename Trait_list>
    using add_trait_t = typename add_trait<Trait, Trait_list>::type;

	/**
	 * \brief Test if a Trait List contain a Trait 
	 */
	template <template <typename> typename T_search_trait, typename ...T_trait_list>
	static constexpr auto contains_trait_v = false;

	template <template <typename> typename T_search_trait, template <typename> typename T_trait, template <typename> typename ...T_trait_list>
	static constexpr auto contains_trait_v<T_search_trait, traits_holder<T_trait, T_trait_list...>> = contains_trait_v<T_search_trait, traits_holder<T_trait_list...>>;

	template <template <typename> typename T_search_trait, template <typename> typename ...T_trait_list>
	static constexpr auto contains_trait_v<T_search_trait, traits_holder<T_search_trait, T_trait_list...>> = true;

	/**
	 * \brief Test if container implement a trait
	 * \tparam T_container
	 * \tparam T_search_trait
	 */
	template <typename T_container, template <typename> typename T_search_trait>
	struct implement_trait;

	template <typename T_content, template <typename, typename> typename T_storage, typename T_index, typename T_trait_list, template <typename> typename T_search_trait, typename T_propertie_list>
	struct implement_trait<n_indexed<T_content, T_storage, T_index, T_trait_list, T_propertie_list>, T_search_trait> {
		static constexpr auto value =
			contains_trait_v<T_search_trait, T_trait_list>;
	};

	template <typename T_container, template <typename> typename T_search_trait>
	static constexpr auto implement_trait_v = implement_trait<T_container, T_search_trait>::value;

    /**
     * \brief Remove a trait from trait list 
     * \tparam T_container
     * \tparam T_search_trait
     */

    template <template <typename> typename Trait, typename Ttrait_list>
    struct without_trait;

    template <template <typename> typename Trait, template <typename> typename ...Traits>
    struct without_trait<Trait, traits_holder<Trait, Traits...>> {
        using type = traits_holder<Traits...>;
    };

    template <template <typename> typename Trait, template <typename> typename First, template <typename> typename ...Traits>
    struct without_trait<Trait, traits_holder<First, Traits...>> {
        using type = add_trait_t<First, without_trait<Trait, traits_holder<Traits...>>>;
    };

    template <template <typename> typename Trait, typename T_content, template <typename, typename> typename T_storage, typename T_index, typename T_trait_list, typename T_propertie_list>
    struct without_trait<Trait, n_indexed<T_content, T_storage, T_index, T_trait_list, T_propertie_list>> {
        using type = n_indexed<T_content, T_storage, T_index, typename without_trait<Trait, T_trait_list>::type, T_propertie_list>;
    };

    template <template <typename> typename Trait, typename Ttrait_list>
    using without_trait_t = typename without_trait<Trait, Ttrait_list>::type;

	/**
	 * \brief Test if a Type is a range type 
	 */

	template <typename T, typename = void>
	struct range_trait : std::false_type {};

	template <typename T>
	struct range_trait<T, std::void_t <decltype(std::begin(std::declval<T>()), std::end(std::declval<T>()))>> : std::true_type
	{
	    using T_content = decltype(*std::begin(std::declval<T>()));
	};

	template <typename T>
	static constexpr bool is_range_v = range_trait<T>::value;

	template <typename Trange, typename Tvalue>
	static constexpr auto is_range_of()
    {
	    if constexpr (is_range_v<Trange>)
	        return std::is_convertible_v<typename range_trait<Trange>::T_content, Tvalue>;
	    else
	        return false;
    }

    template <typename Trange, typename Tvalue>
    static constexpr auto is_range_of_v = is_range_of<Trange, Tvalue>();

    /**
     * \brief Test if a type is a predicate
     */

    template <typename T_func, typename T_value>
    struct is_predicate :
            std::is_invocable_r<bool, T_func, T_value> {};
    template <typename T_func, typename T_value>

    static constexpr auto is_predicate_v =
            is_predicate<T_func, T_value>::value;

    /**
     * \brief Check if a function is a predicate for each type in type list
     */
    template <typename T_func, typename T_list>
    static constexpr auto is_predicate_for_each_v = false;

    template <typename T_func, typename ...T>
    static constexpr auto is_predicate_for_each_v<T_func, type_list::list<T...>> =
            (is_predicate_v<T_func, T> && ...);

    /**
     * 
     */
    template <typename T_func>
    static constexpr auto is_value_record_predicate_v =
            is_predicate_for_each_v<T_func, value_record_supported_types>;

    /**
     * \brief Test if a value match a criterion
     * \detail a criterion can be either
     *      -  a value          :   Match if value are equals
     *      -  a range          :   Match if value is in the range 
     *      -  a predicate      :   Match if predicate(value) = true
     */

    template <typename T_value, typename T_criterion>
    struct criterion_matcher;

    template <typename T_value, typename T_criterion>
    auto criterion_match(const T_value& value, const T_criterion criterion)
    {
        return criterion_matcher<T_value, T_criterion>::match(value, criterion);
    }

    template <typename T_value, typename T_criterion>
    struct criterion_matcher {
        static auto match(const T_value& value, const T_criterion criterion)
        {
            if constexpr (std::is_same_v<T_criterion, criterion_all>)
                return true;
            else if constexpr (is_predicate_v<T_criterion, T_value>)
                return criterion(value);
            else if constexpr (is_range_of_v<T_criterion, T_value>) {
                for (const auto& v : criterion)
                    if (criterion_match(value, v)) return true;
                return false;
            }
            else {
                return (value == T_value{criterion});
            }
        }
    };

    template <typename T_criterion>
    struct criterion_matcher<value_record, T_criterion> {
        static auto match(const value_record& value, const T_criterion criterion)
        {
            if constexpr (std::is_same_v<T_criterion, criterion_all>)
                return true;
            else if constexpr (is_value_record_predicate_v<T_criterion>)
                return apply(criterion, value);
            else if constexpr (is_range_v<T_criterion>) {
                for (const auto& v : criterion)
                    if (equal(value,v )) return true;
                return false;
            }
            else {
                return equal(value, criterion);
            }
        }
    };

    /**
     *  \brief Used to forbid a compile time branch with static assert
     */
    template <typename ...T>
    static constexpr auto always_false = false;

    
    /**
     * \brief Automatically enable a trait
     */

    namespace anti_memoisation {

        /**
         * 
         * 
         * 
         */

        template <template <typename> typename T_search_trait, typename ...T_trait_list>
        static constexpr auto contains_trait_v = false;
    
        template <template <typename> typename T_search_trait, template <typename> typename T_trait, template <typename> typename ...T_trait_list>
        static constexpr auto contains_trait_v<T_search_trait, traits_holder<T_trait, T_trait_list...>> = contains_trait_v<T_search_trait, traits_holder<T_trait_list...>>;

        template <template <typename> typename T_search_trait, template <typename> typename ...T_trait_list>
        static constexpr auto contains_trait_v<T_search_trait, traits_holder<T_search_trait, T_trait_list...>> = true;
    

        template <typename T_container, template <typename> typename T_search_trait>
        struct implement_trait;
    
        template <typename T_content, template <typename, typename> typename T_storage, typename T_index, typename T_trait_list, template <typename> typename T_search_trait, typename T_propertie_list>
        struct implement_trait<n_indexed<T_content, T_storage, T_index, T_trait_list, T_propertie_list>, T_search_trait> {
            static constexpr auto value =
                contains_trait_v<T_search_trait, T_trait_list>;
        };
    
        template <typename T_container, template <typename> typename T_search_trait>
        static constexpr auto implement_trait_v = implement_trait<T_container, T_search_trait>::value;
    }
    

    template <typename Tcontainer, template <typename> typename Trait, typename = void>
    struct require_trait : Trait<Tcontainer> {};

    template <typename Tcontainer, template <typename> typename Trait>
    struct require_trait<Tcontainer, Trait, std::enable_if_t<anti_memoisation::implement_trait_v<Tcontainer, Trait>>> {};

    template <typename Tcontainer, template <typename> typename ...Traits>
    struct require_traits : require_trait<Tcontainer, Traits>... {};

}

#endif
