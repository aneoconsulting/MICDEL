
#include <benchmark/benchmark.h>
#include <boost/multi_array.hpp>

#include "../Interface/n_indexed.hpp"
#include "../Implem/boost_multi_array/boost_multi_array.hpp"
#include "../Implem/slice_view/slice_view.hpp"

constexpr auto SIZE = 16;
using Tcontent = double;


static void boost_multi_array_bracket(benchmark::State &state)
{
    using Tcontainer = boost::multi_array<Tcontent, 3>;

    Tcontainer container{boost::extents[SIZE][SIZE][SIZE]};

    int i=0 , j=0 , k=0;

    for (auto _ : state) {
        container[i][j][k] = i+j+k;
        i = (i+1) % SIZE;
        j = (i+2) % SIZE;
        k = (k+3) % SIZE;
    }
}
BENCHMARK(boost_multi_array_bracket);

static void boost_multi_array_index(benchmark::State &state)
{
    using Tcontainer = boost::multi_array<Tcontent, 3>;
    using Tindex = boost::array<typename Tcontainer::index, 3>;

    Tcontainer container{boost::extents[SIZE][SIZE][SIZE]};

    int i=0 , j=0 , k=0;

    for (auto _ : state) {
        const Tindex idx = {{i, j, k}};
        container(idx) = i+j+k;
        i = (i+1) % SIZE;
        j = (i+2) % SIZE;
        k = (k+3) % SIZE;
    }
}
BENCHMARK(boost_multi_array_index);

static void n_indexed_boost_multi_array(benchmark::State &state)
{
    using namespace NIndexedContainer;
    using Tcontainer =
            n_indexed<Tcontent, boost_multi_array_storage, indexes<int, int, int>, traits<random_access_trait>>;


    Tcontainer container{SIZE, SIZE, SIZE};
    int i=0 , j=0 , k=0;

    for (auto _ : state) {
        container(i, j, k) = i+j+k;
        i = (i+1) % SIZE;
        j = (i+2) % SIZE;
        k = (k+3) % SIZE;
    }
}

BENCHMARK(n_indexed_boost_multi_array);

//

static void boost_multi_array_slice_view(benchmark::State &state)
{
    using namespace NIndexedContainer;
    using Tcontainer =
            n_indexed<
                Tcontent, 
                boost_multi_array_storage,
                indexes<int, int, int>, 
                traits<
                    random_access_trait,
                    slice_view_trait
                >
            >;

    Tcontainer container{SIZE, SIZE, SIZE};
    int i=0 , j=0;

    for (auto _ : state) {
        auto view = container.slice_view<0>(0);
        view(i, j) = i+j;
        i = (i+1) % SIZE;
        j = (i+2) % SIZE;
    }


}
BENCHMARK(boost_multi_array_slice_view);

static void boost_multi_array_make_slice_view(benchmark::State &state)
{
    using namespace NIndexedContainer;
    using Tcontainer =
            n_indexed<
                Tcontent, 
                boost_multi_array_storage,
                indexes<int, int, int>, 
                traits<
                    random_access_trait
                >
            >;

    Tcontainer container{SIZE, SIZE, SIZE};
    int i=0 , j=0;

    for (auto _ : state) {
        auto view = make_slice_view<0>(container, 0);
        view(i, j) = i+j;
        i = (i+1) % SIZE;
        j = (i+2) % SIZE;
    }
}
BENCHMARK(boost_multi_array_make_slice_view);
//

extern "C" {

    // Pour analyser le code Machine :

    using n_indexed =
        NIndexedContainer::n_indexed<
            double, 
            NIndexedContainer::boost_multi_array_storage, 
            NIndexedContainer::indexes<int, int, int>, 
            NIndexedContainer::traits<NIndexedContainer::random_access_trait>>;

    using multi_array = boost::multi_array<double, 3>;
    using multi_array_index = boost::array<typename multi_array::index, 3>;


    const double get_multi_array(const multi_array& c, const int i, const int j, const int k)
    {
        const multi_array_index idx{{i, j, k}};
        return c(idx);
    }

    const double get_n_indexed(const n_indexed& c, const int i, const int j, const int k)
    {
        return c(i, j, k);
    }
}
