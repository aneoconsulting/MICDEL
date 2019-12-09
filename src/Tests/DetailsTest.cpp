
#include "catch.hpp"
#include "../Details/value_record.hpp"
#include "../Details/impl_helper.hpp"
#include "../Details/tuple_counter.hpp"
#include "../Interface/apply_trait.hpp"
#include "../Interface/mono_dim_filter_trait.hpp"
#include "../Interface/size_trait.hpp"
#include "../Interface/range.hpp"

#include <iostream>

using namespace NIndexedContainer;

TEST_CASE("Implementation Helper") {

    SECTION("is_predicate") {
        static_assert(is_predicate_v<int, int> == false);
        static_assert(is_predicate_v<bool(int), int> == true);
        static_assert(is_predicate_v<bool(const int&), int> == true);

        auto f1 = [](int i){return i == 4;};
        auto f2 = [](const auto &x) {return x == 42;};

        static_assert(is_predicate_v<decltype(f1), int>);
        static_assert(is_predicate_v<decltype(f2), int>);
        static_assert(is_predicate_v<decltype(f2), float>);
    }

    SECTION("range_trait") {
        static_assert(is_range_v<int> == false);
        static_assert(is_range_v<std::vector<int>> == true);

        const auto x = { "e", "zre", "kjf", "lk,df" };
        static_assert(is_range_v<decltype(x)> == true);

        static_assert(is_range_v<range<int, 3>> );
        static_assert(is_range_v<decltype(range{3, 4, 9})>);

        auto y = range{"a", "b", "c"};
        static_assert(is_range_v<decltype(y)>);
    }

    SECTION("contains_trait") {
        static_assert(contains_trait_v < apply_trait, traits_holder<apply_trait, mono_dim_filter_trait, filter_trait>>);
        static_assert(contains_trait_v < apply_trait, traits_holder<mono_dim_filter_trait, apply_trait, filter_trait>>);
        static_assert(contains_trait_v < apply_trait, traits_holder<mono_dim_filter_trait, filter_trait, apply_trait>>);
        static_assert(contains_trait_v < size_trait, traits_holder<mono_dim_filter_trait, filter_trait, apply_trait>> == false);
    }
}

TEST_CASE("ValueRecord", "") {
    value_record x{42};
	value_record y{ "string" };

	SECTION("apply") {
		REQUIRE(apply([](const auto& v) {return sizeof(v); }, x) == sizeof(int));
		REQUIRE(apply([](const auto& v) {return sizeof(v); }, y) == sizeof(String));

		auto f = [](const auto&) {return int{};};
        static_assert(std::is_same_v<decltype(apply(f, x)), int>);
	}

	SECTION("equal") {
		REQUIRE(equal(x, 42) == true);
		REQUIRE(equal(x, 43) == false);
		REQUIRE(equal(y, String{"string"}) == true);
		REQUIRE(equal(y, String{"strinG"}) == false);
	}

	SECTION("asVariant") {
		const auto vx = as_variant(x);
		const auto vy = as_variant(y);

		REQUIRE(std::get<int>(vx) == 42);
		REQUIRE(std::get<String>(vy) == String{ "string" });
	}

}

TEST_CASE("Criterion match")
{
    auto s = std::string{"hallo"};
    auto x = 42;

    REQUIRE(criterion_match(s, "hallo"));           // String literal
    REQUIRE(criterion_match(s, "hall") == false);
    REQUIRE(criterion_match(s, "halloo") == false);

    REQUIRE(criterion_match(s, s));

    REQUIRE(criterion_match(s, [](const auto& v) { return v[0] == 'h';}));
    REQUIRE(criterion_match(x, [](const auto& v) {return v < 333;}));

    REQUIRE(criterion_match(s, range{"ee", "fd", "hallo"}));
    REQUIRE(criterion_match(x, range{40, 41, 43}) == false);
}

