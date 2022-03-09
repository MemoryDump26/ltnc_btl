#ifndef UTILS_H
#define UTILS_H

template<class T>
T clamp(const T value, const T low, const T high) {
    if (value < low) return low;
    else if (value > high) return high;
    else return value;
}

#endif
