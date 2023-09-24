#include "StrikeThrough.hpp"

namespace ie {
	StrikeThrough::Make::Make(const sf::Color& color, float strikeThroughOffset) : color(color), strikeThroughOffset(strikeThroughOffset) {
	}
	
	BaseLine* StrikeThrough::Make::make(LineInitInfo initInfo) {
		return new StrikeThrough{std::move(*this), initInfo};
	}
	
	StrikeThrough::StrikeThrough(Make&& make, LineInitInfo initInfo) : BaseLine(sf::TriangleStrip, 4, make.color, initInfo), strikeThroughOffset(make.strikeThroughOffset) {
		strikeThroughOffset *= initInfo.size;
		underlineThickness = initInfo.font.getUnderlineThickness(initInfo.size);
	}
	
	StrikeThrough::StrikeThrough(sf::Color color, float strikeThroughOffset) : BaseLine(sf::TriangleStrip, 4, color), strikeThroughOffset(strikeThroughOffset) {
	}
	
	void StrikeThrough::init(LineInitInfo initInfo) {
		BaseLine::init(initInfo);
		
		strikeThroughOffset *= initInfo.size;
		underlineThickness = initInfo.font.getUnderlineThickness(initInfo.size);
	}
	
	void StrikeThrough::resize(float start, float end, float height) {
		vertexArray[0].position = {start, height - strikeThroughOffset - (underlineThickness / 2)};
		vertexArray[1].position = {start, height - strikeThroughOffset + (underlineThickness / 2)};
		vertexArray[2].position = {end, height - strikeThroughOffset - (underlineThickness / 2)};
		vertexArray[3].position = {end, height - strikeThroughOffset + (underlineThickness / 2)};
	}
	
	StrikeThrough* StrikeThrough::copy() const{
		return new StrikeThrough{*this};
	}
	
	bool DecodePointer<StrikeThrough>::decodePointer(const YAML::Node& node, StrikeThrough*& strikeThrough) {
		sf::Color color{nullColor};
		float strikeThroughOffset = 0.3;
		if(node["color"])
			node["color"] >> color;
		if(node["strike-through-offset"])
			node["strike-through-offset"] >> strikeThroughOffset;
		{
			strikeThrough = new StrikeThrough{color, strikeThroughOffset};
			return true;
		}
	}
}