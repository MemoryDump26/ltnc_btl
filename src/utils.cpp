#include "utils.h"

int clamp(const int value, const int low, const int high) {
    if (value < low) return low;
    else if (value > high) return high;
    else return value;
}

