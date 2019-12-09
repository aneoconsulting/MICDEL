
.. PAs trop compris le fonctionement de toctree (probablement le menu defilant de gauche)

.. toctree::
   :caption: Content:

##################################################
A Multidimensional Container Interface Framework
##################################################


******
Goals
******

Storage is actually one of the most complex issue when writing code. Choosing one container over another has serious consequences in term of performance because a given container could be very efficient for one access pattern while offering poor performance for another usage. It is difficult to know which container fit to a given usage because it require rigorous benchmarking. In addition, it is often impossible in a real life project to predict exactly how will a container be used.

This project aim to provide an interface framework for multidimensional container which allow user to describe a container in term of needed functionality. Each requested feature is associated with piece of interface.


***************
API reference
***************

The container interface
=======================

This structure is the framework's entry point. It is used to describe a container.

.. doxygenstruct:: NIndexedContainer::n_indexed
   :members:

Indexation types
================

There are two kinds of indexation :

.. doxygenstruct:: NIndexedContainer::indexes
   :members:

.. Pour des raisons obscures, il ne faut pas mettre l'espace de nom pour dynamic_indexes.......

.. doxygenstruct:: dynamic_indexes
   :members:

Storage Properties type
=======================

.. doxygenstruct:: NIndexedContainer::storage_properties
	:members:

Traits
=======

Traits implements features with respect to the storage method. 

.. warning:: Not all features are available for all storage methods !

apply
-------

.. doxygenstruct:: NIndexedContainer::apply_trait
   :members:

create_edge
--------------

.. doxygenstruct:: NIndexedContainer::create_edge_trait
   :members:

filter
--------------

.. doxygenstruct:: NIndexedContainer::filter_trait
   :members:

.. doxygenstruct:: NIndexedContainer::criterion_all


foreach
--------------

.. doxygenstruct:: NIndexedContainer::foreach_trait
   :members:

insert
--------------

.. doxygenstruct:: NIndexedContainer::insert_trait
   :members:

iterable
--------------

.. doxygenstruct:: NIndexedContainer::iterable_trait
   :members:

mono_dim_filter
----------------

.. doxygenstruct:: NIndexedContainer::mono_dim_filter_trait
	:members:

random_access
--------------

.. doxygenstruct:: NIndexedContainer::random_access_trait< n_indexed< T_content, T_concrete_storage, indexes< T_indexes... >, T_trait_list, T_propertie_list > >
	:members:

.. doxygenstruct::NIndexedContainer::random_access_trait< n_indexed< T_content, T_concrete_storage, dynamic_indexes, T_trait_list, T_propertie_list > >
	:members:

remove
--------------

.. doxygenstruct:: NIndexedContainer::remove_trait< n_indexed< T_content, T_concrete_storage, indexes< T_indexes... >, TraitList, T_propertie_list > >
	:members:

.. doxygenstruct:: NIndexedContainer::remove_trait< n_indexed< T_content, T_concrete_storage, dynamic_indexes, T_trait_list, T_propertie_list > >
	:members:

shape
--------------

.. doxygenstruct:: NIndexedContainer::shape_trait
	:members:

size
--------------

.. doxygenstruct:: NIndexedContainer::size_trait
	:members:

slice
--------------

.. doxygenstruct:: NIndexedContainer::slice_trait
	:members:

slice_view
--------------

.. doxygenstruct:: NIndexedContainer::slice_view_trait
	:members:

****************
Implementations
****************

We call implementation a given storage method and associated features. There are currently 5 working implementations:



boost multi_array
	Based on the `boost multi_array`_ container. Use the static indexation.

eigen
	Based on the `eigen matrix`_ container. Dimensions **can** be specified at compile time using the storage_propertie *dimensions* (see `Examples`_). The default setting is to define sizes along each dimension at runtime.

graph
	A graph where nodes carry values and edges are labeled by the indexes.

map_tree
	A fixed depth tree where each node is an associative container. The value are stored in the leaves.

tuple_map
	tuple_map is an associative array which map index tuple to stored values.

Here is a summary of each available trait for all implementations :

+----------------+-------------+-------------+-------------+-------------+-------------+
|                | multi array | eigen       | graph       | map_tree    | tuple_map   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|apply           |   |check|   |   |check|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|create_edge     |   |cross|   |   |cross|   |   |check|   |   |cross|   |   |cross|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|filter          |   |cross|   |   |cross|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|foreach         |   |check|   |   |check|   |   |cross|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|insert          |   |cross|   |   |cross|   |   |check|   |   |cross|   |   |cross|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|iterable        |   |check|   |   |check|   |   |cross|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|mono_dim_filter |   |cross|   |   |cross|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|random_access   |   |check|   |   |check|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|remove          |   |cross|   |   |cross|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|shape           |   |check|   |   |check|   |   |cross|   |   |cross|   |   |cross|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|size            |   |check|   |   |check|   |   |check|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|slice           |   |check|   |   |check|   |   |cross|   |   |check|   |   |check|   |
+----------------+-------------+-------------+-------------+-------------+-------------+
|slice_view      |   |check|   |   |check|   |   |check|   |   |cross|   |   |cross|   |
+----------------+-------------+-------------+-------------+-------------+-------------+

**********
Examples
**********


.. code:: c++

	using namespace NIndexedContainer;

	using container = 
		n_indexed<
			double,
			// Contains double

			eigen_matrix_storage,
			// Rely on the eigen matrix storage method

			indexes<int, int>,
			// Indexed by two int

			traits<	
				random_access_trait,
				foreach_trait
			>,
			// Request ramdom_access and apply features

			storage_properties<
				dimensions<static_dim<10>, dynamic_dim>	
			>
			// Additional option : 
			// The first dimension is known at compile time
			// and the second at runtime
		>;

	// The first size must be equal to the compile time size given in properties
	container c{10, 42};

	c.foreach([](int i, int j, auto& x) { x = i+j; });
	c(7, 2) = 9;

	
.. ------------------------------------------------------------------------------------
.. Useful :
.. |check| unicode:: U+02713
.. |cross| unicode:: U+02717
.. _boost multi_array: http://www.boost.org/doc/libs/1_70_0/libs/multi_array/doc/index.html
.. _eigen matrix: http://eigen.tuxfamily.org
