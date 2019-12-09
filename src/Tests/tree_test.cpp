
#include "catch.hpp"

#include <string>
#include <vector>

#include "../Details/tuple_helper.hpp"
#include "../Details/type_def.hpp"
#include "../Interface/range.hpp"

#include "../Implem/map_tree/map_tree.hpp"
#include "../Implem/tuple_map/tuple_map.hpp"

#include "../Logger/logger.hpp"


using namespace NIndexedContainer;



TEMPLATE_TEST_CASE("random_access_trait/size_trait", "[random_access]",
                   (n_indexed<String, map_tuple_storage, indexes<String, int, int>,  traits<random_access_trait, size_trait>>),
                   (n_indexed<String, map_tree_storage, indexes<String, int, int>,  traits<random_access_trait, size_trait>>))
{
    using Container = TestType;
	Container c;

	// write
	c("hello", 32, 2) = "zaza";
	c("hello", 32, 1) = "zozo";

	// read
	REQUIRE(c.at("hello", 32, 2) == "zaza");
	REQUIRE(c.at("hello", 32, 1) == "zozo");
	REQUIRE(c.size() == 2);

	// change
	c("hello", 32, 2) = "zeze";
	REQUIRE(c.at("hello", 32, 2) == "zeze");
	REQUIRE(c.size() == 2);
	
	// copy
	Container c2{ c };

	REQUIRE(c2.at("hello", 32, 1) == "zozo");
	REQUIRE(c2.at("hello", 32, 2) == "zeze");
	REQUIRE(c.size() == 2);
	REQUIRE(c2.size() == 2);

	// copy is independent from original
	c("hello", 32, 1) = "abcd";
	c("hello", 32, 2) = "azer";

	REQUIRE(c.at("hello", 32, 1) == "abcd");
	REQUIRE(c.at("hello", 32, 2) == "azer");
	REQUIRE(c2.at("hello", 32, 1) == "zozo");
	REQUIRE(c2.at("hello", 32, 2) == "zeze");
	REQUIRE(c.size() == 2);
	REQUIRE(c2.size() == 2);
}

TEMPLATE_TEST_CASE("RandomAccessTrait/SizeTait/RemoveTrait", "[]",
          (n_indexed<String, map_tuple_storage, indexes<String, int>,  traits<random_access_trait, size_trait, remove_trait>>),
          (n_indexed<String, map_tree_storage, indexes<String, int>,  traits<random_access_trait, size_trait, remove_trait>>))
{

	using Container = TestType;
	Container c;

	c("A", 42) = "hello";
	c("B", 42) = "coucou";
	c("B", 43) = "ok";
	
	REQUIRE(c.at("A", 42) == "hello");
	REQUIRE(c.at("B", 42) == "coucou");
	REQUIRE(c.at("B", 43) == "ok");
	REQUIRE(c.size() == 3);

	c.remove("B", 42);

	REQUIRE(c.at("A", 42) == "hello");
	REQUIRE(c.at("B", 43) == "ok");
	REQUIRE(c.size() == 2);
}

TEMPLATE_TEST_CASE("RandomAccessTrait/MonoDimFilter/Size", "[]", 
          (n_indexed<String, map_tuple_storage, indexes<String, int>,  traits<random_access_trait, size_trait, filter_trait, mono_dim_filter_trait>>),
          (n_indexed<String, map_tree_storage, indexes<String, int>,  traits<random_access_trait, size_trait, filter_trait, mono_dim_filter_trait>>))
{
	using Container = TestType;
	Container c;

	c("A", 1) = "aze";
	c("A", 2) = "rty";
	c("B", 1) = "tyu";
	c("B", 2) = "uio";
	c("BA", 1) = "tyu";
	c("BA", 2) = "uio";

	SECTION("filter by value") {
		auto c2 = c.template filter_dim<0>("BA");
		auto c3 = c.template filter_dim<1>(1);

		REQUIRE(c2.size() == 2);
		REQUIRE(c3.size() == 3);

		REQUIRE(c2.at("BA", 1) == "tyu");
		REQUIRE(c2.at("BA", 2) == "uio");

		REQUIRE(c3.at("A", 1) == "aze");
		REQUIRE(c3.at("B", 1) == "tyu");
		REQUIRE(c3.at("BA", 1) == "tyu");
	}


	SECTION("filter by predicat") {
		auto c2 = c.template filter_dim<0>([](const String& index) {return index[0] == 'B'; });

		REQUIRE(c2.size() == 4);

		REQUIRE(c2.at("B", 1) == "tyu");
		REQUIRE(c2.at("B", 2) == "uio");
		REQUIRE(c2.at("BA", 1) == "tyu");
		REQUIRE(c2.at("BA", 2) == "uio");
	}

	SECTION("filter by ranges") {
		auto rg = { "B", "BA" };
		auto c2 = c.template filter_dim<0>(rg);

		REQUIRE(c2.size() == 4);

		REQUIRE(c2.at("B", 1) == "tyu");
		REQUIRE(c2.at("B", 2) == "uio");
		REQUIRE(c2.at("BA", 1) == "tyu");
		REQUIRE(c2.at("BA", 2) == "uio");
	}

}

TEMPLATE_TEST_CASE("RandomAccessTrait/filter/Size", "[]",
          (n_indexed<int, map_tuple_storage, indexes<String, String, String>,  traits<random_access_trait, size_trait, filter_trait>>),
          (n_indexed<int, map_tree_storage, indexes<String, String, String>,  traits<random_access_trait, size_trait, filter_trait>>))
{
	using Container = TestType;
	Container c;

	c("using", "namespace", "NIndexedContainer") = 1;
	c("using", "Container", "NIndexed") = 2;
	c("int", "MapStorage", "Indexes") = 3;
	c("String", "String", "String") = 4;
	c("Traits", "S_RandomAccessTrait", "FilterTrait") = 5;

	SECTION("filter by value/All") {
		auto c2 = c.filter("using", criterion_all{}, criterion_all{});
		REQUIRE(c2.size() == 2);
		REQUIRE(c2.at("using", "namespace", "NIndexedContainer") == 1);
		REQUIRE(c2.at("using", "Container", "NIndexed") == 2);
	}

	SECTION("filter by predicat") {
		auto c2 = c.filter(
			[](const String& str) { return str[0] == 'S' || str[0] == 'T'; },
			[](const String& str) { return str[0] == 'S'; },
			[](const String& str) { return str[0] == 'F'; });

		REQUIRE(c2.at("Traits", "S_RandomAccessTrait", "FilterTrait") == 5);
		REQUIRE(c2.size() == 1);
	}

	SECTION("filter by range") {
		auto c2 = 
			c.filter(
				range{ "int", "using" }, 
				range{ "namespace", "MapStorage" }, 
				range{ "Indexes" });

		REQUIRE(c2.at("int", "MapStorage", "Indexes") == 3);
		REQUIRE(c2.size() == 1);
	}

}

TEMPLATE_TEST_CASE("RandomAccessTrait/slice/Size", "[]",
           (n_indexed<int, map_tuple_storage, indexes<String, int, int>,  traits<random_access_trait, size_trait, slice_trait>>),
           (n_indexed<int, map_tree_storage, indexes<String, int, int>,  traits<random_access_trait, size_trait, slice_trait>>))
{
	using Container = TestType;
	Container c;

	c("a", 1, 0) = 1;
	c("b", 1, 0) = 2;
	c("a", 0, 0) = 3;
	c("b", 0, 0) = 4;
	c("a", 1, 1) = 5;
	c("b", 1, 1) = 6;
	c("a", 0, 1) = 7;
	c("b", 0, 1) = 8;

	SECTION("Slice on first Index") {
		auto c2 = c.template slice<0>("b");

		REQUIRE(c2.size() == 4);
		REQUIRE(c2.at(1, 0) == 2);
		REQUIRE(c2.at(0, 0) == 4);
		REQUIRE(c2.at(1, 1) == 6);
		REQUIRE(c2.at(0, 1) == 8);
	}

	SECTION("Slice on second Index") {
		auto c2 = c.template slice<1>(1);

		REQUIRE(c2.size() == 4);
		REQUIRE(c2.at("a", 0) == 1);
		REQUIRE(c2.at("b", 0) == 2);
		REQUIRE(c2.at("a", 1) == 5);
		REQUIRE(c2.at("b", 1) == 6);
	}

	SECTION("Slice on third Index") {
		auto c2 = c.template slice<2>(1);
		REQUIRE(c2.size() == 4);
		REQUIRE(c2.at("a", 1) == 5);
		REQUIRE(c2.at("b", 1) == 6);
		REQUIRE(c2.at("a", 0) == 7);
		REQUIRE(c2.at("b", 0) == 8);
	}

	SECTION("Empty Slice raise exception") {
		
		bool did_raise_exception;

		try {
			// Nothing match, slice should throw an exception
			auto c2 = c.template slice<0>("ee");
			did_raise_exception = false;
		}
		catch (empty_slice_exception&)
		{
			did_raise_exception = true;
		}

		REQUIRE(did_raise_exception == true);
	}
}

TEMPLATE_TEST_CASE("Iterator", "[]",
	    (n_indexed<String, map_tuple_storage, indexes<int, char, String>,  traits<random_access_trait, size_trait, iterable_trait>>),
        (n_indexed<String, map_tree_storage, indexes<int, char, String>,  traits<random_access_trait, size_trait, iterable_trait>>))
{	
	using Container = TestType;
	Container c;

	c(0, 'a', "A") = "0, a, A";
	c(0, 'a', "B") = "0, a, B";
	c(0, 'b', "C") = "0, b, C";
	c(0, 'b', "D") = "0, b, D";
	c(1, 'c', "E") = "1, c, E";
	c(1, 'c', "F") = "1, c, F";
	c(1, 'd', "G") = "1, d, G";
	c(1, 'd', "H") = "1, d, H";
		
	SECTION("Begin, end") {
		REQUIRE(c.begin() == c.begin());
		REQUIRE(c.end() == c.end());
	}

	SECTION("for : ") {
		Size_t count{ 0u };

		// Indexes and value match
		for (const auto& ord: c) {
			REQUIRE(
				std::apply(
					[&c](auto ...x) {return c.at(x...); },
                    tuple_without_last_view(ord)) == tuple_last(ord));
			count++;
		}

		// Everything was read
		REQUIRE(count == c.size());
	}

	SECTION("Empty container iterator") {
		Container c2;

		auto begin = c2.begin();
		auto end = c2.end();

		REQUIRE(end == begin);
		
		bool empty = true;
		for (const auto& x: c2)
			empty = false;
		REQUIRE(empty == true);
	}	

}

template <typename T1, typename T2> 
struct type_pair {
	using T_first = T1;
	using T_second = T2;
};

TEMPLATE_TEST_CASE("Copy with different trait", "[]",
		(type_pair<
			n_indexed<int, map_tuple_storage, indexes<int, char, char>,  traits<random_access_trait>>,
			n_indexed<int, map_tuple_storage, indexes<int, char, char>,  traits<random_access_trait, iterable_trait, apply_trait, size_trait>>>
		),
        (type_pair<
        	n_indexed<int, map_tree_storage, indexes<int, char, char>,  traits<random_access_trait>>,
        	n_indexed<int, map_tree_storage, indexes<int, char, char>,  traits<random_access_trait, iterable_trait, apply_trait, size_trait>>>)
        )
{
	using ContainerFrom = typename TestType::T_first;
	using ContainerTo = typename TestType::T_second;

	ContainerFrom from;

	from(0, 'a', 'A') = 1;
	from(0, 'a', 'B') = 2;
	from(0, 'b', 'C') = 3;
	from(0, 'b', 'D') = 4;
	from(1, 'c', 'E') = 5;
	from(1, 'c', 'F') = 6;
	from(1, 'd', 'G') = 7;
	from(1, 'd', 'H') = 8;

	ContainerTo to = from;

	REQUIRE(8 == to.size());

	for (const auto& ord : to) {
		REQUIRE(
			std::apply(
				[&from](auto ...x) {return from.at(x...); },
                tuple_without_last_view(ord)) == tuple_last(ord));
	}

	to(0, 'a', 'A') = 42;
	REQUIRE(from(0, 'a', 'A') == 1);

	std::map<String, String> mm;
	
}

