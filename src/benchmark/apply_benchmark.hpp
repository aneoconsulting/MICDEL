#ifndef APPLY_BENCHMARK_H_
#define APPLY_BENCHMARK_H_

#include <benchmark/benchmark.h>
#include "../Interface/apply_trait.hpp"
#include "../Details/impl_helper.hpp"
#include "benchmark_helper.hpp"

#include <vector>

namespace NIndexedContainer {

    template <typename TContainer>
    struct apply_benchmark {

        static_assert(implement_trait_v<TContainer, apply_trait>);

        template <typename ...TIndexes>
        static void do_benchmark(benchmark::State& state)
        {
            TContainer c;
            BenchmarkHelper::random_container_fill<TContainer, TIndexes...>(c, state.max_iterations);

            std::size_t count{0u};
            for (auto _ : state)
                c.apply([&count](const auto&){count++;});

            state.SetItemsProcessed(count);
        }

    };

    template <typename Tcontent, template <typename, typename> typename Tstorage, typename ...Tindexes, typename Ttrait_list, typename T_propertie_list>
    struct apply_benchmark<n_indexed<Tcontent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>> {

        using TContainer =
            n_indexed<Tcontent, Tstorage, indexes<Tindexes...>, Ttrait_list, T_propertie_list>;

        static void do_benchmark(benchmark::State& state)
        {
            TContainer c;
            BenchmarkHelper::random_container_fill<TContainer, Tindexes...>(c, state.max_iterations);

            std::size_t count{0u};
            for (auto _ : state)
                c.apply([&count](const auto&){count++;});

            state.SetItemsProcessed(count);
        }

    };
}


#endif


