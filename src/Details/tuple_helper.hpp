#ifndef TUPLE_HELPER_H_
#define TUPLE_HELPER_H_

#include "type_def.hpp"

namespace NIndexedContainer {

	template <typename TSeq, typename TTuple>
	struct sub_tuple;

	template <typename ...T, typename Tint, Tint ...Indexes>
	struct sub_tuple<std::integer_sequence<Tint, Indexes...>, Tuple<T...>> {

		static auto view(Tuple<T...>& t)
		{
			return std::tie(std::get<Indexes>(t)...);
		}

        static auto view(const Tuple<T...>& t)
        {
            return std::tie(std::get<Indexes>(t)...);
        }

		static auto value(const Tuple<T...>& t)
        {
		    return std::make_tuple(std::get<Indexes>(t)...);
        }

	};

	/**  
	 * \tparam TSeq Selected indexes
	 * \return a view on a subset of tuple content
	 */
	template <typename TSeq, typename TTuple>
	auto sub_tuple_view(const TTuple &t)
	{
		return sub_tuple<TSeq, TTuple>::view(t);
	}

    template <typename TSeq, typename TTuple>
    auto sub_tuple_view(TTuple& t)
    {
        return sub_tuple<TSeq, TTuple>::view(t);
    }

    /**
     * \tparam TSeq Selected indexes
     * \return a subset of tuple content
     */
    template <typename TSeq, typename TTuple>
    auto sub_tuple_value(const TTuple& t)
    {
        return sub_tuple<TSeq, TTuple>::value(t);
    }

	/**
	 * \return a view on a tuple without the last element
	 */
	template <typename TTuple>
	auto tuple_without_last_view(const TTuple &t)
	{
		return sub_tuple_view<std::make_integer_sequence<Size_t, std::tuple_size_v<TTuple> - 1>>(t);
	}

    template <typename TTuple>
    auto tuple_without_last_value(TTuple& t)
    {
        return sub_tuple_value<std::make_integer_sequence<Size_t, std::tuple_size_v<TTuple> - 1>>(t);
    }

    /**
	 * \return Return the last index of a tuple
	 */
	template <typename TTuple>
	auto& tuple_last(TTuple& t) noexcept
	{
		static_assert(std::tuple_size_v<TTuple> > 0, "It is impossible to retrieve the last element of an empty tuple");
		return std::get<std::tuple_size_v<TTuple> -1>(t);
	}

	template <typename TTuple>
    const auto& tuple_last(const TTuple& t) noexcept
    {
        static_assert(std::tuple_size_v<TTuple> > 0, "It is impossible to retrieve the last element of an empty tuple");
        return std::get<std::tuple_size_v<TTuple> -1>(t);
    }

    /**
     * \return a view on a tuple without the nth element
     */

    template <typename T, T v, typename Tseq>
    struct integer_sequence_insert;

    template <typename T, T v, T ...i>
    struct integer_sequence_insert<T, v, std::integer_sequence<T, i...>> {
        using type =
                std::integer_sequence<T, v, i...>;
    };

    template <typename T, T v, typename Tseq>
    using integer_sequence_insert_t =
            typename integer_sequence_insert<T, v, Tseq>::type;

    template <Size_t N, typename Tseq>
    struct integer_sequence_remove_nth;

    template <typename T, T f, T ...n>
    struct integer_sequence_remove_nth<0, std::integer_sequence<T, f, n...>> {
        using type = std::integer_sequence<T, n...>;
    };

    template <Size_t N, typename T, T f, T ...n>
    struct integer_sequence_remove_nth<N, std::integer_sequence<T, f, n...>> {
        using type =
                integer_sequence_insert_t<T, f, typename integer_sequence_remove_nth<N - 1, std::integer_sequence<T, n...>>::type>;
    };

    template <Size_t N, typename Tseq>
    using integer_sequence_remove_nth_t =
            typename integer_sequence_remove_nth<N, Tseq>::type;

    template <Size_t N, typename TTuple>
    auto tuple_remove_nth(const TTuple& t)
    {
        static_assert( N < std::tuple_size_v<TTuple>);
        using tuple_indexes = std::make_integer_sequence<Size_t, std::tuple_size_v<TTuple>>;
        return sub_tuple_value<integer_sequence_remove_nth_t<N, tuple_indexes>>(t);
    }
}

#endif