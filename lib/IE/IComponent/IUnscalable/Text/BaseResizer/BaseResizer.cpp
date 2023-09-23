#include "BaseResizer.hpp"

namespace ie {
	BaseResizer* BaseResizer::Make::make(ResizerInitInfo resizerInitInfo) {
		return nullptr;
	}
	
	BaseResizer::BaseResizer(float lineSpacing, BaseResizer::Align align, BaseResizer::Algorithm algorithm, ResizerInitInfo initInfo) :
		characters(&initInfo.characters),
		lines(&initInfo.lines),
		lineSpacing(lineSpacing),
		align(align),
		algorithm(algorithm) {
	}
	
	BaseResizer::BaseResizer(float lineSpacing, Align align, Algorithm algorithm) : characters(nullptr), lines(nullptr), lineSpacing(lineSpacing), align(align), algorithm(algorithm) {
	}
	
	void BaseResizer::init(ResizerInitInfo initInfo) {
		this->characters = &initInfo.characters;
		this->lines = &initInfo.lines;
	}
	
	sf::Vector2f BaseResizer::getMinSize() {
		if(algorithm == Algorithm::Console) {
			return getMinSizeConsole();
		} else if(algorithm == Algorithm::Absolute) {
			return getMinSizeAbsolute();
		}
		return getMinSizeBase();
	}
	
	bool Decode<BaseResizer::Align>::decode(const YAML::Node& node, BaseResizer::Align& align) {
		if(node.as<std::string>() == "left") {
			align = BaseResizer::Align::Left;
		} else if(node.as<std::string>() == "right") {
			align = BaseResizer::Align::Right;
		} else if(node.as<std::string>() == "center") {
			align = BaseResizer::Align::Center;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
	
	bool Decode<BaseResizer::Algorithm>::decode(const YAML::Node& node, BaseResizer::Algorithm& align) {
		if(node.as<std::string>() == "base") {
			align = BaseResizer::Algorithm::Base;
		} else if(node.as<std::string>() == "console") {
			align = BaseResizer::Algorithm::Console;
		} else if(node.as<std::string>() == "absolute") {
			align = BaseResizer::Algorithm::Absolute;
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
}
