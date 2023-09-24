
#include "BaseLine.hpp"

namespace ie {
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertexCount, sf::Color color, LineInitInfo initInfo) : vertexArray(type, vertexCount) {
		for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
			vertexArray[i].color = color;
		
		this->renderTarget = &initInfo.renderTarget;
		
		if(vertexArray[0].color == sf::Color{255, 255, 255, 0})
			for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
				vertexArray[i].color = initInfo.color;
	}
	
	BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertexCount, sf::Color color) : vertexArray(type, vertexCount) {
		for(std::size_t i = 0; i < vertexArray.getVertexCount(); ++i)
			vertexArray[i].color = color;
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
