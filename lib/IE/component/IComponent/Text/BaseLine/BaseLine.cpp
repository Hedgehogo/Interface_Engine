
#include "BaseLine.hpp"

namespace ie {
	BaseLine::BaseLine(sf::PrimitiveType type, size_t vertex_count, orl::Option<sf::Color> color, LineInitInfo init_info) :
		vertex_array_(type, vertex_count), render_target_(&init_info.render_target) {
		auto current_color{std::move(color).some_or({init_info.color})};
		for(auto i{size_t{0}}; i < vertex_array_.getVertexCount(); ++i) {
			vertex_array_[i].color = current_color;
		}
	}
	
	void BaseLine::draw() {
		render_target_->draw(vertex_array_);
	}
	
	void BaseLine::move(sf::Vector2f offset) {
		for(auto i{size_t{0}}; i < vertex_array_.getVertexCount(); ++i) {
			vertex_array_[i].position += offset;
		}
	}
}
