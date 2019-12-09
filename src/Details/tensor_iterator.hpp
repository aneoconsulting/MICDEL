#ifndef N_INDEXED_TENSOR_ITERATOR_H_
#define N_INDEXED_TENSOR_ITERATOR_H_

#include "../Interface/n_indexed.hpp"
#include "tuple_counter.hpp"
#include "impl_helper.hpp"


// For debug only
#include <iostream>

namespace NIndexedContainer {


    template <typename Tcontainer>
    class tensor_iterator {

        template <typename T>
        struct tensor_info;

        template <typename T>
        struct tensor_info<const T> : tensor_info<T> {};

        template <typename Tcontent, template <typename, typename> typename Tstorage, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
        struct tensor_info<n_indexed<Tcontent, Tstorage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {
            using type = Tuple<Tindexes...>;
            using content_type = Tcontent; 
            static constexpr auto indexes_count = sizeof...(Tindexes); 
        };

    public:
        using Tidx = typename tensor_info<Tcontainer>::type;
        using Tcontent = typename tensor_info<Tcontainer>::content_type;
        static constexpr auto indexes_count = tensor_info<Tcontainer>::indexes_count;

        // Need random_access and shape trait
        static auto begin(Tcontainer& c) noexcept
        {
            return tensor_iterator{c, get_begin_idx(c), get_end_idx(c)};
        }

        static auto end(Tcontainer& c) noexcept
        {
            const auto end_idx{get_end_idx(c)};
            return tensor_iterator{c, end_idx, end_idx};
        }

        auto& operator++() noexcept
        {
            _idx.next();
            return *this;
        }

        auto operator==(const tensor_iterator& other) const noexcept
        {
            return _idx == other._idx;
        }

        auto operator !=(const tensor_iterator& other) const noexcept
        {
            return !(_idx.operator==(other._idx));
        }

        auto operator*()
        {
            const auto& index = _idx.get_cur();

            if constexpr (std::is_const_v<Tcontainer>) {
                const auto value = std::apply([this](const auto& ...i){ return _container(i...); }, index);
                return std::tuple_cat( index, std::make_tuple(value));
            }
            else {
                auto& value = std::apply([this](const auto& ...i) -> Tcontent& { return _container(i...); }, index);
                return std::tuple_cat( index, std::tie(value));
            }
        }

    private:
        tensor_iterator(Tcontainer& ref, Tidx&& start, Tidx&& end)
        : _container{ref}, _idx{start, end}
        {
        }

        tensor_iterator(Tcontainer& ref, const Tidx& start, const Tidx& end)
        : _container{ref}, _idx{start, end}
        {
        }

        static auto get_begin_idx(const Tcontainer& c)
        {
            return Tidx{};
        }

        template <typename Seq>
        struct get_end_helper;

        template <Size_t ...N>
        struct get_end_helper<std::index_sequence<N...>>
        {
            static auto get_end(const Tcontainer& c)
            {
                const auto indexes_count = sizeof...(N);
                auto shape = c.shape();
                auto it = shape.begin();
                return Tidx{((void)N, *it++)...};
            }
        };

        static auto get_end_idx(const Tcontainer& c)
        {
            return get_end_helper<std::make_index_sequence<indexes_count>>::get_end(c);
        }

        Tcontainer& _container;
        tuple_counter<Tidx> _idx;
    };

    template <typename Tcontainer>
    auto tensor_begin(Tcontainer& c)
    {
        return tensor_iterator<Tcontainer>::begin(c);
    }

    template <typename Tcontainer>
    auto tensor_end(Tcontainer& c)
    {
        return tensor_iterator<Tcontainer>::end(c);
    }

}

#endif
