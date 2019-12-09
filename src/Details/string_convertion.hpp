#ifndef STRING_CONVERTION_H_
#define STRING_CONVERTION_H_

#include "type_def.hpp"

namespace NIndexedContainer {

	// Value to string

	template <typename T>
	inline String toString(const T& v)
	{
		return std::to_string(v);
	}

	template <>
	inline String toString(const String& str)
	{
		return str;
	}

	// String to Value

	template <typename T>
	T fromString(const String& str);

	template <>
	String fromString<String>(const String& str);

	template <>
	int fromString<int>(const String& str);

	template <>
	char fromString<char>(const String& str);

	template <>
	float fromString<float>(const String& str);

	template <>
	double fromString<double>(const String& str);

	template <>
	Size_t fromString<Size_t>(const String& str);

	template <>
	long long int fromString<long long int>(const String& str);

} /* NIndexedContainer */

#endif