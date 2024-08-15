#pragma once

#include <option_result/option_result.hpp>
#include "LineInitInfo/LineInitInfo.hpp"

namespace ie {
	class BaseLine {
	public:
		struct MainLine {
			struct Make {
				sf::PrimitiveType type;
				size_t vertex_count;
				orl::Option<sf::Color> color;
				
				Make(sf::PrimitiveType type, size_t vertex_count, const orl::Option<sf::Color>& color);
				
				virtual auto make(LineInitInfo init_info) -> MainLine* = 0;
				
				virtual auto copy() -> Make* = 0;
				
				virtual ~Make() = default;
			};
			
			sf::VertexArray vertex_array_;
			bool text_color_;
			
			MainLine(Make const& make, LineInitInfo init_info);
			
			virtual auto reinit(LineInitInfo init_info) -> void;
			
			virtual auto copy() -> MainLine* = 0;
			
			virtual auto make() -> BaseLine* = 0;
			
			virtual ~MainLine() = default;
		};
		
		BaseLine(MainLine const& main_line);

		virtual auto draw(sf::RenderTarget* render_target) -> void;
		
		virtual auto move(sf::Vector2f offset) -> void;
		
		virtual auto resize(float start, float end, float height) -> void = 0;
		
		virtual auto copy() const -> BaseLine* = 0;
		
		virtual ~BaseLine() = default;
	
	protected:
		sf::VertexArray vertex_array_;
	};
}