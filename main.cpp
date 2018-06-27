
#include <ciso646>

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream.hpp> // <iostream> + nl, sp etc. defined...
#include <iterator>
#include <list>
#include <map>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

namespace fs = std::experimental::filesystem;

#include <autotimer.hpp>

#include "string_split.hpp"


int main ( ) {

    ss::print ( ss::string_split ( std::string ( "first one,two,three" ), " ","," ) ); std::cout << nl;
    ss::print ( ss::string_split ( std::string ( "second one,two" ), " ", "," ) ); std::cout << nl;
    ss::print ( ss::string_split ( std::string ( "third one" ), " ", "," ) ); std::cout << nl;
    ss::print ( ss::string_split ( std::string ( "alone" ), " ", "," ) ); std::cout << nl;

	return 0;
}
