#ifndef TYPE_DEF_H_
#define TYPE_DEF_H_

#include <map>
#include <memory>
#include <unordered_map>
#include <cstddef>
#include <string>
#include <tuple>
#include <set>
#include <array>

#include <gsl/gsl>

namespace NIndexedContainer {

    using Int = int;
    using Uint = unsigned int;
	using Size_t = std::size_t;
	using String = std::string;

	template <typename ...T>
	using Map = std::map<T...>;

	template <typename ...T>
	using UnorderedMap = std::unordered_map<T...>;

	template <typename ...T>
	using Tuple = std::tuple<T...>;

	template <typename ...T>
	using Set = std::set<T...>;

	template <typename ...T>
	using SharedPtr = std::shared_ptr<T...>;

	template <typename ...T>
	using UniquePtr = std::unique_ptr<T...>;

	template <typename T>
	using Span = gsl::span<T>;

	template <typename T, auto N>
	using Array = std::array<T, N>;


} /* n_indexed */

#endif