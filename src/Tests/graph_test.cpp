
#include <string>

#include "catch.hpp"
#include "../Interface/range.hpp"
#include "../Implem/graph/graph.hpp"

#include "../Logger/logger.hpp"

using String = std::string;

TEST_CASE("GRAPH RandomAccess/Size", ""){

	using namespace NIndexedContainer;
	using Container = 
		n_indexed<
			int, 
			graph_storage, 
			dynamic_indexes, 
			traits<random_access_trait, size_trait>>;

	Container c;

	SECTION("Node Contain a value") {
		REQUIRE(c.size() == 1);
		c() = 42;
		REQUIRE(c() == 42);
		REQUIRE(c.at() == 42);
		REQUIRE(c.size() == 1);
	}

	SECTION("Node Creation with only int") {

		// Create 3 nodes
		REQUIRE(c.size() == 1);
		c() = 42;
		REQUIRE(c.size() == 1);
		c(0) = 43;
		REQUIRE(c.size() == 2);
		c(0, 0) = 44;
		REQUIRE(c.size() == 3);
		c(0, 1) = 45;
		REQUIRE(c.size() == 4);
		
		// Change Node
		c(0, 0) = 46;
		REQUIRE(c.size() == 4);

		// Check values
		REQUIRE(c.at() == 42);
		REQUIRE(c.at(0) == 43);
		REQUIRE(c.at(0, 0) == 46);
		REQUIRE(c.at(0, 1) == 45);
	}

	SECTION("Node Creation with mixed index types", "") {
		// Create 3 nodes
		REQUIRE(c.size() == 1);
		c() = 42;
		REQUIRE(c.size() == 1);
		c(0) = 43;
		REQUIRE(c.size() == 2);
		c(0, "0" ) = 44;
		REQUIRE(c.size() == 3);
		c("0", 1) = 45;
		REQUIRE(c.size() == 5);

		// Change Node
		c(0, "0") = 46;
		REQUIRE(c.size() == 5);

		// Check values
		REQUIRE(c.at() == 42);
		REQUIRE(c.at(0) == 43);
		REQUIRE(c.at(0, "0") == 46);
		REQUIRE(c.at("0", 1) == 45);
	}

}

TEST_CASE("Graph RandomAccess/Size/Insert", "") {

	using namespace NIndexedContainer;
	using Container =
		n_indexed<
		int,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, size_trait, insert_trait>>;

	Container c;

	c(0, 'a') = 1;
	c(1, 'b') = 2;
	c(2) = 3;

	REQUIRE(c.size() == 6);

	SECTION("Insert Node with 1 paths") {
		c.insert(42, std::make_tuple(0, 'a', 43));
		REQUIRE(c.size() == 7);
		REQUIRE(c.at(0, 'a', 43) == 42);
		REQUIRE(c.at(0, 'a') == 1);
		REQUIRE(c.at(1, 'b') == 2);
		REQUIRE(c.at(2) == 3);
	}

	SECTION("Insert Node with 2 paths + copy") {

		c.insert(
			42,
			std::make_tuple(0, 'a', "z"), 
			std::make_tuple(1, 'b', 23));

		// Previous value are still here
		REQUIRE(c.size() == 7);
		REQUIRE(c.at(0, 'a') == 1);
		REQUIRE(c.at(1, 'b') == 2);
		REQUIRE(c.at(2) == 3);

		// Value was inserted
		REQUIRE(c.at(0, 'a', "z") == 42);
		REQUIRE(c.at(1, 'b', 23) == 42);

		// Value are corectly linked

		c.at(0, 'a', "z")++;
		REQUIRE(c.at(0, 'a', "z") == 43);
		REQUIRE(c.at(1, 'b', 23) == 43);
	}

	SECTION("Node Creation with variable, overlaped path") {

		c.insert(
			42,
			std::make_tuple(0, 2),
			std::make_tuple(1, 2),
			std::make_tuple(1, 'b', 2),
			std::make_tuple(6)
		);

		// Previous value are still here
		REQUIRE(c.size() == 7);
		REQUIRE(c.at(0, 'a') == 1);
		REQUIRE(c.at(1, 'b') == 2);
		REQUIRE(c.at(2) == 3);

		REQUIRE(c.at(0, 2) == 42);
		REQUIRE(c.at(1, 2) == 42);
		REQUIRE(c.at(1, 'b', 2) == 42);
		REQUIRE(c.at(6) == 42);

		// Value are corectly linked

		c(6)++;

		REQUIRE(c.at(0, 2) == 43);
		REQUIRE(c.at(1, 2) == 43);
		REQUIRE(c.at(1, 'b', 2) == 43);
		REQUIRE(c.at(6) == 43);
	}

}

TEST_CASE("Graph RandomAccess/Size/Insert/Apply")
{
	using namespace NIndexedContainer;
	using Container =
		n_indexed<
		String,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, size_trait, apply_trait, insert_trait>>;

	Container c;

	SECTION("", "apply sufix") {
		c(0, "zaza") = "hello";
		c("ze", 1, 3) = "sss";

		c.insert(
			"hallo",
			std::make_tuple(0, "zaza", 2),
			std::make_tuple("ze", 1, 3, 4));

		c.apply([](String& str) { str += "-1"; });
		REQUIRE(c.at(0, "zaza") == "hello-1");
		REQUIRE(c.at("ze", 1, 3) =="sss-1");
		REQUIRE(c.at() == "-1");
		REQUIRE(c.at(0) == "-1");
		REQUIRE(c.at("ze") == "-1");
		REQUIRE(c.at("ze", 1) == "-1");
		REQUIRE(c.at("ze", 1, 3, 4) == "hallo-1");
		REQUIRE(c.at(0, "zaza", 2) == "hallo-1");
	}

}

TEST_CASE("Graph deep copy") {
	using namespace NIndexedContainer;
	using Container =
		n_indexed<
		int,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, size_trait, insert_trait>>;

	using Container2 =
		n_indexed<
		int,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, size_trait, apply_trait>>;

	Container c;

	c() = 13;

	c.insert(
		42,
		std::make_tuple(0),
		std::make_tuple(1),
		std::make_tuple(2));

	c.insert(
		43,
		std::make_tuple(0, 'a'),
		std::make_tuple('3'));

	c.insert(
		44,
		std::make_tuple(0, 'a', "b"),
		std::make_tuple(4));

	SECTION("Deep copy, same type") {
		Container c2{ c };

		// Check that values were copied
		REQUIRE(c.size() == c2.size());
		REQUIRE(c.at() == c2.at());
		REQUIRE(c.at(0) == c2.at(0));
		REQUIRE(c.at(1) == c2.at(1));
		REQUIRE(c.at(2) == c2.at(2));
		REQUIRE(c.at(0, 'a') == c2.at(0, 'a'));
		REQUIRE(c.at('3') == c2.at('3'));
		REQUIRE(c.at(0, 'a', "b") == c2.at(0, 'a', "b"));
		REQUIRE(c.at(4) == c2.at(4));

		// Check that copy is independent

		c(0) = 68; // change original

		// Copy is still the same
		REQUIRE(c2.at(0) == 42);
		REQUIRE(c2.at(1) == 42);
		REQUIRE(c2.at(2) == 42);

		// again :
		c(0, 'a', "b") = 32;

		REQUIRE(c2.at(0, 'a', "b") == 44);

		// Check that copy is corectly linked
		c2.at(0, 'a') = 33;
		REQUIRE(c2.at('3') == 33);
	}

	SECTION("Deep copy, different traits_holder") {
		Container2 c2{ c };

		// Check that values were copied
		REQUIRE(c.size() == c2.size());
		REQUIRE(c.at() == c2.at());
		REQUIRE(c.at(0) == c2.at(0));
		REQUIRE(c.at(1) == c2.at(1));
		REQUIRE(c.at(2) == c2.at(2));
		REQUIRE(c.at(0, 'a') == c2.at(0, 'a'));
		REQUIRE(c.at('3') == c2.at('3'));
		REQUIRE(c.at(0, 'a', "b") == c2.at(0, 'a', "b"));
		REQUIRE(c.at(4) == c2.at(4));

		// Check that copy is independent

		c(0) = 68; // change original

		// Copy is still the same
		REQUIRE(c2.at(0) == 42);
		REQUIRE(c2.at(1) == 42);
		REQUIRE(c2.at(2) == 42);

		// again :
		c(0, 'a', "b") = 32;

		REQUIRE(c2.at(0, 'a', "b") == 44);

		// Check that copy is corectly linked
		c2.at(0, 'a') = 33;
		REQUIRE(c2.at('3') == 33);

		// Use new trait
		c2.apply([](int& x) { x *= 2; });
		REQUIRE(c2.at(0, 'a') == 66);
		REQUIRE(c2.at(0) == 84);
		REQUIRE(c2.at(1) == 84);
		REQUIRE(c2.at(2) == 84);
	}
}

TEST_CASE("Graph MakeEdge") {

	using namespace NIndexedContainer;
	using Container =
		n_indexed<
		int,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, size_trait, create_edge_trait>>;

	Container c;

	// Create 3 branches

	c(1, 2, 3) = 1;
	c('1', '2', '3') = 2;
	c("1", "2", "3") = 3;

	REQUIRE(c.size() == 10);

	SECTION("MakeEdge") {

		c.create_edge(
			"edge",
			std::make_tuple(1, 2, 3),
			std::make_tuple('1', '2', '3')
		);

		// Check the link
		REQUIRE(c.at(1, 2, 3, "edge") == 2);

		c(1, 2, 3, "edge") = 42;
		REQUIRE(c.at('1', '2', '3') == 42);
		
		// Edge doesnt change size
		REQUIRE(c.size() == 10);
	}

	SECTION("MakeEdge : test cycle detection") {

		bool exception_was_raised = false;

		try {
			c.create_edge(
				"o",
				std::make_tuple(1, 2, 3),
				std::make_tuple(1));
		}
		catch (std::logic_error&)
		{
			exception_was_raised = true;
		}

		REQUIRE(exception_was_raised == true);
	}
}


TEST_CASE("Graph filter")
{
	using namespace NIndexedContainer;
	using container =
		n_indexed<
		String,
		graph_storage,
		dynamic_indexes,
		traits<random_access_trait, insert_trait, size_trait, filter_trait>>;

	container c;

	c() = "root";
	c(0) = "A";
	c(2) = "E";

	c.insert("C",
		std::make_tuple(0, 4),
		std::make_tuple(1),
		std::make_tuple(2, 5));

	c.insert("D",
		std::make_tuple(1, 6),
		std::make_tuple(3));

	c.insert("B",
		std::make_tuple(0, 11),
		std::make_tuple(1, 12));

	REQUIRE(c.size() == 6);

	SECTION("Graph filter 1") {
		auto c2 = c.filter(criterion_all{}, range{4, 5});

		REQUIRE(c2.size() == 4);
		REQUIRE(c2.at() == "root");
		REQUIRE(c2.at(0) == "A");
		REQUIRE(c2.at(0, 4) == "C");
		REQUIRE(c2.at(2) == "E");
		REQUIRE(c2.at(2, 5) == "C");


		// Check link
		REQUIRE(&(c2.at(0, 4)) == (&(c2.at(2, 5))));
	
		bool exception_was_raise = false;

		try {
			c2.at(1);
		}
		catch (...)
		{
			exception_was_raise = true;
		}

		REQUIRE(exception_was_raise == true);
	}

    SECTION("Graph filter 1") {
        auto c2 = c.filter(
                criterion_all{},
                [](const auto& x)
                {
                    if constexpr (std::is_convertible_v<std::decay_t<decltype(x)>, int> )
                        return x == 4 || x == 5;
                    else
                        return false;
                });

        REQUIRE(c2.size() == 4);
        REQUIRE(c2.at() == "root");
        REQUIRE(c2.at(0) == "A");
        REQUIRE(c2.at(0, 4) == "C");
        REQUIRE(c2.at(2) == "E");
        REQUIRE(c2.at(2, 5) == "C");


        // Check link
        REQUIRE(&(c2.at(0, 4)) == (&(c2.at(2, 5))));

        bool exception_was_raise = false;

        try {
            c2.at(1);
        }
        catch (...)
        {
            exception_was_raise = true;
        }

        REQUIRE(exception_was_raise == true);
    }


}

