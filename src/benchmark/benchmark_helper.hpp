#ifndef BENCHMARK_HELPER_H_
#define BENCHMARK_HELPER_H_

#include <vector>
#include <random>
#include <tuple>
#include <algorithm> 
#include "../Interface/random_access_trait.hpp"

namespace BenchmarkHelper {

	// TODO BETTER (Work only for POD type, tuple and strings)
	// Random value generation

	template <typename T>
	struct rand {

		using Type = std::decay_t<T>;

		static auto gen()
		{
			uint64_t data[sizeof(Type)];
			static_assert (std::is_trivially_copyable_v<Type>);

			for (auto i = 0; i < sizeof(Type); i++)
				data[i] = gen_byte();

			return *reinterpret_cast<Type*>(data);
		}

	private:
		
		static uint8_t gen_byte()
		{
			static std::mt19937_64 engine{42};
			static std::uniform_int_distribution dis{0u, 255u};
			return static_cast<uint8_t>(dis(engine));
		}
	};

	template <typename ...T>
	struct rand<std::tuple<T...>> {
		static auto gen()
		{
			return std::make_tuple(rand<T>::gen()...);
		}
	};

	template <>
	struct rand<std::string> {
	    static auto gen()
        {
	        const int len = 512;// + rand<uint8_t>::gen() & 0x7;
	        char array[len + 1];
	        for (auto i = 0u; i < len; i++) {
		  auto c = rand<char>::gen();
		  array[i] = c ? c : 'A';
		}
		array[len] = 0;
	        return std::string{array};
        }
	};

	template <typename T>
	auto random_vector(const size_t size)
	{
		auto ret = std::vector<T>{size};
		std::generate(ret.begin(), ret.end(), rand<T>::gen);
		return ret;
	};

	// ---

	template <typename TContainer, typename ...Tindexes>
	void random_container_fill(TContainer& c, const std::size_t count)
	{
		using namespace NIndexedContainer;
		static_assert(implement_trait_v<TContainer, random_access_trait>);

		using Tindex = std::tuple<Tindexes...>;
		using Tcontent = decltype(c.at(std::declval<Tindexes>()...));

		for (auto i = 0u; i < count; ++i)
			std::apply([&c](const Tindexes& ...i){ c(i...) = rand<Tcontent>::gen();},
					rand<Tindex>::gen());
	};

	// Insert N value

}

#endif
