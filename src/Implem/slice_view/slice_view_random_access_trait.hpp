#ifndef SLICE_VIEW_RANDOM_ACCESS_H_
#define SLICE_VIEW_RANDOM_ACCESS_H_

#include "slice_view_storage.hpp"
#include "../../Interface/random_access_trait.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	namespace Details {

		// TODO : à netoyer, en parler avec vivien

		template <int N, typename Tfunc, typename Targ>
		struct bind_helper;

		template <int N, typename Tfunc, typename Targ>
		constexpr auto bind(Tfunc f, Targ&& arg)
		{
			return bind_helper<N, Tfunc, Targ>::bnd(std::move(f), std::forward<Targ>(arg));
		}

		template <int N, typename Tfunc, typename Targ>
		struct bind_helper {

			static constexpr auto bnd(Tfunc&& f, Targ&& arg)
			{
				return 
				[f, argv = arg](const auto& first, const auto& ...nexts)
				{
					return bind<N - 1>(bind<0>(f, first), argv)(nexts...);
				};
			}
		};

		template <typename Tfunc, typename Targ>
		struct bind_helper<0, Tfunc, Targ> {

			static constexpr auto bnd(Tfunc f, Targ&& arg)
			{
				return
				[f, argv = arg](const auto& ...x) -> auto&&
				{
					return f(argv, x...);
				};
			}
		};
	}

	template <typename Tcontent, typename ...Tindexes, typename TtraitList, typename TPropertieList>
	struct random_access_trait<n_indexed<Tcontent, slice_view_storage, indexes<Tindexes...>, TtraitList, TPropertieList>> {

		decltype(auto) operator()(const Tindexes& ...idx)
		{
			auto func = [this](const auto& ...x) -> Tcontent& { return self()->_storage(x...); };
			return Details::bind<trait_container_t<random_access_trait>::dim>(func, self()->_index)(idx...);
		}

	private:
		DEFINE_SELF
	};

}

#endif