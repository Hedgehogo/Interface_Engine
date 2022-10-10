#include "layerWithShader.hpp"

namespace ui {
	void convertTransmission(const YAML::Node& node, uint &transmission) {
		std::map<std::string, LayerWithShader::Transmission> transmissionMap {
			{"size", LayerWithShader::Transmission::size},
			{"texture", LayerWithShader::Transmission::texture},
			{"aspectRatio", LayerWithShader::Transmission::aspectRatio},
			{"mousePosition", LayerWithShader::Transmission::mousePosition},
			{"time", LayerWithShader::Transmission::time},
		};
		
		if(node.IsScalar()) {
			std::string strTransmission = node.as<std::string>();
			transmission = transmissionMap[strTransmission];
		} else if(node.IsSequence()) {
			std::string strTransmission;
			for(const auto &item: node) {
				strTransmission = item.as<std::string>();
				transmission = static_cast<LayerWithShader::Transmission>(transmission | transmissionMap[strTransmission]);
			}
		}
	}
	
    LayerWithShader::LayerWithShader(IScalable *object, sf::Shader *shader, uint transmission, bool optimize, sf::Vector2f minSize) :
        LayerWithRenderTexture(object, optimize, minSize), shader(shader), transmission(transmission){
        clock.restart();
    }

    void LayerWithShader::draw() {
        if(!optimize || active || interactionManager->isBlocked()) {
            renderTexture.clear(sf::Color(0, 0, 0, 0));
            drawManager.draw();
            sprite.setTexture(renderTexture.getTexture());
            active = false;

        }
        if (transmission & Transmission::time) shader->setUniform("time", clock.getElapsedTime().asSeconds());
        if (transmission & Transmission::texture) shader->setUniform("texture", renderTexture.getTexture());
        renderTarget->draw(sprite, shader);
    }

    void LayerWithShader::setSize(sf::Vector2f size) {
        if (transmission & Transmission::size) shader->setUniform("size", size);
        if (transmission & Transmission::aspectRatio) shader->setUniform("aspectRatio", size.x / size.y);
        Layout::setSize(size);
    }

    void LayerWithShader::resize(sf::Vector2f size, sf::Vector2f position) {
        if (transmission & Transmission::size) shader->setUniform("size", size);
        if (transmission & Transmission::aspectRatio) shader->setUniform("aspectRatio", size.x / size.y);
        LayerWithRenderTexture::resize(size, position);
    }

    bool LayerWithShader::updateInteractions(sf::Vector2f mousePosition) {
        if (transmission & Transmission::mousePosition) shader->setUniform("mousePosition", mousePosition - position);
        return LayerWithRenderTexture::updateInteractions(mousePosition);
    }

    bool convertPointer(const YAML::Node &node, LayerWithShader *&layerWithShader) {
        IScalable* object;
        sf::Shader* shader = new sf::Shader{};
        uint transmission{};
        bool optimize{true};
        sf::Vector2f minSize{0, 0};
        node["object"] >> object;
        if (node["transmission"]) convertTransmission(node["transmission"], transmission);
        if (node["shader"]) node["shader"] >> *shader;
        if (node["optimize"]) node["optimize"] >> optimize;
        if (node["min-size"]) node["min-size"] >> minSize;
        { layerWithShader = new LayerWithShader{object, shader, transmission, optimize, minSize}; return true; }
    }
}
