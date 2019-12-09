
#include "catch.hpp"

#include <iostream>
#include <Eigen/Dense>
#include "../Details/tuple_helper.hpp"

#include "../Implem/map_tree/map_tree.hpp"
#include "../Implem/slice_view/slice_view.hpp"
#include "../Implem/eigen_matrix/eigen_matrix.hpp"
#include "../Implem/boost_multi_array/boost_multi_array.hpp"
#include "../Implem/MDX_emitter/MDX_emitter.hpp"

TEST_CASE("Sandbox : Eigen")
{
	using namespace NIndexedContainer; 

	using container = 
		n_indexed<
			int,
			eigen_matrix_storage,
			indexes<int, unsigned int>,
			traits<size_trait, random_access_trait, apply_trait, shape_trait, iterable_trait, slice_trait>,
			storage_properties<
				static_dimensions<10, 10>
			>>;

	container c;
	container c2{c};

	REQUIRE(c.size() == 100);

    c(1,2) = 22;
    c(2,3) = 23;

    REQUIRE(c(1, 2) == 22);
    
    REQUIRE(c(2, 3) == 23);

    c.apply([](auto& x){ x = 2*x;});

    REQUIRE(c(1, 2) == 22 * 2);
    REQUIRE(c(2, 3) == 23 * 2);

    int i =0;
    c.apply([&i](auto& x){ x = i++;});

    // Ref test
    auto& ref = c(3, 4);
    auto idx = std::make_tuple(3, 4);


    auto count = 0u;
    for (auto ord : c) {
        tuple_last(ord) = 444;
        count++;
    }

    REQUIRE(c(3,4) == 444);
    REQUIRE(count == c.size());

    //
    for (auto i = 0u; i < 10; i++)
        c(i, 0) = i;

    auto first_column = c.slice<1>(0);

    REQUIRE(first_column.size() == 10);

    for (auto i = 0u; i < 10; i++)
        REQUIRE(first_column(i) == i);

}


template <typename T1, typename T2>
void test(T1 a, T2 b)
{
    REQUIRE(a == b);
}


TEST_CASE("okok") 
{

    using namespace NIndexedContainer;

    using Tcontainer =
            n_indexed<
                    int,
                    eigen_matrix_storage ,
                    indexes<int>,
                    traits<size_trait, random_access_trait>,
                    storage_properties<static_dimensions<10>>
                    >;

    Tcontainer c{};

    REQUIRE(c.size() == 10);

    for (auto i = 0; i < 10; i++)
        c(i) = i;

    for (auto i = 0; i < 10; i++)
        REQUIRE(c(i) == i);

}


TEST_CASE("Sandbox : Eigen op")
{
    using namespace NIndexedContainer;
    using Tcontainer =
            n_indexed<
                    int,
                    eigen_matrix_storage ,
                    indexes<int, int>,
                    traits<size_trait, random_access_trait, sum_trait, shape_trait>,
                    storage_properties<static_dimensions<10, 10>>
                    >;


    Tcontainer x, y;
    Tcontainer z =  x+y;
    Tcontainer t;

    REQUIRE(t.size() == 100);

    t = x+y;

    


    z.shape(); 
    REQUIRE(z.size() == 100);
}


//

template <typename Tcontainer>
int count(const Tcontainer& c)
{
    int size{0};
    for (const auto& _ : c) size++;
    return size;
}

//

TEST_CASE("kk")
{
    using namespace NIndexedContainer;


    using c_map_tree = 
        n_indexed<
            double, 
            map_tree_storage, 
            indexes<int, int, int>,
            traits<iterable_trait, random_access_trait>
        >;


    using c_boost = 
        n_indexed<
            double, 
            boost_multi_array_storage, 
            indexes<int, int, int>,
            traits<iterable_trait, random_access_trait>
        >;


    c_map_tree map;
    c_boost boost{10, 10, 10};


    //const int a = count(map);
    //const int b = count(boost);
}

TEST_CASE("")
{
    using namespace NIndexedContainer;
    using Tcontainer = 
        n_indexed<
            double, 
            eigen_matrix_storage,
            indexes<
                int, int
            >,
            traits<
                random_access_trait, 
                size_trait
            >,
            storage_properties<
//                dimensions<dynamic_dim, dynamic_dim>
            >
        >;

    Tcontainer x{10, 10};   

}


namespace NIndexedContainer {


    template <typename T1, typename T2>
    void transfert(const iterable_trait<T1>& from, random_access_trait<T2>& to)
    {
        for (const auto ord : from)
            std::apply(
                [value = tuple_last(ord), &to](const auto& ...idx){ 
                    to(idx...) = value;
                },
                tuple_without_last_view(ord));
    }

}


TEST_CASE("TRANSFERT")
{
    using namespace NIndexedContainer;

    using Tfrom = 
        n_indexed<
            double, 
            boost_multi_array_storage,
            indexes<int, int, int>,
            traits<random_access_trait, iterable_trait, size_trait>
        >;

    using Tto = 
        n_indexed<
            double, 
            map_tree_storage,
            indexes<int,int,int>,
            traits<random_access_trait, size_trait>
        >;

    Tfrom from{10, 10, 10};
    Tto to;

    REQUIRE(to.size() == 0);
    transfert(from, to);
    REQUIRE(from.size() == to.size());
    REQUIRE(1000 == to.size());
}



TEST_CASE("slice_view")
{
    using namespace NIndexedContainer;

    using Tcontainer = 
        n_indexed<
            int, 
            boost_multi_array_storage,
            indexes<int, int, int>,
            traits<
                random_access_trait, 
                iterable_trait, 
                size_trait, 
                slice_trait, slice_view_trait>>;

    Tcontainer c{10, 10, 10};

    for (auto ord : c) tuple_last(ord) = 0;

    auto slice_view = c.slice_view<0>(4);    // première index = 4
    auto slice = c.slice<0>(4);

    REQUIRE(c.size() == 1000);
    REQUIRE(slice_view.size() == 100);

    REQUIRE( &(slice_view(1, 1)) == &(c(4, 1, 1)));  // slice_view est bien une vue !
    REQUIRE( &(slice_view(1, 2)) == &(c(4, 1, 2)));
    REQUIRE( &(slice_view(3, 5)) == &(c(4, 3, 5)));

    REQUIRE( &(slice(1, 1)) != &(c(4, 1, 1)));  // mais pas slice
    REQUIRE( &(slice(1, 2)) != &(c(4, 1, 2)));
    REQUIRE( &(slice(3, 5)) != &(c(4, 3, 5)));


    for (auto _ : c.slice_view<0>(0)) tuple_last(_) = 1; 

    REQUIRE( c(0, 2, 3) == 1);

    auto v = c.slice_view<0>(0).slice_view<0>(0);

    REQUIRE(v.size() == 10);


    v(0) = 1;
}

template <typename T>
struct display_type;

TEST_CASE("zfe")
{
    using namespace NIndexedContainer;

    using container_type = 
        n_indexed<
            int, 
            eigen_matrix_storage, 
            indexes<int, int>,
            traits<random_access_trait, size_trait, apply_trait>>;
    //

    container_type matrix{10, 10};

    {
        int i = 0;
        matrix.apply([&i](auto& x){x = i++;});
    }

    auto view = make_slice_view<0>(matrix, 1);

    REQUIRE(view(0) == matrix(1, 0));
    REQUIRE(view(1) == matrix(1, 1));
    REQUIRE(view(2) == matrix(1, 2));

    view(2) = 9;
    REQUIRE(view(2) == 9);
    REQUIRE(&(view(2)) == &(matrix(1, 2)));
}



TEST_CASE("MDX")
{

    using namespace NIndexedContainer;

    using Tcontainer = 
        n_indexed<
            int,
            MDX_emitter_storage,
            indexes<int, int, int>,
            traits<slice_trait, filter_trait>>;

    

    Tcontainer c;

    // Initialization 


    c._name = "CUBE";
    c._dimensions[0].name = "TIME";
    c._dimensions[1].name = "PLACE";
    c._dimensions[2].name = "PRODUCT";

    //  Querys 

    c.slice<1>(42);

    //

    std::cout << std::endl;

    //c.filter(criterion_all{}, 42, criterion_all{});
}   

