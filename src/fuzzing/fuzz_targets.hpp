#ifndef FUZZ_TARGET_H_
#define FUZZ_TARGET_H_

#include "../Interface/n_indexed.hpp"

namespace NIndexedContainer {
	

	template <typename T, typename ...>
	struct filter_fuzz;

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	struct filter_fuzz< n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>> {

		using container = n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>;

		filter_fuzz(container& c)
			: _c{ c } {}

		auto operator()(Tindexes ...indexes)
		{
			return _c.filter(indexes...);
		}

	private:
		container& _c;
	};

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes> 
	struct filter_fuzz<n_indexed<T_content, T_storage, dynamic_indexes, Ttrait_list, TpropertieList>, Tindexes...> {

		using container = n_indexed<T_content, T_storage, dynamic_indexes, Ttrait_list, TpropertieList>;

		filter_fuzz(container& c)
			: _c{c} {}

		auto operator()(Tindexes ...indexes)
		{

		}

	private:
		container& _c;
	};

	//------------------------------------------

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	filter_fuzz(n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>) ->
		filter_fuzz<n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>>;

	template <typename T>
	struct random_access_fuzz;

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	struct random_access_fuzz< n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>> {

		using container = n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>;

		random_access_fuzz(container& c)
			: _c{ c } {}

		void operator()(T_content content, Tindexes ...indexes)
		{
			_c(indexes...) = content;
		}

	private:
		container& _c;
	};

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	random_access_fuzz(n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>) ->
		random_access_fuzz<n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>>;

	//----------------------------------------------------------------------------------------------------------

	template <typename T>
	struct remove_fuzz;

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	struct remove_fuzz< n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>> {

		using container = n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>;

		remove_fuzz(container& c)
			: _c{ c } {}

		auto operator()(Tindexes ...indexes)
		{
			return _c.remove(indexes...);
		}

	private:
		container& _c;
	};

	template <typename T_content, template <typename, typename> typename T_storage, typename Ttrait_list, typename TpropertieList, typename ...Tindexes>
	remove_fuzz(n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>) ->
		remove_fuzz<n_indexed<T_content, T_storage, indexes<Tindexes...>, Ttrait_list, TpropertieList>>;


	//----------------------------------------------------------------------------------------------------
}


#endif