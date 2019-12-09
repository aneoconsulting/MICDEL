#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include "../Details/type_def.hpp"
#include "../Details/type_list.hpp"

namespace NIndexedContainer {

    /**
     * 	
     * Standard Properties :
     * 
     */

    /**
     * \brief Describe a compile time defined dimension
     * \tparam Dim dimension
     */
    template <auto Dim>
    struct static_dim;

    /**
     * \brief Describe a runtime defined dimension
     */
    struct dynamic_dim;

    /**
     * \brief A type list used to hold dimensions (either static or dynamics)
     */
    template <typename ...Dims>
    struct dimensions;

    /**
     * \brief A shortcut which define a static dimensions list
     */
    template <auto ...Dims>
    using static_dimensions = 
        dimensions<static_dim<Dims>...>;
}

#endif