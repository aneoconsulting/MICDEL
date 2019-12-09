

#include "catch.hpp"
#include "../Implem/map_tree/map_tree.hpp"
#include "../Logger/logger.hpp"

#include <iostream>

TEST_CASE("Logger") {

    using namespace NIndexedContainer;
    using container =
            n_indexed<
                    int,
                    map_tree_storage,
                    indexes<int, int, int>,
                    traits<size_trait, random_access_trait, remove_trait, apply_trait, iterable_trait, slice_trait>>;

    container c;

    c.size();

    c(3, 4, 5);
    c(1, 2, 3);
    const auto x = c.at(3, 4, 5);
    c.at(1, 2, 3) = 3;
    c.apply([](auto&){});
    c.remove(1,2,3);

    BEGIN_SECTION("section 8")
    c.begin();

        BEGIN_SECTION("section 3")
    c.end();

        END_SECTION()

    END_SECTION()


    auto y = c.slice<1>(4);
}

