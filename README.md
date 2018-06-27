# string_split
A string splitter allowing strings as delimiters, written in C++17.

Pass in a STL-string, followed by the delimiters. The order of the passed in delimiters is important as the delimiters are applied left to right on the (sub-strings) of the previous parsing pass.

It's header only, with no other dependencies than the STL.
