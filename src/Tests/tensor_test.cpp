
#include "catch.hpp"
#include "../Implem/boost_multi_array/boost_multi_array.hpp"
#include "../Logger/logger.hpp"
#include "../Details/tuple_helper.hpp"


TEST_CASE("Tensor, size/random access")
{
    using namespace NIndexedContainer;
    using Tensor =
            n_indexed<int, boost_multi_array_storage, indexes<int, int>, traits_holder<random_access_trait, size_trait>>;

    Tensor matrix{3, 3};

    SECTION("Read write") {
        matrix(0, 0) = 22;
        matrix(1, 2) = 42;

        REQUIRE(matrix.at(0, 0) == 22);
        REQUIRE(matrix.at(1, 2) == 42);
    }

    SECTION("Size") {
        REQUIRE(matrix.size() == 9);
    }
}

TEST_CASE("Tensor, size/random access/iterable")
{
    using namespace NIndexedContainer;
    using Tensor =
        n_indexed<
        int,
        boost_multi_array_storage,
        indexes<int, int, int>,
        traits_holder<random_access_trait, size_trait, iterable_trait>>;

    Tensor matrix{42, 8, 23};

    for (auto i = 0u; i < 42; i++)
        for (auto j = 0u; j < 8; j++)
            for (auto k = 0u; k < 23; k++)
                matrix(i,j,k) = i + 2*j + 4*k;

    REQUIRE(matrix.size() == 42*8*23);

    SECTION("for : read") {
        Size_t count{ 0u };

        // Indexes and value match
        for (const auto& ord: matrix) {
            REQUIRE(
                    std::apply(
                            [&matrix](auto ...x) {return matrix.at(x...); },
                            tuple_without_last_view(ord)) == tuple_last(ord));
            count++;
        }

        // Everything was read
        REQUIRE(count == matrix.size());
    }

    SECTION("for : write") {
        Size_t count{0u};

        for (auto ord: matrix) {
            tuple_last(ord) = count;
            count++;
        }

        count = 0u;
        for (const auto ord: matrix) {
            REQUIRE(tuple_last(ord) == count);
            count++;
        }
    }

}

TEST_CASE("Tensor, size/random access/apply")
{
    using namespace NIndexedContainer;
    using Tensor =
        n_indexed<int, boost_multi_array_storage, indexes<int, int, int>, traits_holder<random_access_trait, size_trait, apply_trait>>;

    Tensor matrix{42, 8, 23};

    SECTION("Size apply match")
    {
        std::size_t s = 0u;
        matrix.apply([&s](const int&) {s++;});
        REQUIRE(s == matrix.size());
    }

    SECTION("Apply can change content")
    {
        matrix(1,2,3) = 42;
        matrix(1,1, 1) = 9;
        matrix.apply([](int& x) {x++;});

        REQUIRE(matrix(1, 2, 3) == 43);
        REQUIRE(matrix(1, 1, 1) == 10);
    }
}

TEST_CASE("Tensor, size/random access/slice")
{
    using namespace NIndexedContainer;
    using Tensor =
        n_indexed<int, boost_multi_array_storage, indexes<int, int, int>, traits_holder<random_access_trait, size_trait, slice_trait>>;

    Tensor tensor{10, 10, 10};

    //auto slice = tensor._storage[indices[]];

    tensor(0, 2, 0) = 1;;
    tensor(3, 2, 1) = 2;
    tensor(1, 2, 3) = 3;

    SECTION("slice")
    {
        auto slice = tensor.slice<1>(2);

        REQUIRE(tensor.size() == 10*10*10);
        REQUIRE(slice.size() == 10*10);
        REQUIRE(slice(0, 0) == 1);
        REQUIRE(slice(3, 1) == 2);
        REQUIRE(slice(1, 3) == 3);
    }

}

TEST_CASE("tensor deep copy/random access/apply_trait/iterable_trait")
{
    using namespace NIndexedContainer;
    using Tensor =
            n_indexed<
                    int, boost_multi_array_storage, indexes<int, int, int, int>,
                    traits_holder<random_access_trait, size_trait, apply_trait, iterable_trait>>;

    Tensor tensor{10, 2, 14, 3};

    {
        int i = 0;
        tensor.apply([&i](int& x) {x = i++;} );
    }

    SECTION("deep copy")
    {
        Tensor tensor2{tensor};

        // Same size
        REQUIRE(tensor.size() == tensor2.size());

        // Really a deep copy
        REQUIRE(&(tensor(0, 0, 0, 0)) != &(tensor2(0, 0, 0, 0)));

        // Same content
        for (const auto& ord: tensor) {
            REQUIRE(
                    std::apply(
                            [&tensor2](auto ...x) {return tensor2.at(x...); },
                            tuple_without_last_view(ord)) == tuple_last(ord));
        }
    }
}
