#define __ANIMAL__

#include "Animal.hpp"

// Here with inclusion we include definition of the global type_ variable
// It is here defined and allocated static memory for that variable.
// It cannot be defined in other TU, but only here and it suffices.

// It would be even more better, if we define those gloabs here, because we never include .cpp file, so it cannot be redefined anywhere else

string Animal::type_;