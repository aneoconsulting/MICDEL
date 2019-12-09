#ifndef RANDOM_ACCESS_BENCHMARK_H_
#define RANDOM_ACCESS_BENCHMARK_H_

#include <benchmark/benchmark.h>
#include "../Interface/n_indexed.hpp"
#include "../Interface/random_access_trait.hpp"
#include "../Details/impl_helper.hpp"
#include "benchmark_helper.hpp"

namespace NIndexedContainer {
/*
	template <typename Tcontainer, typename ...Tindexes>
	void insert_benchmark_helper(benchmark::State& state)
	{
		static_assert(
			implement_trait_v<Tcontainer, random_access_trait>);

		using Targ = 
			std::tuple<Tindexes...>;
		Tcontainer c;

		auto arg_vec =
			BenchmarkHelper::random_vector<Targ>(state.max_iterations);

		// do_benchmark insert
		auto ind = 0u;
		for (auto _ : state) {
			std::apply(
				[&c](const Tindexes& ...indexes)
				{
				    const auto v = c(indexes...);
					benchmark::DoNotOptimize(v);
				}, arg_vec[ind++]);
		}
	}
*/	
	template <typename Tcontainer, typename ...Tindexes>
	void insert_benchmark_helper(benchmark::State& state)
	{
		int i = 0;
		Tcontainer c;

		for (auto _ : state)
			benchmark::DoNotOptimize(c(Tindexes{i++}...));
	}

	template <typename Tcontainer, typename ...Tindexes>
	void read_benchmark_helper(benchmark::State& state)
	{
		using Targ = 
				std::tuple<Tindexes...>;

		Tcontainer c;

		auto arg_vec =
			BenchmarkHelper::random_vector<Targ>(state.max_iterations);

		// insert

		for (const auto& arg : arg_vec) {
			std::apply([&c](const Tindexes& ...indexes)
			{
				c(indexes...);
			}, arg);
		}

		// access

		auto ind = 0u;
		for (auto _ : state) {
			std::apply(
				[&c](const Tindexes& ...indexes)
				{
                    const auto v = c.at(indexes...);
					benchmark::DoNotOptimize(v);
				}, arg_vec[ind++]);
		}
	}

	// ----

	template <typename Tcontainer>
	struct random_access_benchmark;

	template <typename TContent, template <typename, typename> typename Tstorage, typename ...Tindexes,typename Ttrait_list, typename T_propertie_list>
	struct random_access_benchmark<n_indexed<TContent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>> {
		using Tcontainer =
			n_indexed<TContent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>;

		static void do_insert_benchmark(benchmark::State &state)
		{
			insert_benchmark_helper<Tcontainer, Tindexes...>(state);
		}

		static void do_read_benchmark(benchmark::State &state)
		{
			read_benchmark_helper<Tcontainer, Tindexes...>(state);
		}

	};

	template <typename TContent, template <typename, typename> typename Tstorage, typename Ttrait_list, typename T_propertie_list>
	struct random_access_benchmark<n_indexed<TContent, Tstorage, dynamic_indexes, Ttrait_list, T_propertie_list>> {
		using Tcontainer = 
			n_indexed<TContent, Tstorage, dynamic_indexes, Ttrait_list, T_propertie_list>;

		template <typename ...Tindexes>
		static void do_insert_benchmark(benchmark::State &state)
		{
			insert_benchmark_helper<Tcontainer, Tindexes...>(state);
		}

		template <typename ...Tindexes>
		static void do_read_benchmark(benchmark::State &state)
		{

			read_benchmark_helper<Tcontainer, Tindexes...>(state);
		}
	};

}

#endif