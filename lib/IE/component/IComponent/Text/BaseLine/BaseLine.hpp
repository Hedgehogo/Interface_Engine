#pragma once

#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"
#include "LineInitInfo/LineInitInfo.hpp"

using uint = unsigned;

namespace ie {
	class BaseLine {
	public:
		struct Make {
			virtual BaseLine* make(LineInitInfo init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseLine(sf::PrimitiveType type, size_t vertex_count, orl::Option<sf::Color> color, LineInitInfo init_info);
		
		BaseLine(sf::PrimitiveType type, size_t vertex_count = 0, orl::Option<sf::Color> color = {});
		
		virtual void init(LineInitInfo init_info);
		
		virtual void draw();
		
		virtual void move(sf::Vector2f position);
		
		virtual void resize(float start, float end, float height) = 0;
		
		virtual BaseLine* copy() const = 0;
		
		virtual ~BaseLine() = default;
	
	protected:
		sf::RenderTarget* render_target;
		sf::VertexArray vertex_array;
	};
}