#include "Underline.hpp"

namespace ie {
	Underline::Make::Make(const sf::Color& color) : color(color) {
	}
	
	Underline* Underline::Make::make(LineInitInfo initInfo) {
		return new Underline{std::move(*this), initInfo};
	}
	
	Underline::Underline(Make&& make, LineInitInfo initInfo) : BaseLine(sf::TriangleStrip, 4, make.color, initInfo) {
		underlineOffset = initInfo.font.getUnderlinePosition(initInfo.size);
		underlineThickness = initInfo.font.getUnderlineThickness(initInfo.size);
	}
	
	Underline::Underline(sf::Color color) : BaseLine(sf::TriangleStrip, 4, color) {
	}
	
	void Underline::init(LineInitInfo initInfo) {
		BaseLine::init(initInfo);
		
		underlineOffset = initInfo.font.getUnderlinePosition(initInfo.size);
		underlineThickness = initInfo.font.getUnderlineThickness(initInfo.size);
	}
	
	void Underline::resize(float start, float end, float height) {
		vertexArray[0].position = {start, height + underlineOffset - (underlineThickness / 2)};
		vertexArray[1].position = {start, height + underlineOffset + (underlineThickness / 2)};
		vertexArray[2].position = {end, height + underlineOffset - (underlineThickness / 2)};
		vertexArray[3].position = {end, height + underlineOffset + (underlineThickness / 2)};
	}
	
	Underline* Underline::copy() const{
		return new Underline{*this};
	}
	
	bool DecodePointer<Underline>::decodePointer(const YAML::Node& node, Underline*& underline) {
		underline = new Underline{convDef(node["color"], nullColor)};
		return true;
	}
}