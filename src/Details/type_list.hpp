#ifndef TYPE_LIST_H_
#define TYPE_LIST_H_

#include <type_traits>

namespace type_list {

	/**
	 * 	\brief Define what we call type list
	 */
	template <typename T>
	constexpr auto is_type_list = false;

	template <template <typename...> typename Template, typename ...T>
	constexpr auto is_type_list<Template<T...>> = true;

	/**
	 * \brief an example of list
	 */
	template <typename ...T>
	struct list;

	/**
	 * \brief Compute list length
	 */
	template <typename>
	struct length;

	template <template <typename...> typename Template, typename ...T>
	struct length<Template<T...>> {
		static constexpr auto value = sizeof...(T);
	};

	template <typename T>
	constexpr auto length_v = length<T>::value;

	//

	template <typename T>
	struct head;

	template <template <typename...> typename Template, typename Tfirst, typename ...T>
	struct head<Template<Tfirst, T...>> {	
		using type = Tfirst;
	};

	template <typename T>
	using head_t = typename head<T>::type;

	//

	template <typename T>
	struct tail;

	template <template <typename...> typename Template, typename Tfirst, typename ...T>
	struct tail<Template<Tfirst, T...>> {
		using type = Template<T...>;
	};

	template <typename T>
	using tail_t = typename tail<T>::type;

	//

	template <typename T, typename Tlist>
	struct insert;

	template <typename T, template <typename...> typename Template, typename ...Elmt>
	struct insert<T, Template<Elmt...>> {
		using type = Template<T, Elmt...>;
	};

	template <typename T, typename Tlist>
	using insert_t = typename insert<T, Tlist>::type;

	//

	template <typename Tlist1, typename Tlist2>
	struct cat;

	template <template <typename...> typename Template, typename ...T1, typename ...T2>
	struct cat<Template<T1...>, Template<T2...>> {
		using type = Template<T1..., T2...>;
	};

	template <typename Tlist1, typename Tlist2>
	using cat_t = typename cat<Tlist1, Tlist2>::type;

	//

	template <typename T, typename Tlist>
	struct contains;

	template <typename T, template <typename...> typename Template, typename ...Elmts>
	struct contains<T, Template<Elmts...>> : 
		std::disjunction<std::is_same<T, Elmts>...> {};

	template <typename T, typename Tlist>
	constexpr auto contains_v = contains<T, Tlist>::value;	

	//

	template <typename Tlist>
	struct is_unique;

	template <template <typename ...> typename Template>
	struct is_unique<Template<>> : std::true_type {};

	template <template <typename...> typename Template, typename Tfirst, typename ...T>
	struct is_unique<Template<Tfirst, T...>> {
		static constexpr auto value = 
			!contains_v<Tfirst, Template<T...>> && is_unique<Template<T...>>::value;
	};

	template <typename Tlist>
	constexpr auto is_unique_v = is_unique<Tlist>::value;

	//

	template <typename Tlist>
	struct unique;

	template <template <typename...> typename Template>
	struct unique<Template<>> {
		using type = Template<>;
	};

	template <template <typename...> typename Template, typename Tfirst, typename ...T>
	struct unique<Template<Tfirst, T...>> {
		using type =
			std::conditional_t<
				contains_v<Tfirst, Template<T...>>,
				typename unique<Template<T...>>::type,
				insert_t<Tfirst, typename unique<Template<T...>>::type>
			>;
	};

	template <typename Tlist>
	using unique_t = typename unique<Tlist>::type;

	//

	template <auto N, typename Tlist>
	struct get_nth : get_nth<N - 1, tail_t<Tlist>> {};

	template <typename Tlist>
	struct get_nth<0, Tlist> : head<Tlist> {};

	template <auto N, typename Tlist>
	using get_nth_t = typename get_nth<N, Tlist>::type;

	//

	template <auto N, typename Tlist>
	struct remove_nth : 
		insert<
			head_t<Tlist>, 
			typename remove_nth<N - 1, tail_t<Tlist>>::type> {};

	template <typename Tlist>
	struct remove_nth<0, Tlist> : tail<Tlist> {};

	template <auto N, typename Tlist>
	using remove_nth_t = typename remove_nth<N, Tlist>::type;

	//

	template <template <typename...> typename UnaryOp, typename Tlist>
	struct transform;

	template <template <typename...> typename UnaryOp, template <typename...> typename Template, typename ...T>
	struct transform<UnaryOp, Template<T...>> {
		using type = Template<typename UnaryOp<T>::type...>;
	};

	template <template <typename...> typename UnaryOp, typename Tlist>
	using transform_t = typename transform<UnaryOp, Tlist>::type;

	//

	template <template <typename...> typename Template, typename Tlist>
	struct instanciate;

	template <template <typename...> typename Template, template <typename...> typename Template2, typename ...T>
	struct instanciate<Template, Template2<T...>> {
		using type = Template<T...>;
	};

	template <template <typename...> typename Template, typename Tlist>
	using instanciate_t = typename instanciate<Template, Tlist>::type;

	//

	template <template <typename...> typename UnaryPred, typename Tlist>
	struct true_for_each : 
		instanciate_t<std::conjunction, transform_t<UnaryPred, Tlist>> {};

	template <template <typename ...> typename UnaryOp, typename Tlist>
	constexpr auto true_for_each_v = true_for_each<UnaryOp, Tlist>::value;

	//

	template <template <typename...> typename UnaryPred, typename Tlist>
	struct true_for_any : 
		instanciate_t<std::disjunction, transform_t<UnaryPred, Tlist>> {};

	template <template <typename ...> typename UnaryOp, typename Tlist>
	constexpr auto true_for_any_v = true_for_any<UnaryOp, Tlist>::value;

	//

	

}

#endif