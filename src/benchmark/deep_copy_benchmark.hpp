#ifndef DEEP_COPY_BENCHMARK_H_
#define DEEP_COPY_BENCHMARK_H_

#include <benchmark/benchmark.h>
#include "../Interface/n_indexed.hpp"
#include "../Interface/random_access_trait.hpp"
#include "../Interface/size_trait.hpp"
#include "../Details/impl_helper.hpp"
#include "benchmark_helper.hpp"

namespace NIndexedContainer {

	template <typename Tcontainer, typename ...Tindexes>
	void deep_copy_benchmark_helper(benchmark::State& state)
	{
		Tcontainer c;

		static_assert(implement_trait_v<Tcontainer, size_trait>);

		// Fill container
		BenchmarkHelper::random_container_fill<Tcontainer, Tindexes...>(c, state.max_iterations);

		// Benchmark deep copy
		for (auto _ : state) {
			Tcontainer c2{ c };
			benchmark::DoNotOptimize(c2);
		}

		state.SetItemsProcessed(state.iterations() * c.size());
	}

	template <typename Tcontainer>
	struct deep_copy_benchmark;
	
	template <typename Tcontent, template <typename, typename> typename Tstorage, typename ...Tindexes, typename Ttrait_list, typename T_propertie_list>
	struct deep_copy_benchmark<n_indexed<Tcontent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>> {

		using Tcontainer =
			n_indexed<Tcontent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>;

		static void do_benchmark(benchmark::State &state)
		{
			deep_copy_benchmark_helper<Tcontainer, Tindexes...>(state);
		}

	};

	template <typename Tcontent, template <typename, typename> typename Tstorage, typename Ttrait_list, typename T_propertie_list>
	struct deep_copy_benchmark<n_indexed<Tcontent, Tstorage, dynamic_indexes, Ttrait_list, T_propertie_list>> {

		using Tcontainer =
			n_indexed<Tcontent, Tstorage, dynamic_indexes, Ttrait_list, T_propertie_list>;

		template <typename ...Tindexes>
		static void do_benchmark(benchmark::State &state)
		{
			deep_copy_benchmark_helper<Tcontainer, Tindexes...>(state);
		}

	};

}

#endif