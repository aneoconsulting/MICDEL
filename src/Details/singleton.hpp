#ifndef N_INDEXED_SINGLETON_H_
#define N_INDEXED_SINGLETON_H_

namespace NIndexedContainer {

    template <typename Timpl>
    class singleton {

    protected:
        singleton() {}

    public:
        singleton(const singleton&) = delete;
        singleton(const singleton&&) = delete;
        singleton& operator=(const singleton&) = delete;
        singleton& operator=(const singleton&&) = delete;
        ~singleton() {}

        static Timpl& get_instance()
        {
            static Timpl _instance{};
            return _instance;
        }
    };


}

#endif
