#include "baseResizer.hpp"

namespace ui {
    BaseResizer::BaseResizer(float lineSpacing, Align align) : lineSpacing(lineSpacing), align(align), characters(nullptr), lines(nullptr) {}

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
}
