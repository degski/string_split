
#pragma once

#include <iostream>

// Escape sequences...

std::ostream &  nl ( std::ostream  & out_ ) { return out_ <<  '\n'; }
std::wostream & nl ( std::wostream & out_ ) { return out_ << L'\n'; }

std::ostream &  np ( std::ostream  & out_ ) { return out_ <<  '\f'; }
std::wostream & np ( std::wostream & out_ ) { return out_ << L'\f'; }

std::ostream &  cr ( std::ostream  & out_ ) { return out_ <<  '\r'; }
std::wostream & cr ( std::wostream & out_ ) { return out_ << L'\r'; }

std::ostream &  bs ( std::ostream  & out_ ) { return out_ <<  '\b'; }
std::wostream & bs ( std::wostream & out_ ) { return out_ << L'\b'; }

std::ostream &  sp ( std::ostream  & out_ ) { return out_ <<  ' '; }
std::wostream & sp ( std::wostream & out_ ) { return out_ << L' '; }

std::ostream &  ab ( std::ostream  & out_ ) { return out_ <<  '\a'; }
std::wostream & ab ( std::wostream & out_ ) { return out_ << L'\a'; }

std::ostream &  ht ( std::ostream  & out_ ) { return out_ <<  '\t'; }
std::wostream & ht ( std::wostream & out_ ) { return out_ << L'\t'; }

std::ostream &  vt ( std::ostream  & out_ ) { return out_ <<  '\v'; }
std::wostream & vt ( std::wostream & out_ ) { return out_ << L'\v'; }

// Spaced dash...

std::ostream &  sd ( std::ostream  & out_ ) { return out_ <<  " - "; }
std::wostream & sd ( std::wostream & out_ ) { return out_ << L" - "; }
