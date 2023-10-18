
#include "BaseLine.hpp"

namespace ie {
	BaseLine* BaseLine::Make::make(LineInitInfo) {
		return nullptr;
	}
	
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertex_count, orl::Option<sf::Color> color, LineInitInfo init_info) : vertex_array(type, vertex_count) {
		sf::Color current_color;
		if(color.is_some())
			current_color = color.some();
		else
			current_color = init_info.color;
		
		for(std::size_t i = 0; i < vertex_array.getVertexCount(); ++i)
			vertex_array[i].color = current_color;
		
		this->render_target = &init_info.render_target;
	}
	
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertex_count, orl::Option<sf::Color> color) : vertex_array(type, vertex_count) {
		for(std::size_t i = 0; i < vertex_array.getVertexCount(); ++i)
			vertex_array[i].color = color.except();
	}
	
	void BaseLine::init(LineInitInfo init_info) {
		this->render_target = &init_info.render_target;
		
		if(vertex_array[0].color == sf::Color{255, 255, 255, 0})
			for(std::size_t i = 0; i < vertex_array.getVertexCount(); ++i)
				vertex_array[i].color = init_info.color;
	}
	
	void BaseLine::draw() {
		render_target->draw(vertex_array);
	}
	
	void BaseLine::move(sf::Vector2f position) {
		for(std::size_t i = 0; i < vertex_array.getVertexCount(); ++i)
			vertex_array[i].position += position;
	}
}
