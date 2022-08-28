// #pragma once

#ifndef NONMOVEABLE_H_INCLUDED
#define NONMOVEABLE_H_INCLUDED

struct NonMovable {
    NonMovable() = default;
    NonMovable& operator = (NonCopyable&&) = delete;
    NonMovable(NonCopyable&&) = delete;
};

#endif // For NONMOVEABLE_H_INCLUDED