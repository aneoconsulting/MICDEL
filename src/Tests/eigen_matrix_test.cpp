
#include "catch.hpp"
#include "../Implem/eigen_matrix/eigen_matrix.hpp"
#include "../Details/tuple_helper.hpp"

TEST_CASE("eigen matrix size")
{
	using namespace NIndexedContainer;


	SECTION("Eigen matrix dynamic_dim size")
	{
		using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int, int>,
				traits<size_trait>>;
		
		matrix m{10, 11};

		REQUIRE(m.size() == 10*11);
	}


	SECTION("Eigen matrix dynamic_dim/static_dim size")
	{
		using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int, int>,
				traits<size_trait>,
				storage_properties<
					dimensions<dynamic_dim, static_dim<10>>
				>
			>;

		/*
			Constructor argument are forwarded the eigen internal matrix.

			Actually the eigen matrix consstructor still need both size, even if one is statically fixed, with one exception : 
			if the fixed size is equal to 1, then the matrix is considered as a vector (in this case you should use indexes<int>).
			An eigen runtime assertion will check that the submitted size match the static one.
		
		*/
		
		matrix m
		{
			11, 	
			10		// must be equal to 10 because of static_dim<10>
		};	

		REQUIRE(m.size() == 10*11);
	}


	SECTION("Eigen matrix static_dim/dynamic_dim size")
	{
		using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int, int>,
				traits<size_trait>,
				storage_properties<
					dimensions<static_dim<10>, dynamic_dim>
				>
			>;
		
		matrix m{10, 11};	// again

		REQUIRE(m.size() == 10*11);
	}

	//

	SECTION("Eigen vector dynamic_dim size")
	{
		using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int>,
				traits<size_trait>>;
		
		matrix m{10};

		REQUIRE(m.size() == 10);
	}

	SECTION("Eigen vector static_dim size")
	{
		using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int>,
				traits<size_trait>,
				storage_properties<
					dimensions<static_dim<10>>
				>
			>;
		
		matrix m;

		REQUIRE(m.size() == 10);
	}

}


TEST_CASE("eigen matrix random_access")
{
	using namespace NIndexedContainer;

	using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int, int>,
				traits<size_trait, random_access_trait>
			>;
		
	matrix m{20, 20};

    SECTION("Read write") {
        m(0, 0) = 22;
        m(11, 2) = 42;

    	REQUIRE(m.at(0, 0) == 22);
    	REQUIRE(m.at(11, 2) == 42);
    }
}

TEST_CASE("eigen matrix, random access/apply/foreach/iterable")
{
    using namespace NIndexedContainer;

	using matrix = 
			n_indexed<
				int, 
				eigen_matrix_storage, 
				indexes<int, int>,
				traits<
					random_access_trait, 
					apply_trait, 
					foreach_trait,
					iterable_trait
				>
			>;

	matrix m{20, 20};

	SECTION("apply")
	{
		m.apply([](auto& x) { x = 42;});


		for (auto i = 0; i < 20; ++i) {
			for (auto j = 0; j < 20; ++j) {
				REQUIRE(m.at(i, j) == 42);
			}
		}
	}

	SECTION("foreach")
	{
		m.foreach([](auto i, auto j, auto& x)
		{
			x = i + j;
		});

		for (auto i = 0; i < 20; ++i) {
			for (auto j = 0; j < 20; ++j) {
				REQUIRE(m.at(i, j) == i + j);
			}
		}
	}
}

TEST_CASE("eigen matrix slice/slice_view")
{
	using namespace NIndexedContainer;

	using matrix = 
		n_indexed<
			int, 
			eigen_matrix_storage, 
			indexes<int, int>,
			traits<
				random_access_trait,
				size_trait,
				slice_trait, slice_view_trait
			>
		>;

	matrix m{10, 10};


	SECTION("Slice a matrix by value on axis 0") 
	{
		for (auto i = 0; i < 10; ++i)
			m(2, i) = i;

		auto slice = m.slice<0>(2);

		REQUIRE(slice.size() == 10);
	
		for (auto i = 0; i < 10; ++i)
			REQUIRE(slice.at(i) == i);

		slice(1) = 0;

		// Slice by value : slice and original container are independent
		REQUIRE(slice.at(1) == 0);
		REQUIRE(m.at(2, 1) == 1);
	}

	SECTION("Slice a matrix by value on axis 1") 
	{
		for (auto i = 0; i < 10; ++i)
			m(i, 2) = i;

		auto slice = m.slice<1>(2);

		REQUIRE(slice.size() == 10);
	
		for (auto i = 0; i < 10; ++i)
			REQUIRE(slice.at(i) == i);

		slice(1) = 0;

		// Slice by value : slice and original container are independent
		REQUIRE(slice.at(1) == 0);
		REQUIRE(m.at(1, 2) == 1);
	}

	SECTION("Slice View a matrix on axis 0")
	{
		auto slice_view = m.slice_view<0>(2);

		REQUIRE(slice_view.size() == 10);

		for (auto i = 0; i < 10; ++i)
			REQUIRE(&(slice_view.at(i)) == &(m.at(2, i)));	// view to the same data
	}

	SECTION("Slice View a matrix on axis 1")
	{
		auto slice_view = m.slice_view<1>(2);

		REQUIRE(slice_view.size() == 10);

		for (auto i = 0; i < 10; ++i)
			REQUIRE(&(slice_view.at(i)) == &(m.at(i, 2)));	// view to the same data
	}

}