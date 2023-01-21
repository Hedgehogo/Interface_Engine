#include "baseResizer.hpp"

namespace ui {
    BaseResizer::BaseResizer(float lineSpacing, Align align, Algorithm algorithm) : lineSpacing(lineSpacing), align(align), algorithm(algorithm ), characters(nullptr), lines(nullptr) {}

    void BaseResizer::init(std::vector<BaseCharacter *> &characters, std::vector<BaseLine *> &lines) {
        this->characters = &characters;
        this->lines = &lines;
    }
	
	template<>
	bool convert(const YAML::Node& node, BaseResizer::Align& align){
		if (node.as<std::string>() == "left") align = BaseResizer::Align::left;
		else if (node.as<std::string>() == "right") align = BaseResizer::Align::right;
		else if (node.as<std::string>() == "center") align = BaseResizer::Align::center;
		else throw YAML::BadConversion{node.Mark()};
		return true;
	}

	template<>
	bool convert(const YAML::Node& node, BaseResizer::Algorithm& align){
		if (node.as<std::string>() == "base") align = BaseResizer::Algorithm::base;
		else if (node.as<std::string>() == "console") align = BaseResizer::Algorithm::console;
		else if (node.as<std::string>() == "absolute") align = BaseResizer::Algorithm::absolute;
		else throw YAML::BadConversion{node.Mark()};
		return true;
	}
}
