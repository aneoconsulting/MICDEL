#ifndef N_INDEXED_BOOST_MULTI_ARRAY_RANDOM_ACCESS_TRAIT_H_
#define N_INDEXED_BOOST_MULTI_ARRAY_RANDOM_ACCESS_TRAIT_H_

#include "../../Interface/random_access_trait.hpp"
#include "boost_multi_array_storage.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

    template <typename Tcontent, typename ...Tindexes, typename Ttrait_list, typename TPropertieList>
    struct random_access_trait<n_indexed<Tcontent, boost_multi_array_storage, indexes<Tindexes...>, Ttrait_list, TPropertieList>> {

        using storage_type = boost::multi_array<Tcontent, sizeof...(Tindexes)>;
        using index_type = boost::array<typename storage_type::index, sizeof...(Tindexes)>;

        Tcontent& at(const Tindexes& ...indexes)
        {
            index_type idx{{indexes...}};
            return self()->_storage(idx);
        }

        const Tcontent& at(const Tindexes& ...indexes) const
        {
            index_type idx{{indexes...}};
            return self()->_storage(idx);
        }

        Tcontent& operator()(const Tindexes& ...indexes)
        {
            index_type idx{{indexes...}};
            return self()->_storage(idx);
        }

        const Tcontent& operator() (const Tindexes& ...indexes) const
        {
            index_type idx{{indexes...}};
            return self()->_storage(idx);
        }

    private:
        DEFINE_SELF
    };

}

#endif

