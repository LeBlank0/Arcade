//
// Created by chaoticks on 30/03/2020.
//

#ifndef OOP_ARCADE_2019_SOLOADER_HPP
#define OOP_ARCADE_2019_SOLOADER_HPP

#include <string>
#include <dlfcn.h>
#include <iostream>

template <typename T>
class SoLoader {
public:
    SoLoader(const std::string &filename)
    {
        if (filename == "")
            return;
        this->_lib = dlopen(filename.c_str(), RTLD_LAZY);
        if (this->_lib == nullptr)
            throw std::exception();
        T *(*func)() = reinterpret_cast<T *(*)()>(dlsym(this->_lib, "entry"));
        if (func == nullptr)
            throw std::exception();
        this->_instance = func();
    }

    ~SoLoader() = default;

    T *operator ->() const {
        return (this->_instance);
    }

    T &operator *() const {
        return (*this->_instance);
    }
private:
    void *_lib = nullptr;
    T *_instance = nullptr;
};
#endif //OOP_ARCADE_2019_SOLOADER_HPP
