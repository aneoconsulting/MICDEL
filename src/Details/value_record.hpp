#ifndef VALUE_RECORD_H_
#define VALUE_RECORD_H_

#include <utility>
#include <variant>
#include <type_traits>

#include "string_convertion.hpp"
#include "type_list.hpp"
#include "type_def.hpp"

namespace NIndexedContainer {

	// Supported Types

	using value_record_supported_types =
		type_list::list<
			int, char,
			long long int, 
			float, double, Size_t, String>;

	constexpr auto value_record_supported_types_count =
	        type_list::length_v<value_record_supported_types>;

	// Type -> Index
	        
	template <typename>
	struct type_index_helper;

	template <typename T_first, typename ...Types>
	struct type_index_helper<type_list::list<T_first, Types...>> {
		
		template <typename T>
		static constexpr Size_t index()
		{
			if constexpr (std::is_same_v<T_first, T>)
				return 0;
			else
				return 1 + type_index_helper<type_list::list<Types...>>::template index<T>();
		}

	};

	template <typename T>
	constexpr Size_t type_index()
	{
		static_assert (type_list::contains_v<T, value_record_supported_types>, "Unsupported type");
		return type_index_helper<value_record_supported_types>::template index<T>();
	}

	// Index -> Types

	template <Size_t Index, typename T_List>
	struct indexed_type_helper;

	template <Size_t Index, typename T_first, typename ...Types>
	struct indexed_type_helper<Index, type_list::list<T_first, Types...>> {
		using type =
			typename indexed_type_helper<Index - 1, type_list::list<Types...>>::type;
	};

	template <typename T_first, typename ...Types>
	struct indexed_type_helper<0, type_list::list<T_first, Types...>> {
		using type = T_first;
	};

	template <Size_t Index>
	struct indexed_type {
		using type =
			typename indexed_type_helper<Index, value_record_supported_types>::type;
	};

	template <Size_t Index>
	using indexed_type_t = typename indexed_type<Index>::type;


	struct value_record {
		
		template <typename T>
		explicit value_record(const T& v) noexcept :
			_type_index{type_index<T>()},
			_data{toString(v)}
		{}

		explicit value_record(const char *c_str) noexcept :
			value_record(String{c_str}) {}

		value_record(const value_record&) = default;
		~value_record() = default;

		bool operator==(const value_record& other) const noexcept
		{
			return
				_type_index == other._type_index &&
				_data == other._data;
		}

		bool operator!=(const value_record& other) const noexcept
		{
			return !operator==(other);
		}

		Size_t _type_index;
		String _data;
	};

	struct value_record_hasher {

		Size_t operator()(const value_record& v) const noexcept
		{
			const Size_t type_index_hash = std::hash<Size_t>{}(v._type_index);
			const Size_t data_hash = std::hash<String>{}(v._data);
			return type_index_hash ^ (data_hash << 1);
		}

	};

	// Apply function

	template <typename>
	struct apply_helper;

	template <Size_t ...Indexes>
	struct apply_helper<std::integer_sequence<Size_t, Indexes...>> {

		template <typename T_func>
		static auto apply(T_func&& func, const value_record& record)
		{
			// The list of types that can be returned by func
			using ret_type_list =
				type_list::unique_t<type_list::list<decltype(func(std::declval<indexed_type_t<Indexes>>()))...>>;

			if constexpr (std::is_same_v<type_list::list<void>, ret_type_list>) {
				// Function func return nothing
				impl(func, static_cast<void*>(nullptr), record);
			}
			else if constexpr (type_list::length_v<ret_type_list> == 1) {
				// Function always return the same type
				using ret_type = type_list::head_t<ret_type_list>;

				ret_type ret;
				impl(func, &ret, record);
				return ret;
			}
			else {
				// Function return a type depending on it parameters.
				// Use a variant to store the result
				using ret_type =
					type_list::instanciate_t<std::variant, ret_type_list>;

				ret_type ret;
				impl(func, &ret, record);
				return ret;
			}
		}

	private:

		template <typename TRet, Size_t Index, typename T_func>
		static bool call_helper(T_func&& func, TRet *ret, const value_record& record)
		{
			if (Index == record._type_index) {
				if constexpr (std::is_same_v<void, TRet>)
					func(fromString<indexed_type_t<Index>>(record._data));
				else
					*ret = func(fromString<indexed_type_t<Index>>(record._data));
				return true;
			}
			return false;
		}

		template <typename TRet, typename T_func>
		static void impl(T_func&& func, TRet *ret, const value_record& record)
		{
			(call_helper<TRet, Indexes>(func, ret, record) || ...);
		}

	};


	/**
	 * \brief Apply a function to the stored value
	 * 
	 * \param func function to apply
	 * \param record recorded value
	 * \return void if function return void else a variant of types returned by function on each supported types. 
	 * (if only one type is return one type is returned, then this type is used instead of variant)
	 * 	 
	 */
	template <typename T_func>
	auto apply(T_func func, const value_record& record)
	{
		return apply_helper<
			std::make_integer_sequence<Size_t, value_record_supported_types_count>>::template apply(func, record);
	}

	/**
	 * \brief compare a value with a value record
	 */
	template <typename T>
	inline bool equal(const value_record& value, const T& x)
	{
		return apply(
			[&x](const auto arg) { 
			
			using Targ = std::decay_t<decltype(arg)>;

			if constexpr (std::is_convertible_v<Targ, T>) {
				return x == static_cast<T>(arg);
			}
			else {
				return false;
			}

			}, value);
	}

	template <typename T>
	inline bool equal(const T& x, const value_record& value)
	{
		return equal(value, x);
	}

	inline auto as_variant(const value_record &value)
	{
		return
			apply([](const auto &x) { return x; }, value);
	}
}

#endif /* VALUE_RECORD_H_ */



