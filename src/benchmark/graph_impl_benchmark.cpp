#include <benchmark/benchmark.h>
#include "random_access_benchmark.hpp"
#include "deep_copy_benchmark.hpp"
#include "apply_benchmark.hpp"

#include "../Implem/graph/graph.hpp"

using namespace NIndexedContainer;

#ifndef BENCHMARK_CONTENT
#warning "BENCHMARK_CONTENT undefined, default is double"
#define BENCHMARK_CONTENT double
#endif

#ifndef BENCHMARK_INDEXES
#warning "BENCHMARK_INDEXES undefined, default is <int, int>"
#define BENCHMARK_INDEXES int,int
#endif

static void graph_random_access_insert(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, graph_storage, dynamic_indexes, traits<random_access_trait>>;

 	random_access_benchmark<container>::template do_insert_benchmark<BENCHMARK_INDEXES>(state);
} 	
BENCHMARK(graph_random_access_insert);

/*
static void graph_random_access_read(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, graph_storage, dynamic_indexes, traits<random_access_trait>>;

	random_access_benchmark<container>::template do_read_benchmark<BENCHMARK_INDEXES>(state);
} 	
BENCHMARK(graph_random_access_read);
*/

static void graph_deep_copy_benchmark(benchmark::State& state)
{
	using container =
		n_indexed<BENCHMARK_CONTENT, graph_storage, dynamic_indexes, traits<random_access_trait, size_trait>>;

	deep_copy_benchmark<container>::do_benchmark<BENCHMARK_INDEXES>(state);
}
BENCHMARK(graph_deep_copy_benchmark);

static void graph_apply_benchmark(benchmark::State& state)
{

	using container =
		n_indexed<BENCHMARK_CONTENT, graph_storage, dynamic_indexes, traits<random_access_trait, apply_trait>>;
	apply_benchmark<container>::do_benchmark<BENCHMARK_INDEXES>(state);
}
BENCHMARK(graph_apply_benchmark);
