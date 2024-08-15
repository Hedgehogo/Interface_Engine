
#include "BaseLine.hpp"

namespace ie {
	namespace detail {
		auto setColor(sf::VertexArray& vertex_array, sf::Color color) -> void {
			for(auto i{size_t{0}}; i < vertex_array.getVertexCount(); ++i) {
				vertex_array[i].color = color;
			}
		}
	}
	
	BaseLine::MainLine::Make::Make(
		sf::PrimitiveType type,
		size_t vertex_count,
		const orl::Option<sf::Color>& color
	) :
		type(type),
		vertex_count(vertex_count),
		color(color) {
	}
	
	BaseLine::MainLine::MainLine(Make const& make, LineInitInfo init_info) :
		vertex_array_(make.type, make.vertex_count), text_color_(!make.color.is_some()) {
		detail::setColor(vertex_array_, make.color.some_or({init_info.color}));
	}
	
	auto BaseLine::MainLine::reinit(LineInitInfo init_info) -> void {
		if(text_color_) {
			detail::setColor(vertex_array_, init_info.color);
		}
	}
	
	BaseLine::BaseLine(BaseLine::MainLine const& main_line) : vertex_array_(main_line.vertex_array_){
	}
	
	void BaseLine::draw(sf::RenderTarget* render_target) {
		render_target->draw(vertex_array_);
	}
	
	void BaseLine::move(sf::Vector2f offset) {
		for(auto i{size_t{0}}; i < vertex_array_.getVertexCount(); ++i) {
			vertex_array_[i].position += offset;
		}
	}
}
