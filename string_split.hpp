
#pragma once

#include <ciso646>

#include <iostream.hpp> // <iostream> + nl, sp etc. defined...
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>


namespace ss {


template<typename T>
using is_string = std::is_base_of<std::basic_string<typename T::value_type>, T>;


template<typename T, typename = is_string<T>>
void print ( const T & string_ ) noexcept {

	if constexpr ( std::is_same<T, std::string>::value ) { std::cout << '[' << string_ << ']'; }
	else if constexpr ( std::is_same<T, std::wstring>::value ) { std::wcout << L'[' << string_ << L']'; }
}

template<typename T, typename = is_string<T>>
void print ( const std::vector<T> & string_vector_ ) noexcept {

	for ( const auto & string : string_vector_ ) {

		if constexpr ( std::is_same<T, std::string>::value ) { std::cout << '<' << string << '>' << sp; }
		else if constexpr ( std::is_same<T, std::wstring>::value ) { std::wcout << L'<' << string << L'>' << sp; }
	}
}

#define CHARACTER(name, character) \
template<typename T, typename = is_string<T>> \
struct name { \
\
	static constexpr auto c ( ) noexcept { \
\
		if constexpr ( std::is_same<T, std::string>::value ) return std::string ( character ).back ( ); \
		if constexpr ( std::is_same<T, std::wstring>::value ) return std::wstring ( L##character ).back ( ); \
	} \
\
	static constexpr auto s ( ) noexcept { \
\
		if constexpr ( std::is_same<T, std::string>::value ) return std::string ( character ); \
		if constexpr ( std::is_same<T, std::wstring>::value ) return std::wstring ( L##character ); \
	} \
};

CHARACTER ( space, " " )
CHARACTER ( dot, "." )
CHARACTER ( comma, "," )
CHARACTER ( langle, "<" )
CHARACTER ( rangle, ">" )
CHARACTER ( dquote, "\"" )

namespace detail {

#define FORCE_INLINE

template<typename T, typename = is_string<T>>
FORCE_INLINE std::size_t index_after_if_first ( const std::size_t begin_, const T & string_, const T & delimiter_ ) noexcept {

	const std::size_t length = delimiter_.length ( );

	if ( string_.length ( ) - begin_ < length ) {

		return begin_;
	}

	typename T::value_type const * s = string_.data ( ) + begin_;

	for ( std::size_t i = 0; i < length; ++i ) {

		if ( s [ i ] != delimiter_ [ i ] ) {

			return begin_;
		}
	}

	return begin_ + length;
}

template<typename T, typename = is_string<T>>
FORCE_INLINE std::size_t index_after_if_first ( const std::size_t begin_, const T & string_, const typename T::value_type delimiter_ ) noexcept {

	return string_.length ( ) - begin_ ? begin_ + ( string_ [ begin_ ] == delimiter_ ) : begin_;
}

template<typename T, typename = is_string<T>>
FORCE_INLINE std::size_t find_first_not_space_nor_delimiter ( const T & string_, const T & delimiter_ ) noexcept {

	std::size_t begin = 0, prev = 0;

	while ( true ) {

		begin = index_after_if_first ( begin, string_, delimiter_ );
		begin = index_after_if_first ( begin, string_, space<T>::c ( ) );

		if ( prev == begin ) {

			return begin;
		}

		prev = begin;
	}
}

template<typename T, typename = is_string<T>>
FORCE_INLINE void trim_trailing_spaces ( T & string_ ) noexcept {

	while ( string_.back ( ) == space<T>::c ( ) ) string_.pop_back ( );
}

template<typename T, typename = is_string<T>>
FORCE_INLINE void trim_trailing_spaces ( std::vector<T> & string_vector_ ) noexcept {

	for ( auto & string : string_vector_ ) {

		trim_trailing_spaces ( string );
	}
}


template<typename T, typename = is_string<T>>
void string_split ( std::vector<T> & string_vector_, const T & string_, const T & delimiter_ ) {

	std::size_t begin = find_first_not_space_nor_delimiter ( string_, delimiter_ );

	if ( begin < string_.length ( ) ) {

		const std::size_t s_length = string_.length ( ), d_length = delimiter_.length ( );

		std::size_t end = std::min ( string_.find ( delimiter_, begin ), s_length );

		while ( true ) {

			if ( begin < end ) string_vector_.emplace_back ( string_.substr ( begin, end - begin ) );

			end += d_length;

			if ( end >= s_length ) break;

			begin = string_.find_first_not_of ( space<T>::c ( ), end );
			end = std::min ( string_.find ( delimiter_, begin ), s_length );
		}
	}
}

template<typename T, typename = is_string<T>>
void string_split ( std::vector<T> & string_vector_, const typename T::value_type * delimiter_ ) {

	const T delimiter ( delimiter_ );

	std::vector<T> string_vector;

	for ( const T & string : string_vector_ ) {

		string_split ( string_vector, string, delimiter );
	}

	string_vector_ = std::move ( string_vector );
}

template<typename T, typename = is_string<T>>
T string_vector_concat ( std::vector<T> && string_vector_ ) {

	T string;

	for ( T && s : string_vector_ ) {

		string.append ( s );
	}

	return string;
}


#undef FORCE_INLINE
#undef CHARACTER

} // namespace detail


template<typename T, typename ... Delimiters, typename = is_string<T>>
std::vector<T> string_split ( const T & string_, Delimiters ... delimiters_ ) {

	std::vector<T> string_vector { string_ };

	( detail::string_split ( string_vector, std::forward<Delimiters> ( delimiters_ ) ), ... );
	detail::trim_trailing_spaces ( string_vector );

	return string_vector;
}


template<typename T, typename = is_string<T>>
T string_remove ( const T & string_, const T & delimiter_ ) {

	const std::size_t s_length = string_.length ( ), d_length = delimiter_.length ( );

	std::size_t begin = 0;

	T string;

	while ( true ) {

		std::size_t end = std::min ( string_.find ( delimiter_, begin ), s_length );

		if ( begin < end ) string.append ( string_.substr ( begin, end - begin ) );

		end += d_length;

		if ( end >= s_length ) break;

		begin = end;
	}

	return string;
}


} // namespace ss