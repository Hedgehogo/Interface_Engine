
#include "BaseLine.hpp"

namespace ie {
	BaseLine* BaseLine::Make::make(LineInitInfo) {
		return nullptr;
	}
	
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertexCount, orl::Option<sf::Color> color, LineInitInfo initInfo) : vertexArray(type, vertexCount) {
		sf::Color currentColor;
		if(color.is_some())
			currentColor = color.some();
		else
			currentColor = initInfo.color;
		
		for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
			vertexArray[i].color = currentColor;
		
		this->renderTarget = &initInfo.renderTarget;
	}
	
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertexCount, orl::Option<sf::Color> color) : vertexArray(type, vertexCount) {
		for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
			vertexArray[i].color = color.except();
	}
	
	void BaseLine::init(LineInitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		
		if(vertexArray[0].color == sf::Color{255, 255, 255, 0})
			for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
				vertexArray[i].color = initInfo.color;
	}
	
	void BaseLine::draw() {
		renderTarget->draw(vertexArray);
	}
	
	void BaseLine::move(sf::Vector2f position) {
		for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
			vertexArray[i].position += position;
	}
}
