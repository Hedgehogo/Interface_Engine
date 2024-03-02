#include "BaseTextResizer.hpp"

namespace ie {
	BaseTextResizer::BaseTextResizer(
		float line_spacing,
		BaseTextResizer::Align align,
		BaseTextResizer::Algorithm algorithm,
		TextResizerInitInfo init_info
	) :
		characters_(init_info.characters),
		lines_(),
		line_spacing_(line_spacing),
		align_(align),
		algorithm_(algorithm) {
	}

	auto BaseTextResizer::get_lines() const -> std::vector<BoxPtr<BaseLine> > const& {
		return lines_;
	}
	
	auto BaseTextResizer::get_min_size() -> sf::Vector2f {
		if(algorithm_ == Algorithm::Console) {
			return get_min_size_console();
		} else if(algorithm_ == Algorithm::Absolute) {
			return get_min_size_absolute();
		}
		return get_min_size_base();
	}
}

auto ieml::Decode<char, ie::BaseTextResizer::Align>::decode(ieml::Node const& node) -> orl::Option<ie::BaseTextResizer::Align> {
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

auto ieml::Decode<char, ie::BaseTextResizer::Algorithm>::decode(ieml::Node const& node) -> orl::Option<ie::BaseTextResizer::Algorithm> {
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
