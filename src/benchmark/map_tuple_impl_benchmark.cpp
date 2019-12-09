#include <benchmark/benchmark.h>
#include "random_access_benchmark.hpp"
#include "deep_copy_benchmark.hpp"
#include "apply_benchmark.hpp"

#include "../Implem/tuple_map/tuple_map.hpp"

using namespace NIndexedContainer;

#ifndef BENCHMARK_CONTENT
#define BENCHMARK_CONTENT double
#endif

#ifndef BENCHMARK_INDEXES
#define BENCHMARK_INDEXES int,int,int,int,int,int,int,int,int,int,int,int,int,int
#endif

static void map_tuple_random_access_insert(benchmark::State &state)
{
    using container =
        n_indexed<BENCHMARK_CONTENT, map_tuple_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait>>;

    random_access_benchmark<container>::do_insert_benchmark(state);
}
BENCHMARK(map_tuple_random_access_insert);

/*
static void map_tuple_random_access_read(benchmark::State &state)
{
    using container =
    n_indexed<BENCHMARK_CONTENT, map_tuple_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait>>;

    random_access_benchmark<container>::do_read_benchmark(state);
}
BENCHMARK(map_tuple_random_access_read);
*/

static void map_tuple_deep_copy_benchmark(benchmark::State &state)
{
    using container =
    n_indexed<BENCHMARK_CONTENT, map_tuple_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait, size_trait>>;

    deep_copy_benchmark<container>::do_benchmark(state);
}
BENCHMARK(map_tuple_deep_copy_benchmark);

static void map_tuple_apply_benchmark(benchmark::State &state)
{
    using container =
    n_indexed<BENCHMARK_CONTENT, map_tuple_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait, apply_trait>>;

    apply_benchmark<container>::do_benchmark(state);
}
BENCHMARK(map_tuple_apply_benchmark);