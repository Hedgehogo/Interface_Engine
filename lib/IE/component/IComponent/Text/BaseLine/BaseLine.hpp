#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"
#include "LineInitInfo/LineInitInfo.hpp"

namespace ie {
	class BaseLine {
	public:
		struct Make {
			virtual BaseLine* make(LineInitInfo init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseLine(sf::PrimitiveType type, size_t vertex_count, orl::Option<sf::Color> color, LineInitInfo init_info);

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