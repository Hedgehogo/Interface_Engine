#include "BaseTextResizer.hpp"

namespace ie {
	BaseTextResizer::BaseTextResizer(float line_spacing, BaseTextResizer::Align align, BaseTextResizer::Algorithm algorithm, TextResizerInitInfo init_info) :
		characters(init_info.characters),
		lines(),
		line_spacing(line_spacing),
		align(align),
		algorithm(algorithm) {
	}

	const std::vector<BoxPtr<BaseLine> >& BaseTextResizer::get_lines() const {
		return lines;
	}
	
	sf::Vector2f BaseTextResizer::get_min_size() {
		if(algorithm == Algorithm::Console) {
			return get_min_size_console();
		} else if(algorithm == Algorithm::Absolute) {
			return get_min_size_absolute();
		}
		return get_min_size_base();
	}
}

orl::Option<ie::BaseTextResizer::Align> ieml::Decode<char, ie::BaseTextResizer::Align>::decode(ieml::Node const& node) {
	auto& str{node.get_clear().get_string().except()};
	if(str == "left") {
		return ie::BaseTextResizer::Align::Left;
	} else if(str == "right") {
		return ie::BaseTextResizer::Align::Right;
	} else if(str == "center") {
		return ie::BaseTextResizer::Align::Center;
	}
	return {};
}

orl::Option<ie::BaseTextResizer::Algorithm> ieml::Decode<char, ie::BaseTextResizer::Algorithm>::decode(ieml::Node const& node) {
	auto& str{node.get_clear().get_string().except()};
	if(str == "base") {
		return ie::BaseTextResizer::Algorithm::Base;
	} else if(str == "console") {
		return ie::BaseTextResizer::Algorithm::Console;
	} else if(str == "absolute") {
		return ie::BaseTextResizer::Algorithm::Absolute;
	}
	return {};
}
