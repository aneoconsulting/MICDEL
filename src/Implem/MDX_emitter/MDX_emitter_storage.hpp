#ifndef NINDEXED_MDX_EMITTER_STORAGE_H_
#define NINDEXED_MDX_EMITTER_STORAGE_H_

#include "../../Interface/n_indexed.hpp"
#include "../../Details/type_def.hpp"

namespace NIndexedContainer {

	namespace MDX_lang {


		struct dimension {
			std::string name;

		};

	}

	/**
	 * 	
	 * 
	 */

	template <typename, typename>
	struct MDX_emitter_storage;

	//

	template <typename Tcontent, typename ...Tindexes, typename TtraitList>
	struct MDX_emitter_storage<n_indexed<Tcontent, MDX_emitter_storage, indexes<Tindexes...>, TtraitList>, storage_tag> {

		static constexpr auto dimensions_count = sizeof...(Tindexes);
		Array<MDX_lang::dimension, dimensions_count> _dimensions;
		std::string _name;
	};

}




#endif