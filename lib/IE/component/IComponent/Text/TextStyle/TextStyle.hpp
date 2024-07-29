#pragma once

#include <option_result/option_result.hpp>
#include <SFML/Graphics.hpp>
#include <box-ptr/BoxPtr.hpp>
#include "../BaseLine/BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"

namespace ie {
	class TextStyleParameterException : std::exception{
	public:
		explicit TextStyleParameterException(const std::string&  name);
	
	private:
		auto what() const noexcept -> char const* override;
		
	protected:
		std::string str;
	};
	
	struct TextStyle {
		sf::Color
			text_color,
			text_selection_color,
			background_selection_color,
			inactive_text_selection_color,
			inactive_background_selection_color;
		size_t size;
		sf::Font& font;
		bool bold;
		bool italic;
		std::vector<bp::BoxPtr<BaseLine> > lines;
		
		explicit TextStyle(
			orl::Option<TextStyle> const& base_stile,
			orl::Option<sf::Color> const& text_color = {},
			orl::Option<sf::Color> const& text_selection_color = {},
			orl::Option<sf::Color> const& background_selection_color = {},
			orl::Option<sf::Color> const& inactive_text_selection_color = {},
			orl::Option<sf::Color> const& inactive_background_selection_color = {},
			orl::Option<size_t> const& size = {},
			orl::Option<sf::Font&> const& font = {},
			orl::Option<bool> const& bold = {},
			orl::Option<bool> const& italic = {},
			orl::Option<std::vector<bp::BoxPtr<BaseLine::Make> > > && lines = {},
			sf::Text::Style const& style = sf::Text::Style::Regular
		);
	};
}

template<>
struct ieml::Decode<char, ie::TextStyle> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextStyle>;
};