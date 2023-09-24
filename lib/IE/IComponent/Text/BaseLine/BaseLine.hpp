#pragma once

#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "InitInfo/LineInitInfo.hpp"

using uint = unsigned;

namespace ie {
	class BaseLine {
	public:
		struct Make{
			virtual BaseLine* make(LineInitInfo initInfo) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseLine(sf::PrimitiveType type, std::size_t vertexCount, sf::Color color, LineInitInfo initInfo);
		
		BaseLine(sf::PrimitiveType type, std::size_t vertexCount = 0, sf::Color color = sf::Color{255, 255, 255, 0});
		
		virtual void init(LineInitInfo initInfo);
		
		virtual void draw();
		
		virtual void move(sf::Vector2f position);
		
		virtual void resize(float start, float end, float height) = 0;
		
		virtual BaseLine* copy() const = 0;
		
		virtual ~BaseLine() = default;
	
	protected:
		sf::RenderTarget* renderTarget;
		sf::VertexArray vertexArray;
	};
}