#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		Underline(sf::Color color = nullColor);
		
		void init(uint size, sf::Font& font, sf::Color color, sf::RenderTarget& renderTarget);
		
		void resize(float start, float end, float height);
	
	protected:
		void init(float underlineOffset, float underlineThickness, sf::VertexArray vertexArray, sf::RenderTarget& renderTarget);
	
	public:
		Underline* copy();
	
	protected:
		float underlineOffset;
		float underlineThickness;
	};
	
	template<>
	struct DecodePointer<Underline> {
		static bool decodePointer(const YAML::Node& node, Underline*& underline);
	};
}