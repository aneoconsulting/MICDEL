
#include "log_manager.hpp"

namespace NIndexedContainer {


    void log_manager::flush_to(std::ostream &stream)
    {
        stream << _data.rdbuf();
    }

}