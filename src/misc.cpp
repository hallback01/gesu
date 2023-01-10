#include "misc.h"

double Misc::into_radians(double degrees) {
    return degrees * (Misc::PI / 180.0);
}

double Misc::into_degrees(double radians) {
    return radians * (180.0 / Misc::PI);
}