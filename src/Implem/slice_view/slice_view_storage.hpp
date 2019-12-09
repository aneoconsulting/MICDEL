#ifndef SLICE_VIEW_STORAGE_H_
#define SLICE_VIEW_STORAGE_H_

#include "../../Interface/n_indexed.hpp"
#include "../../Details/n_indexed_helper.hpp"

namespace NIndexedContainer {

	template <Uint i>
	struct dim_holder;

	template <typename TBaseContainer, typename Dim, typename TindexValue>
	struct slice_properties;

	template <typename Tcontainer, typename TSliceProperties>
	struct slice_view_storage_impl;

	template <typename Tcontainer, typename Tag>
	using slice_view_storage = 
		order_storage_properties<
			Tcontainer, Tag,
			slice_view_storage_impl,
			propertie_pattern<type_propertie<slice_properties>>>;


	template <typename Tcontent, typename ...Tindexes, typename TtraitList, typename TBaseContainer, Uint Dim, typename TindexValue, typename TPropertieList>
	struct slice_view_storage_impl<n_indexed<Tcontent, slice_view_storage, indexes<Tindexes...>, TtraitList, TPropertieList>, slice_properties<TBaseContainer, dim_holder<Dim>, TindexValue>> {

		static constexpr auto dim = Dim;
		using base_container_type = TBaseContainer;

		slice_view_storage_impl(TBaseContainer& c, const TindexValue& v) noexcept 
		: _storage{c}, _index{v} 
		{}

		slice_view_storage_impl(const slice_view_storage_impl&) noexcept = default;
		slice_view_storage_impl(slice_view_storage_impl&&) noexcept = default;

		TBaseContainer& _storage;
		const TindexValue _index;
	};


	template <Uint N, typename Tcontainer, typename TindexValue>
	auto make_slice_view(Tcontainer& c, const TindexValue& idx)
	{
		using Tcontent = typename n_indexed_info<Tcontainer>::content_type;
		using TindexList = typename n_indexed_info<Tcontainer>::index;
		using Tslice = n_indexed<
							Tcontent, 
							slice_view_storage, 
							type_list::remove_nth_t<N, TindexList>,
							traits<random_access_trait>,
							storage_properties<
								slice_properties<
									Tcontainer, 
									dim_holder<N>, 
									TindexValue
								>
							>
						>;

		return Tslice{c, idx};
	}

}

#endif