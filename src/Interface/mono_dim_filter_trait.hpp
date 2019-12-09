#ifndef MONO_DIM_FILTER_TRAIT_H_
#define MONO_DIM_FILTER_TRAIT_H_

#include "n_indexed.hpp"
#include "filter_trait.hpp"
#include "../Details/impl_helper.hpp"
#include "../Details/type_def.hpp"

namespace NIndexedContainer {

	template <typename T_container>
	struct mono_dim_filter_trait {

		/**
		 * \brief A shortcut to filter only on one dimension : see filter_trait
		 * \details A default implementation for this trait is provided for containers already providing filter_trait 
		 * 
		 * \param criterion Filter criterion
		 * \tparam Dim The dimension on which the criterion will be applied
		 * \return A new fresh filtered container  
		 */
		template <Size_t Dim, typename TCriterion>
		auto filter_dim(const TCriterion& criterion);
	};

	/**
	 * \brief Default implementation that rely on filter trait
	 * \details need the filter trait to be enabled
	 */
	template <typename T_content, template <typename, typename> typename T_concrete_storage,  typename ...T_indexes, typename T_trait_list, typename T_propertie_list>
	struct mono_dim_filter_trait<n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, T_trait_list, T_propertie_list>> 
		: require_trait<n_indexed<T_content, T_concrete_storage, indexes<T_indexes...>, T_trait_list, T_propertie_list>, filter_trait>
	{

		template <Size_t Dim, typename TCriterion>
		auto filter_dim(const TCriterion& criterion)
		{
			constexpr auto IndexesCount = sizeof...(T_indexes);
			static_assert (Dim < IndexesCount, "Dim must be less than Indexes count");

			return impl_helper<
				std::make_integer_sequence<Size_t, Dim>,
				std::make_integer_sequence<Size_t, IndexesCount - Dim - 1>,
				decltype(self()), TCriterion>::helper(self(), criterion);
		}

	private:

		static constexpr criterion_all CriterionAllGen(int)
		{
			return criterion_all{};
		}

		template <typename TSeq1, typename TSeq2, typename TSelf, typename TCriterion>
		struct impl_helper;

		template <Size_t ...N1, Size_t ...N2, typename TSelf, typename TCriterion>
		struct impl_helper<std::integer_sequence<Size_t, N1...>, std::integer_sequence<Size_t, N2...>, TSelf, TCriterion> {

			static auto helper(TSelf s, const TCriterion& criterion)
			{
				return s->filter(CriterionAllGen(N1)..., criterion, CriterionAllGen(N2)...);
			}
		};

		DEFINE_SELF
	};

}

#endif /* MONO_DIM_FILTER_TRAAIT_H_ */
