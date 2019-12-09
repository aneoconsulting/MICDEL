#ifndef N_INDEXED_LOG_MANAGER_H_
#define N_INDEXED_LOG_MANAGER_H_

#include <sstream>
#include <iostream>
#include "../Details/singleton.hpp"

namespace NIndexedContainer {


    class log_manager : public singleton<log_manager> {
    public:

        ~log_manager()
        {
            flush_to(std::cout);
        }

        template <typename ...T>
        void log(T&& ...value)
        {
            (_data << ... << std::forward<T>(value)) << '\n';
        }

        void flush_to(std::ostream& stream);
        //void set_section(const std::string_view& str = "default");

    private:
        //std::string _section{"default"};
        std::stringstream _data;
    };


#ifdef N_INDEXED_LOGGING
#define LOG(...) NIndexedContainer::log_manager::get_instance().log(__VA_ARGS__)
#define BEGIN_SECTION(name) LOG("SECTION(", name, ") [");
#define END_SECTION() LOG("]");
#else
#define LOG(...)
#define BEGIN_SECTION(name)
#define END_SECTION()
#endif


}

#endif
