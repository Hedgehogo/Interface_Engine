#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"
#include "LineInitInfo/LineInitInfo.hpp"

namespace ie {
	class BaseLine {
	public:
		struct Make {
			virtual auto make(LineInitInfo init_info) -> BaseLine* = 0;
			
			virtual ~Make() = default;
		};
		
		BaseLine(sf::PrimitiveType type, size_t vertex_count, orl::Option<sf::Color> color, LineInitInfo init_info);

		virtual auto draw() -> void;
		
		virtual auto move(sf::Vector2f position) -> void;
		
		virtual auto resize(float start, float end, float height) -> void = 0;
		
		virtual auto copy() const -> BaseLine* = 0;
		
		virtual ~BaseLine() = default;
	
	protected:
		sf::RenderTarget* render_target_;
		sf::VertexArray vertex_array_;
	};
}