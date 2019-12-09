#ifndef SLICE_TRAIT_H_
#define SLICE_TRAIT_H_

#include <exception>
#include "n_indexed.hpp"
#include "../Details/type_def.hpp"

namespace NIndexedContainer {

	class empty_slice_exception : public std::exception {
	
	public:
		const char *what() const noexcept override
		{
			return "EmptySliceException";
		}
	}; 

    /**
     * \struct SliceAccessTrait
     * \brief Select values with a given index
     * \details [long description]
     */
    template <typename Tcontainer>
    struct slice_trait {

        /**
         * \brief Select values having the Dim'th index equal to the given index
         * \param select_index 
         * \tparam Dim Indicate on which index selection is done
         * \tparam TIndexValue Index type
         * \return a new n_indexed container containing the selection
         * If nothing match the given criterion, an exception will be thrown
         */
        template <Uint Dim, typename TIndexValue>
        auto slice(const TIndexValue& select_value);
    };

} /* namespace NIndexedContainer */


#endif