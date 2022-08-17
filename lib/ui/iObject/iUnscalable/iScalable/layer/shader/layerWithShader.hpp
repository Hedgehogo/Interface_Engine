#pragma once

#include "../renderTexture/layerWithRenderTexture.hpp"

namespace ui {
    class LayerWithShader : public LayerWithRenderTexture{
    public:
        enum Transmission{
            texture = 1 << 0,
            mousePosition = 1 << 1,
            size = 1 << 2,
            aspectRatio = 1 << 3,
            time = 1 << 4,
        };
    protected:
        sf::Shader *shader;
        uint transmission;

        sf::Clock clock;
    public:
        LayerWithShader(IScalable *object, sf::Shader *shader, uint transmission, bool optimize = true, sf::Vector2f minSize = {});

        void setSize(sf::Vector2f size) override;

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        static LayerWithShader* createFromYaml(const YAML::Node &node);
    };
}