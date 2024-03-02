#include "Caption.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	sf::String CaptionString<sf::String>::make(BasicCaption<sf::String>&, sf::String&& make, InitInfo) {
		return std::move(make);
	}
	
	sf::String CaptionString<sf::String>::get(const sf::String& object) {
		return object;
	}
	
	void CaptionString<sf::String>::set(sf::String& first, sf::String const& second) {
		first = second;
	}
	
	SReader<ISString> CaptionString<SReader<ISString> >::make(
		BasicCaption<SReader<ISString> >& caption,
		MakeDyn<ISString>&& make,
		InitInfo init_info
	) {
		const SReader <ISString>& s_reader = SReader<ISString>{
			DynBuffer::get(std::move(make), SInitInfo{init_info}),
			[&caption](std::u32string_view value) {
				caption.set_string(to_utf32(value));
			}
		};
		return s_reader;
	}
	
	sf::String CaptionString<SReader<ISString> >::get(SReader<ISString> const& object) {
		return to_utf32(object.get().get());
	}
	
	void CaptionString<SReader<ISString> >::set(SReader<ISString>&, sf::String const&) {
	}
}
