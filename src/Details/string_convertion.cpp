
#include "string_convertion.hpp"

namespace NIndexedContainer {

	template <>
	String fromString<String>(const String& str)
	{
		return str;
	}

	template <>
	int fromString<int>(const String& str)
	{
		return std::atoi(str.c_str());
	}

	template <>
	char fromString<char>(const String& str)
	{
		return str.c_str()[0];
	}

	template <>
	float fromString<float>(const String& str)
	{
		return static_cast<float>(std::atof(str.c_str()));
	}

	template <>
	double fromString<double>(const String& str)
	{
		return std::atof(str.c_str());
	}

	template <>
	Size_t fromString<Size_t>(const String& str)
	{
		return std::atoll(str.c_str());
	}

	template <>
	long long int fromString<long long int>(const String& str)
	{
		return std::atoll(str.c_str());
	}

} /* NIndexedContainer  */