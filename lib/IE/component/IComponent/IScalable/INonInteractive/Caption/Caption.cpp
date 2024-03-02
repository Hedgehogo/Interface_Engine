#include "Caption.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	auto CaptionString<sf::String>::make(BasicCaption<sf::String>&, sf::String&& make, InitInfo) -> sf::String {
		return std::move(make);
	}
	
	auto CaptionString<sf::String>::get(sf::String const& object) -> sf::String {
		return object;
	}
	
	auto CaptionString<sf::String>::set(sf::String& first, sf::String const& second) -> void {
		first = second;
	}
	
	SReader<ISString> CaptionString<SReader<ISString> >::make(
		BasicCaption<SReader<ISString> >& caption,
		MakeDyn<ISString>&& make,
		InitInfo init_info
	) {
		return SReader<ISString>{
			DynBuffer::get(std::move(make), SInitInfo{init_info}),
			[&caption](std::u32string_view value) {
				caption.set_string(to_utf32(value));
			}
		};
	}
	
	auto CaptionString<SReader<ISString> >::get(SReader<ISString> const& object) -> sf::String {
		return to_utf32(object.get().get());
	}
	
	auto CaptionString<SReader<ISString> >::set(SReader<ISString>&, sf::String const&) -> void {
	}
}
