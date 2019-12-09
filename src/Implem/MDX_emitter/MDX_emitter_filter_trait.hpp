#ifndef N_INDEXED_MDX_EMITTER_FILTER_TRAIT_H_
#define N_INDEXED_MDX_EMITTER_FILTER_TRAIT_H_

#include "MDX_emitter_storage.hpp"
#include "../../Interface/filter_trait.hpp"
#include "../../Details/impl_helper.hpp"

namespace NIndexedContainer {

	template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
	struct filter_trait<n_indexed<Tcontent, MDX_emitter_storage, indexes<Tindexes...>, Ttrait_list>> {

		template <typename ...Tcriterions>
		auto filter(const Tcriterions& ...criterions)
		{
			std::cout << "SELECT\n";

			for (auto i = 0; i < sizeof...(Tindexes); ++i) {
				std::cout << self()->_dimensions[i].name << " ON "
				<< "axis(" << i << ")\n";
			}

			std::cout << "FROM " << self()->_name << "\n"
			<< "WHERE (\n";

			([i = 0, this](const auto& crit) mutable {	

				using criterion_type = 
					std::decay_t<decltype(crit)>;

				if constexpr (!std::is_same_v<criterion_type, criterion_all>) {
					std::cout << this->self()->_dimensions[0].name << "." << crit << "\n";
				}
				
				i++;
				
			}(criterions), ...);

			

			std::cout << ")" << std::endl;
		}

	private:
		DEFINE_SELF
	};

}

#endif