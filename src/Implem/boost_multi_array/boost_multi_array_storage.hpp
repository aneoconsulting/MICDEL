#ifndef N_INDEXED_BOOST_MULTI_INDEX_STORAGE_H_
#define N_INDEXED_BOOST_MULTI_INDEX_STORAGE_H_

#include "../../Interface/n_indexed.hpp"
#include "../../Details/type_list.hpp"
#include "../../Details/storage_properties_helper.hpp"
#include "../../Details/impl_helper.hpp"
#include <boost/multi_array.hpp>

namespace NIndexedContainer {

    template <typename>
    struct boost_multi_array_storage_type;

    template <typename Tcontainer, typename TstoreTypePropertie>
    struct boost_multi_array_impl;

    template <typename Tcontainer, typename Tag>
    using boost_multi_array_storage =
        order_storage_properties<
            Tcontainer, Tag,
            boost_multi_array_impl,
            propertie_pattern<type_propertie<boost_multi_array_storage_type>>
        >;

    //

    template <typename Tcontent, typename ...Tindexes, typename TtraitList, typename TPropertieList, typename Tstorage_type>
    struct boost_multi_array_impl<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, TtraitList, TPropertieList>, boost_multi_array_storage_type<Tstorage_type>>
    {   
        using storage_type = Tstorage_type;

        boost_multi_array_impl(storage_type&& sto)  : _storage{ std::move(sto)} {}
        boost_multi_array_impl(boost_multi_array_impl&&)  = default;
        boost_multi_array_impl(const boost_multi_array_impl&) = default; 

        storage_type _storage;
    };

    template <typename Tcontent, typename ...Tindexes, typename TtraitList, typename TPropertieList>
    struct boost_multi_array_impl<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, TtraitList, TPropertieList>, undefined_propertie>
    {
        using container_type = n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, TtraitList, TPropertieList>;
        using storage_type =  boost::multi_array<Tcontent, sizeof...(Tindexes)>;

        template <typename ...Tstorage_arg>
        boost_multi_array_impl(Tstorage_arg&& ...extents) :
        _storage{storage_arg_adapter<Tstorage_arg...>::arg(std::forward<Tstorage_arg>(extents)...)}
        {}

        boost_multi_array_impl(boost_multi_array_impl&&) noexcept (noexcept(storage_type(std::move(std::declval<storage_type>())))) = default;
        boost_multi_array_impl(const boost_multi_array_impl&) = default;

        storage_type _storage;

    private:
        
        /**
         * \brief Check if a type is a valid index type
         */

        template <typename T>
        struct is_valid_index :
                std::is_convertible<T, typename storage_type::index> {};

        /**
         * \brief Check if a type is a valid extent (dimension) type
         */
        template <typename T>
        struct is_valid_extent :
                std::is_convertible<T, typename storage_type::size_type> {};

        /**
         * 
         */
        template <typename ...T>
        struct storage_arg_adapter {
            static auto arg(T&& ...args) {
                if constexpr (type_list::true_for_each_v<is_valid_extent, type_list::list<T...>>)
                    return extents_helper<T...>::extents(std::forward<T>(args) ...);
                else
                    static_assert(always_false < T...>);
            }
        };

        template <typename T>
        struct storage_arg_adapter<T> {
            static auto arg(T&& a)
            {
                // When there is only one argument, we try to pass it directly to storage
                if constexpr (is_valid_extent<T>::value)
                    return extents_helper<T>::extents(std::forward<T>(a));              //  Parameter seems to be an extent
                else if constexpr (std::is_same_v<std::decay_t<T>, container_type>)     
                    return a._storage;                                                  //  Parameter is another container of the same type 
                else
                    return std::forward<T>(a);                                          //  Else forward parameter as it is (for example a view)
            }
        };

        /**
         * \brief Convert (e1, e2, ...) to boost::extents[e1][e2]...
         */
        template <typename Tidx, typename ...Tidxs>
        struct extents_helper {
            static auto extents(const Tidxs& ...idxs, const Tidx& idx)
            {
                return extents_helper<Tidxs...>::extents(idxs...)[idx];
            }
        };

        template <typename Tidx>
        struct extents_helper<Tidx> {
            static auto extents(const Tidx& idx)
            {
                return boost::extents[idx];
            }
        };


        //  Assert tat indexes types are valid
        static_assert(type_list::true_for_each_v<is_valid_index, indexes<Tindexes...>>);
    };

}

#endif

