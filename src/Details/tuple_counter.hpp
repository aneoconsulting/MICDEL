#ifndef N_INDEXED_TUPLE_COUNTER_H_
#define N_INDEXED_TUPLE_COUNTER_H_

#include "type_def.hpp"

namespace NIndexedContainer {

    template <typename Tuple>
    class tuple_counter;

    template <typename ...T>
    class tuple_counter<Tuple<T...>> {

        static constexpr auto TupleSize = sizeof...(T);

    public:
        using TupleType = Tuple<T...>;

        tuple_counter(const TupleType& start, const TupleType& end) noexcept
                : _start{start}, _cur{start}, _end{end}
        {}

        tuple_counter(TupleType&& start, TupleType&& end) noexcept
                : _start{start}, _cur{_start}, _end{end}
        {}

        tuple_counter(const tuple_counter&) noexcept = default;
        tuple_counter(tuple_counter&&) noexcept = default;

        const auto& get_cur() const noexcept
        {
            return _cur;
        }

        const auto& next()
        {
            increment_tuple<std::make_index_sequence<TupleSize>>::increment(_cur, _end);
            return _cur;
        }

        bool operator==(const tuple_counter& other) const noexcept
        {
            return other._cur == _cur;
        }

        bool operator!=(const tuple_counter& other) const noexcept
        {
            return !operator==(other);
        }

    private:
        const TupleType _start;
        TupleType _cur;
        const TupleType _end;

        template <Size_t N>
        static auto increment_element(TupleType& cur, const TupleType& end)
        {
            // If N'th value can be incremented
            auto next_value = std::get<N>(cur) + 1;
            if (next_value < std::get<N>(end)) {
                std::get<N>(cur) = next_value;
                return true;
            }
            else {
                if constexpr (N != TupleSize - 1)
                    std::get<N>(cur) = 0;
                else 
                    cur = end;
                return false;
            }
        }

        template <typename TSeq>
        struct increment_tuple;

        template <Size_t ...N>
        struct increment_tuple<std::index_sequence<N...>> {
            static auto increment(TupleType& cur, const TupleType& end)
            {
                return (increment_element<N>(cur, end) || ...);
            }
        };
    };
}

#endif
