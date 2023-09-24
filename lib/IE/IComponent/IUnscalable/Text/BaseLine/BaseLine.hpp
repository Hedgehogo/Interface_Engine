#pragma once

#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "InitInfo/LineInitInfo.hpp"

using uint = unsigned;

namespace ie {
	class BaseLine {
	public:
		struct Make{
			virtual BaseLine* make(LineInitInfo initInfo);
		};
		
		BaseLine(sf::PrimitiveType type, std::size_t vertexCount, orl::Option<sf::Color> color, LineInitInfo initInfo);
		
		BaseLine(sf::PrimitiveType type, std::size_t vertexCount = 0, orl::Option<sf::Color> color = {});
		
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