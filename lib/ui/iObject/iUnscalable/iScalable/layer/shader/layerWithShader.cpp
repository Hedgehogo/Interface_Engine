#include "layerWithShader.hpp"

void operator >>(const YAML::Node& node, uint &transmission){
    std::map<std::string, ui::LayerWithShader::Transmission> transmissionMap {
        {"size", ui::LayerWithShader::Transmission::size},
        {"texture", ui::LayerWithShader::Transmission::texture},
        {"aspectRatio", ui::LayerWithShader::Transmission::aspectRatio},
        {"mousePosition", ui::LayerWithShader::Transmission::mousePosition},
        {"time", ui::LayerWithShader::Transmission::time},
    };

    if(node.IsScalar()) {
        std::string strTransmission = node.as<std::string>();
        transmission = transmissionMap[strTransmission];
    } else if(node.IsSequence()) {
        std::string strTransmission;
        for(const auto &item: node) {
            strTransmission = item.as<std::string>();
            transmission = static_cast<ui::LayerWithShader::Transmission>(transmission | transmissionMap[strTransmission]);
        }
    }
}

namespace ui {
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

    LayerWithShader *LayerWithShader::createFromYaml(const YAML::Node &node) {
        IScalable* object;
        sf::Shader* shader = new sf::Shader{};
        uint transmission{};
        bool optimize{true};
        sf::Vector2f minSize{0, 0};
        node["object"] >> object;
        if (node["transmission"]) node["transmission"] >> transmission;
        if (node["shader"]) node["shader"] >> *shader;
        if (node["optimize"]) node["optimize"] >> optimize;
        if (node["min-size"]) node["min-size"] >> minSize;
        return new LayerWithShader{object, shader, transmission, optimize, minSize};
    }
}
