#ifndef SLICE_VIEW_TRAIT_H_
#define SLICE_VIEW_TRAIT_H_

namespace NIndexedContainer {

	template <typename Tcontainer>
	struct slice_view_trait {

		template <Uint Dim, typename TIndexValue>
		auto slice_view(const TIndexValue& select_value);

	};
}

#endif