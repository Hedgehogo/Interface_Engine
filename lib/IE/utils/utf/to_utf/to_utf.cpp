#include "to_utf.hpp"
#include <codecvt>

namespace ie {
	auto to_utf32(std::string_view str) -> std::u32string {
		auto convert{std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}};
		auto as_int{convert.from_bytes(str.data())};
		return std::u32string{reinterpret_cast<char32_t const*>(as_int.data()), as_int.length()};
	}
	
	auto to_utf32(std::u32string_view str) -> sf::String {
		return std::basic_string<sf::Uint32>{
			reinterpret_cast<sf::Uint32 const*>(str.data()), str.length()
		};
	}
}