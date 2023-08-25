#pragma once

#include "../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

using uint = unsigned;

namespace ui {
	class BaseLine {
	public:
		BaseLine(sf::PrimitiveType type, std::size_t vertexCount = 0, sf::Color color = sf::Color{255, 255, 255, 0});
		
		virtual void init(uint, sf::Font&, sf::Color color, sf::RenderTarget& renderTarget);
		
		virtual void draw();
		
		virtual void move(sf::Vector2f position);
		
		virtual void resize(float start, float end, float height) = 0;
		
		virtual BaseLine* copy() = 0;
		
		virtual ~BaseLine() = default;
	
	protected:
		sf::RenderTarget* renderTarget;
		sf::VertexArray vertexArray;
	};
}