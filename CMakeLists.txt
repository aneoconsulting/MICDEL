
cmake_minimum_required(VERSION 3.8)

project(n_indexed LANGUAGES CXX )

set(SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(3RDPARTY_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

include(${3RDPARTY_PREFIX}/metabench/metabench.cmake)

option(N_INDEXED_ENABLE_LOGGING "" OFF)
option(N_INDEXED_ENABLE_CONCEPTS "" OFF)
option(N_INDEXED_ENABLE_COMPILE_BENCH "" OFF)
option(N_INDEXED_BUILD_DOC "" OFF)

##  
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#   Documentation
if (N_INDEXED_BUILD_DOC)
    add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/doc")
endif()

################################################################
####														####
####					Sources 							####
####														####
################################################################

#	INTERFACE

set(N_INDEXED_INTERFACE_SRC
    ${SRC_PREFIX}/Interface/apply_trait.hpp
    ${SRC_PREFIX}/Interface/create_edge_trait.hpp
    ${SRC_PREFIX}/Interface/filter_trait.hpp
    ${SRC_PREFIX}/Interface/foreach_trait.hpp
    ${SRC_PREFIX}/Interface/insert_trait.hpp
    ${SRC_PREFIX}/Interface/iterable_trait.hpp
    ${SRC_PREFIX}/Interface/mono_dim_filter_trait.hpp
    ${SRC_PREFIX}/Interface/n_indexed.hpp
    ${SRC_PREFIX}/Interface/random_access_trait.hpp
    ${SRC_PREFIX}/Interface/range.hpp
    ${SRC_PREFIX}/Interface/standard_storage_properties.hpp
    ${SRC_PREFIX}/Interface/remove_trait.hpp
    ${SRC_PREFIX}/Interface/shape_trait.hpp
    ${SRC_PREFIX}/Interface/size_trait.hpp
    ${SRC_PREFIX}/Interface/slice_trait.hpp
    ${SRC_PREFIX}/Interface/slice_view_trait.hpp
    ${SRC_PREFIX}/Interface/stride_trait.hpp
    ${SRC_PREFIX}/Interface/TranslateViewTrait.hpp
    ${SRC_PREFIX}/Interface/sum_trait.hpp
    ${SRC_PREFIX}/Interface/scalar_factor_trait.hpp
    ${SRC_PREFIX}/Interface/store_trait.hpp
    ${SRC_PREFIX}/Interface/store_implicit_convertion_trait.hpp)

#	GRAPH IMPLEMENTATION

set(N_INDEXED_GRAPH_SRC
    ${SRC_PREFIX}/Implem/graph/graph_apply_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph_create_edge_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph_filter_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph.hpp
    ${SRC_PREFIX}/Implem/graph/graph_insert_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph_random_access_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph_size_trait.hpp
    ${SRC_PREFIX}/Implem/graph/graph_storage.hpp)

#	MAP TREE IMPLEMENTATION

set(N_INDEXED_MAP_TREE_SRC
    ${SRC_PREFIX}/Implem/map_tree/map_tree_apply_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_filter_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_foreach_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_iterable_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_random_access_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_remove_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_size_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_slice_trait.hpp
    ${SRC_PREFIX}/Implem/map_tree/map_tree_storage.hpp)

#	MAP TUPLE IMPLEMENTATION

set(N_INDEXED_TUPLE_MAP_SRC
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_apply_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_filter_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_foreach_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_iterable_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_random_access_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_remove_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_size_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_slice_trait.hpp
    ${SRC_PREFIX}/Implem/tuple_map/tuple_map_storage.hpp)

#	BOOST MULTI_ARRAY IMPLEMENTATION

set(N_INDEXED_BOOST_MULTI_ARRAY_SRC
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_storage.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_random_access_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_size_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_iterable_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_apply_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_foreach_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_slice_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_slice_view_trait.hpp
    ${SRC_PREFIX}/Implem/boost_multi_array/boost_multi_array_shape_trait.hpp)

#	EIGEN MATRIX IMPLEMENTATION 

set(N_INDEXED_EIGEN_MATRIX_SRC
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_random_access_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_storage.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_apply_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_size_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_iterable_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_foreach_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_slice_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_slice_view_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_sum_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_shape_trait.hpp
    ${SRC_PREFIX}/Implem/eigen_matrix/eigen_matrix_store_implicit_convertion_trait.hpp)

#   MDX IMPLEMENTATION

set(N_INDEXED_MDX_EMITTER_SRC
    ${SRC_PREFIX}/Implem/MDX_emitter/MDX_emitter_slice_trait.hpp
    ${SRC_PREFIX}/Implem/MDX_emitter/MDX_emitter_filter_trait.hpp
    ${SRC_PREFIX}/Implem/MDX_emitter/MDX_emitter_storage.hpp
    ${SRC_PREFIX}/Implem/MDX_emitter/MDX_emitter.hpp)

#	DETAILS

set(N_INDEXED_DETAILS_SRC
    ${SRC_PREFIX}/Details/log_helpers.hpp
    ${SRC_PREFIX}/Details/impl_helper.hpp
    ${SRC_PREFIX}/Details/storage_properties_helper.hpp
    ${SRC_PREFIX}/Details/string_convertion.cpp
    ${SRC_PREFIX}/Details/string_convertion.hpp
    ${SRC_PREFIX}/Details/singleton.hpp
    ${SRC_PREFIX}/Details/tuple_helper.hpp
    ${SRC_PREFIX}/Details/tuple_counter.hpp
    ${SRC_PREFIX}/Details/type_def.hpp
    ${SRC_PREFIX}/Details/type_list.hpp
    ${SRC_PREFIX}/Details/value_record.hpp
    ${SRC_PREFIX}/Details/n_indexed_info.hpp
    ${SRC_PREFIX}/Details/n_indexed_helper.hpp
    ${SRC_PREFIX}/Details/tensor_iterator.hpp
    ${SRC_PREFIX}/Details/meta_helper.hpp)

#	LOGGER

set(LOGGER_SRC
    ${SRC_PREFIX}/Logger/logger.hpp
    ${SRC_PREFIX}/Logger/log_manager.hpp
    ${SRC_PREFIX}/Logger/log_manager.cpp
    ${SRC_PREFIX}/Logger/logged_apply_trait.hpp
    ${SRC_PREFIX}/Logger/logged_create_edge_trait.hpp
    ${SRC_PREFIX}/Logger/logged_filter_trait.hpp
    ${SRC_PREFIX}/Logger/logged_foreach_trait.hpp
    ${SRC_PREFIX}/Logger/logged_insert_trait.hpp
    ${SRC_PREFIX}/Logger/logged_iterable_trait.hpp
    ${SRC_PREFIX}/Logger/logged_monodim_filter_trait.hpp
    ${SRC_PREFIX}/Logger/logged_random_access_trait.hpp
    ${SRC_PREFIX}/Logger/logged_remove_trait.hpp
    ${SRC_PREFIX}/Logger/logged_size_trait.hpp
    ${SRC_PREFIX}/Logger/logged_slice_trait.hpp
    ${SRC_PREFIX}/Logger/logged_slice_view_trait.hpp)

#	COMMON N_INDEXED SRC

set(N_INDEXED_SRC
    ${N_INDEXED_INTERFACE_SRC}
    ${N_INDEXED_GRAPH_SRC}
    ${N_INDEXED_MAP_TREE_SRC}
    ${N_INDEXED_TUPLE_MAP_SRC}
    ${N_INDEXED_BOOST_MULTI_ARRAY_SRC}
    ${N_INDEXED_EIGEN_MATRIX_SRC}
    ${N_INDEXED_MDX_EMITTER_SRC}
    ${N_INDEXED_DETAILS_SRC}
    ${LOGGER_SRC})

##	Targets SRC

set(TEST_SRC
    ${N_INDEXED_SRC}
    ${SRC_PREFIX}/Tests/DetailsTest.cpp
    ${SRC_PREFIX}/Tests/graph_test.cpp
    ${SRC_PREFIX}/Tests/main.cpp
    ${SRC_PREFIX}/Tests/tree_test.cpp
    ${SRC_PREFIX}/Tests/tensor_test.cpp
    ${SRC_PREFIX}/Tests/catch.hpp
    ${SRC_PREFIX}/Tests/logger_test.cpp
    ${SRC_PREFIX}/Tests/eigen_matrix_test.cpp
    #${SRC_PREFIX}/Tests/sandbox.cpp
    )

set(FUZZ_SRC
    ${N_INDEXED_SRC}
    ${SRC_PREFIX}/fuzzing/fuzzing_helper.hpp
    ${SRC_PREFIX}/fuzzing/fuzzing.cpp)

set(BENCHMARK_SRC
    ${N_INDEXED_SRC}
    ${SRC_PREFIX}/benchmark/benchmark_main.cpp
    ${SRC_PREFIX}/benchmark/map_impl_benchmark.cpp
    ${SRC_PREFIX}/benchmark/graph_impl_benchmark.cpp
    ${SRC_PREFIX}/benchmark/map_tuple_impl_benchmark.cpp
    ${SRC_PREFIX}/benchmark/benchmark_helper.hpp
    ${SRC_PREFIX}/benchmark/random_access_benchmark.hpp
    ${SRC_PREFIX}/benchmark/deep_copy_benchmark.hpp
    ${SRC_PREFIX}/benchmark/apply_benchmark.hpp
    ${SRC_PREFIX}/benchmark/filter_benchmark.hpp
    ${SRC_PREFIX}/benchmark/tensor_ovehead.cpp)

################################################################
####														####
####					3rd Party							####
####														####
################################################################

#   BOOST
find_package(Boost REQUIRED)

#	GOOGLE BENCHMARK
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${3RDPARTY_PREFIX}/benchmark benchmark EXCLUDE_FROM_ALL)

#	EIGEN
set(EIGEN_INCLUDE_DIRS ${3RDPARTY_PREFIX}/eigen)

#   MICROSOFT C++ GSL
set(GSL_INCLUDE_DIRS ${3RDPARTY_PREFIX}/GSL/include)

##

################################################################
####														####
####					Test Executable						####
####														####
################################################################


add_executable(
        n_indexed_test ${TEST_SRC})

set_target_properties(
        n_indexed_test PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES)

#add_definitions(n_indexed_test "-std=c++2a -Xclang -fconcepts-ts")

target_include_directories(
        n_indexed_test
        PRIVATE ${Boost_INCLUDE_DIRS}
        PRIVATE ${EIGEN_INCLUDE_DIRS}
        PRIVATE ${GSL_INCLUDE_DIRS})

target_link_libraries(n_indexed_test benchmark ${Boost_LIBRARIES}) # link with google benchmark

if (ENABLE_LOGGING)
    target_compile_definitions(
            n_indexed_test
            PRIVATE
            N_INDEXED_LOGGING)
endif ()

################################################################
####														####
####					Benchmark Executable				####
####														####
################################################################


set(BENCHMARK_CONTENT "double" CACHE STRING "")
set(BENCHMARK_INDEXES "int" CACHE STRING "")

add_executable(
        n_indexed_benchmark ${BENCHMARK_SRC})

target_include_directories(
        n_indexed_benchmark
        PRIVATE ${Boost_INCLUDE_DIRS}
        PRIVATE ${EIGEN_INCLUDE_DIRS}
        PRIVATE ${GSL_INCLUDE_DIRS})

target_link_libraries(
        n_indexed_benchmark benchmark ${Boost_LIBRARIES}) # link with google do_benchmark

set_target_properties(
        n_indexed_benchmark PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES)

target_compile_definitions(
    n_indexed_benchmark PRIVATE
    BENCHMARK_CONTENT=${BENCHMARK_CONTENT}
    BENCHMARK_INDEXES=${BENCHMARK_INDEXES}
    BOOST_DISABLE_ASSERTS)

################################################################
####                                                        ####
####                    Benchmark Compilation               ####
####                                                        ####
################################################################

if (N_INDEXED_ENABLE_COMPILE_BENCH)

    ## The number of compilation benchmark
    ## Higher value led to lower variance but increase benchmark running time
    set(BENCHMAK_COUNT 1)

    #################################
    ##  Boost multi array overhead ##
    #################################

    set(boost_bench_dims "(1...4)")

    macro(add_raw_boost_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${boost_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            INCLUDE_DIRS "${Boost_INCLUDE_DIRS}"
            CXX_STANDARD 17)
    endmacro()

    macro(add_if_boost_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${boost_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" "${GSL_INCLUDE_DIRS}"
            CXX_STANDARD 17)
    endmacro()

    add_raw_boost_dataset(raw_boost_ctor "${SRC_PREFIX}/compile_benchmark/boost_multi_array/raw_ctor.cpp.erb")
    add_raw_boost_dataset(raw_boost_ctor_ra "${SRC_PREFIX}/compile_benchmark/boost_multi_array/raw_ctor_ra.cpp.erb")
    add_raw_boost_dataset(raw_boost_ctor_ra_sv "${SRC_PREFIX}/compile_benchmark/boost_multi_array/raw_ctor_ra_sv.cpp.erb")

    add_if_boost_dataset(if_boost_ctor "${SRC_PREFIX}/compile_benchmark/boost_multi_array/if_ctor.cpp.erb")
    add_if_boost_dataset(if_boost_ctor_ra "${SRC_PREFIX}/compile_benchmark/boost_multi_array/if_ctor_ra.cpp.erb")
    add_if_boost_dataset(if_boost_ctor_ra_sv "${SRC_PREFIX}/compile_benchmark/boost_multi_array/if_ctor_ra_sv.cpp.erb")

    metabench_add_chart(
        boost_chart DATASETS
        raw_boost_ctor
        raw_boost_ctor_ra
        raw_boost_ctor_ra_sv
        if_boost_ctor
        if_boost_ctor_ra
        if_boost_ctor_ra_sv)

    #################################
    ##      Eigen  overhead        ##
    #################################

    set(eigen_bench_dims "(1...3)")

    macro(add_raw_eigen_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${eigen_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            INCLUDE_DIRS "${EIGEN_INCLUDE_DIRS}" "${GSL_INCLUDE_DIRS}"
            CXX_STANDARD 17)
    endmacro()

    macro(add_if_eigen_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${eigen_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            INCLUDE_DIRS "${EIGEN_INCLUDE_DIRS}"
            CXX_STANDARD 17)
    endmacro()

    add_if_eigen_dataset(raw_eigen_instanciation "${SRC_PREFIX}/compile_benchmark/raw_eigen_instanciation.cpp.erb")
    add_raw_eigen_dataset(if_eigen_instanciation "${SRC_PREFIX}/compile_benchmark/if_eigen_instanciation.cpp.erb")

    metabench_add_chart(
        eigen_chart DATASETS
        raw_eigen_instanciation
        if_eigen_instanciation)

    #################################
    ##      Tuple Map  overhead    ##
    #################################

    set(tuple_bench_dims "(1...30)")

    macro(add_raw_tuple_map_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${tuple_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            CXX_STANDARD 17)
    endmacro()

    macro(add_if_tuple_map_dataset name path)
        metabench_add_dataset(
            ${name} "${path}" "${tuple_bench_dims}"
            MEDIAN_OF ${BENCHMAK_COUNT}
            INCLUDE_DIRS "${GSL_INCLUDE_DIRS}"
            CXX_STANDARD 17)
    endmacro()

    add_raw_tuple_map_dataset(raw_tuple_instanciation "${SRC_PREFIX}/compile_benchmark/raw_tuple_instanciation.cpp.erb")
    add_raw_tuple_map_dataset(raw_tuple_instanciation_for "${SRC_PREFIX}/compile_benchmark/raw_tuple_instanciation_for.cpp.erb")

    add_if_tuple_map_dataset(if_tuple_instanciation "${SRC_PREFIX}/compile_benchmark/if_tuple_instanciation.cpp.erb")
    add_if_tuple_map_dataset(if_tuple_instanciation_for "${SRC_PREFIX}/compile_benchmark/if_tuple_instanciation_for.cpp.erb")

    metabench_add_chart(
        tuple_chart DATASETS
        raw_tuple_instanciation
        raw_tuple_instanciation_for
        if_tuple_instanciation
        if_tuple_instanciation_for)


    ###################################
    ##   All Compile Time Benchmark  ##
    ###################################

    add_custom_target(compile_benchmark)
    add_dependencies(compile_benchmark boost_chart eigen_chart tuple_chart)

endif()
