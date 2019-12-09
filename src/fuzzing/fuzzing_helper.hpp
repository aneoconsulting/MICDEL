#ifndef FUZZING_HELPER_H_
#define FUZZING_HELPER_H_

#include <cstdint>
#include <tuple>
#include <utility>
#include <type_traits>

namespace FuzzingHelper {


	// ---------

	class fuzz_stream {

	public:
		fuzz_stream(const uint8_t *data, const std::size_t size)
			: _data{data}, _size{size} {}

		fuzz_stream(fuzz_stream&) = delete;

		template <typename T>
		auto generate()
		{
			return generate_helper<T>::generate(_data, _size, _offset);
		}

		template <typename T>
		fuzz_stream& operator>>(T& v)
		{
			v = generate<T>();
			return *this;
		}

	private:
		const uint8_t *_data;
		std::size_t _size;
		std::size_t _offset{ 0u };

		template <typename T>
		struct generate_helper {

			static auto generate(const uint8_t *data, const std::size_t size, std::size_t& offset)
			{
				static_assert(std::is_trivially_copyable_v<T>);

				if (size == 0u) {
					return T{};
				}
				else {
					uint8_t tmp[sizeof(T)];
					for (auto i = 0u; i < sizeof(T); ++i, ++offset)
						tmp[i] = data[offset % size];
					return *reinterpret_cast<T*>(tmp);
				}
			}
		};

		template <typename ...T>
		struct generate_helper<std::tuple<T...>> {

			static auto generate(const uint8_t *data, const std::size_t size, std::size_t& offset)
			{
				if (size == 0u) {
					return std::make_tuple(T{}...);
				}
				else {
					return std::make_tuple(generate_helper<T>::generate(data, size, offset)...);
				}
			}
		};
	};

	//

	template <typename T, typename TOutputIt>
	auto generate_back(TOutputIt out, const std::size_t count, fuzz_stream& stream) 
	{
		for (auto i = 0u; i < count; ++i)
			*out++ = stream.generate<T>();
	}

	//

	template <typename T>
	struct func_fuzzer_helper :
		func_fuzzer_helper<decltype(&T::operator())> {};

	template <typename Tret, typename ...Targs>
	struct func_fuzzer_helper<Tret(Targs...)> {

		static auto gen_args(fuzz_stream& stream)
		{
			return stream.generate<std::tuple<Targs...>>();
		}
	};
	template <typename Tret, typename ...Targs>
	struct func_fuzzer_helper<std::function<Tret(Targs...)>> :
		func_fuzzer_helper <Tret(Targs...)> {};

	template <class T, typename T_ret, typename ...T_args>
	struct func_fuzzer_helper<T_ret(T::*)(T_args...)> :
		func_fuzzer_helper <T_ret(T_args...)> {};

	template <class T, typename T_ret, typename ...T_args>
	struct func_fuzzer_helper<T_ret(T::*)(T_args...) const> :
		func_fuzzer_helper <T_ret(T_args...)> {};

	template <typename Tret, typename ...Targs>
	struct func_fuzzer_helper<Tret(Targs...) noexcept>
		: func_fuzzer_helper<Tret(Targs...)> {};

	template <typename Tret, typename ...Targs>
	struct func_fuzzer_helper<Tret(*)(Targs...) noexcept>
		: func_fuzzer_helper<Tret(Targs...)> {};

	template <typename Tret, typename ...Targs>
	struct func_fuzzer_helper<Tret(*)(Targs...)>
		: func_fuzzer_helper<Tret(Targs...)> {};

	template <typename Tfunc>
	void function_fuzzer(const std::size_t count, Tfunc func, fuzz_stream& stream)
	{
		for (auto i = 0u; i < count; ++i) {
			auto arg = func_fuzzer_helper<Tfunc>::gen_args(stream);
			std::apply(func, arg);
		}
	}

}

#endif