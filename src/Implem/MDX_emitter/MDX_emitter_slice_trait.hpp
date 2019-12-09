#ifndef MDX_EMITTER_SLICE_TRAIT_H_
#define MDX_EMITTER_SLICE_TRAIT_H_

#include "MDX_emitter_storage.hpp"
#include "../../Interface/n_indexed.hpp"

namespace NIndexedContainer {

	template <typename Tcontent, typename ...Tindexes, typename Ttrait_list>
	struct slice_trait<n_indexed<Tcontent, MDX_emitter_storage, indexes<Tindexes...>, Ttrait_list>> {

		template <Uint Dim, typename TIndexValue>
        void slice(const TIndexValue& select_value)
        {
 			std::cout << "SELECT\n";


 			for (auto i = 0; i < sizeof...(Tindexes) - 1; ++i) {
 				const auto ind = (i < Dim ? i : i + 1);
 				std::cout << self()->_dimensions[ind].name << " ON "
 				<< "axis(" << i << ")\n";
 			}

 			// TODO Comma

 			std::cout << "FROM " << self()->_name << "\n" 
 			<< "WHERE " << self()->_dimensions[Dim].name << "." << select_value 
 			<< std::endl;

        }

	private:
		DEFINE_SELF
	};

}

#endif