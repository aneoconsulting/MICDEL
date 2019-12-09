#ifndef N_INDEXED_COMMA_H_
#define N_INDEXED_COMMA_H_

#include <ostream>
#include <type_traits>

#include "impl_helper.hpp"

namespace NIndexedContainer {

    /**
     * \brief [brief description]
     * \details [long description]
     * 
     * @tparam typename ...T [description]
     */
    template <typename ...T>
    struct comma_helper;

    template <typename Tf, typename ...Tn>
    struct comma_helper <Tf, Tn...>
    {
        static auto comma(std::ostream& s, const Tf& f, const Tn& ...n)
        {
            s << f << ", ";
            comma_helper<Tn...>::comma(s, n...);
        }

    };

    template <typename T>
    struct comma_helper<T> {

        static auto comma(std::ostream& s, const T& x)
        {
            s << x;
        }
    };

    template <>
    struct comma_helper<> {
        static auto comma(std::ostream&)
        {}
    };

    template <typename ...T>
    auto comma(const T& ...x)
    {
        std::stringstream s;
        comma_helper<T...>::comma(s, x...);
        return s.str();
    }

    /**
     *  \brief A meta predicate that check if a type can be streamed to std::ostream
     *  \tparam T the type being tested
     */
    template <typename T, typename = void>
    struct is_streamable : std::false_type {};

    template <typename T>
    struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream>() << std::declval<T>())>>
            : std::true_type {};

    template <typename T>
    static constexpr auto is_streamable_v = is_streamable<T>::value;

    /**
     *  
     */

    /**
     * \brief   Filter criteria to string     * 
     */
    template <typename T, typename = void>
    static constexpr auto is_a_predicate_v = false;

    template <typename T>
    static constexpr auto is_a_predicate_v<T, std::void_t<decltype(std::declval<T>()({}))>> =
            std::is_same_v<decltype(std::declval<T>()({})), bool>;

    template <typename T>
    auto criterion_to_str(const T& criterion)
    {
        if constexpr (std::is_same_v<T, criterion_all>)
            return "Criterion_all";
        else if constexpr (is_a_predicate_v<T>)
            return "a Predicate";
        else if constexpr (is_range_v<T>)
            return "a range of index";
        else if constexpr (is_streamable_v<T>)
            return criterion;
        else
            return "?";
    }

}

#endif
