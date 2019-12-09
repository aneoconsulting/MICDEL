#include <benchmark/benchmark.h>
#include "random_access_benchmark.hpp"
#include "deep_copy_benchmark.hpp"
#include "apply_benchmark.hpp"

#include "../Implem/map_tree/map_tree.hpp"

using namespace NIndexedContainer;

#ifndef BENCHMARK_CONTENT
#define BENCHMARK_CONTENT double
#error "kokok"
#endif

#ifndef BENCHMARK_INDEXES
#error "kokok"
#define BENCHMARK_INDEXES int,int,int,int,int,int,int,int,int,int,int,int,int,int
#endif

static void map_random_access_insert(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, map_tree_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait>>;

	random_access_benchmark<container>::do_insert_benchmark(state);
} 	
BENCHMARK(map_random_access_insert);

/*
static void map_random_access_read(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, map_tree_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait>>;

	random_access_benchmark<container>::do_read_benchmark(state);
} 	
BENCHMARK(map_random_access_read);
*/

static void map_deep_copy_benchmark(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, map_tree_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait, size_trait>>;

	deep_copy_benchmark<container>::do_benchmark(state);
}
BENCHMARK(map_deep_copy_benchmark);

static void map_apply_benchmark(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, map_tree_storage, indexes<BENCHMARK_INDEXES>, traits<random_access_trait, apply_trait>>;

    apply_benchmark<container>::do_benchmark(state);
}
BENCHMARK(map_apply_benchmark);