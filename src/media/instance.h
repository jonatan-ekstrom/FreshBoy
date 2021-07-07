#pragma once
#include <memory>

namespace sdl {

class Instance_;
using Instance = std::shared_ptr<const Instance_>;

class Instance_ {
public:
    ~Instance_();
    Instance_(const Instance_&) = delete;
    Instance_& operator=(const Instance_&) = delete;
    static Instance Create();
private:
    Instance_();
};

}
