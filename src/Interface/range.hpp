#ifndef RANGE_H_
#define RANGE_H_

#include <array>
#include <initializer_list> 

#include "../Details/type_def.hpp"

namespace NIndexedContainer {

	/**
	 * \brief A statically sized array
	 * 
	 * \tparam T Content type
	 * \tparam Size Size (compile time) 
	 */
	template <typename T, Size_t Size>
	class range {

	public:
		template <typename ...TArgs>
		range(TArgs&& ...arg) : _data{ std::forward<TArgs>(arg)... }
		{}

		auto begin() const noexcept { return _data.begin(); }
		auto end() const noexcept { return _data.end(); }
		auto operator[] (const Size_t index) noexcept {return _data[index];}
		auto at(const Size_t index) { return _data.at(index); }
		auto size() const noexcept { return _data.size(); }

	private:
		std::array<T, Size> _data;
	};

	// Deduction guides avoid to explicitly give type an size when instancing a range 
	template <typename T, typename ...Ts>
	range(T, Ts...) ->
		range<
			std::enable_if_t<(std::is_convertible_v<Ts, T> && ...), T>, 1 + sizeof...(Ts)>;

} /* namespace NIndexedContainer */


#endif