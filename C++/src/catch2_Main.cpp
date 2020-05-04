// Provide a file for precompiled header for Catch2 
// per https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
