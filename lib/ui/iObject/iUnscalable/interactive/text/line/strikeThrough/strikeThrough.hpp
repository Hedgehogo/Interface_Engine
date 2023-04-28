#pragma once

#include "../baseLine.hpp"

namespace ui {
    class StrikeThrough : public BaseLine{
    protected:
        float strikeThroughOffset;
        float underlineThickness;
    public:
        StrikeThrough(sf::Color color = sf::Color{255, 255, 255, 0}, float strikeThroughOffset = 0.3);
        void init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget);
        void resize(float start, float end, float height);
    protected:
        void init(float strikeThroughOffset, float underlineThickness, sf::VertexArray vertexArray, sf::RenderTarget &renderTarget);
    public:
        StrikeThrough* copy();
    };
	
	bool convertPointer(const YAML::Node &node, StrikeThrough *&strikeThrough);
	
	template<>
	struct DecodePointer<StrikeThrough> {
		static bool decodePointer(const YAML::Node &node, StrikeThrough *&strikeThrough);
	};
}