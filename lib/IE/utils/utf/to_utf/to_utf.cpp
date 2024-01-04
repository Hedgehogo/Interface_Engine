#include "to_utf.hpp"
#include <codecvt>

namespace ie {
	std::u32string to_utf32(const std::string& str) {
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
		auto as_int = convert.from_bytes(str);
		return std::basic_string<char32_t>{
			reinterpret_cast<char32_t const*>(as_int.data()), as_int.length()
		};
	}
	
	sf::String to_utf32(const std::u32string& str) {
		return std::basic_string<sf::Uint32>{
			reinterpret_cast<sf::Uint32 const*>(str.data()), str.length()
		};
	}
}