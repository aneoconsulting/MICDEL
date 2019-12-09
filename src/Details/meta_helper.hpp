#ifndef N_INDEXED_META_HELPER_H_
#define N_INDEXED_META_HELPER_H_

namespace NIndexedContainer {

    template <template <typename...> typename T_meta_func, typename ...Targs>
    struct meta_curry {
        template <typename ...T>
        using type = T_meta_func<Targs..., T...>;
    };

}

#endif