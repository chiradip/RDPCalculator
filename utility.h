//
// Created by Chiradip Mandal on 4/11/25.
//

#ifndef UTILITY_H
#define UTILITY_H
#include <stdexcept>

template<class R, class A> R narrow_cast(const A& a) {
    R r = R(a);
    if (A(r)!=a) throw std::runtime_error("info loss");
    return r;
}
#endif //UTILITY_H
