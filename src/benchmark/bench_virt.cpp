
#include <benchmark/benchmark.h>
#include "test_virt.h"

static void bench_virt(benchmark::State &state)
{
	test t;
	int sum = 0, i = 1;

	for (auto _ : state) {
		t.virt_next(i, sum);
		benchmark::DoNotOptimize(sum);
	}
}
BENCHMARK(bench_virt);

static void bench_pas_virt(benchmark::State &state)
{
	test t;
	int sum = 0, i = 1;

	for (auto _ : state) {
		t.next(i, sum);
		benchmark::DoNotOptimize(sum);
	}
}
BENCHMARK(bench_pas_virt);

static void bench_inline(benchmark::State &state)
{
	test t;
	int sum = 0, i = 1;

	for (auto _ : state) {
		t.next_inline(i, sum);
		benchmark::DoNotOptimize(sum);
	}
}
BENCHMARK(bench_inline);
