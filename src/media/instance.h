#pragma once
#include <memory>

namespace sdl {

class Instance_;
using Instance = std::shared_ptr<const Instance_>;

class Instance_ {
public:
    ~Instance_();
    Instance_(const Instance_&) = delete;
    Instance_(Instance_&& other) noexcept;
    Instance_& operator=(const Instance_&) = delete;
    Instance_& operator=(Instance_&& other) noexcept;
    static Instance Create();
private:
    Instance_();
    static bool instanceExists;
    bool active;
    friend void Swap(Instance_& lhs, Instance_& rhs) noexcept;
};

void Swap(Instance_& lhs, Instance_& rhs) noexcept;

}
