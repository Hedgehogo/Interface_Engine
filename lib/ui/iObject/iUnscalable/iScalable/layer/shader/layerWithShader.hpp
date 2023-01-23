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
        LayerWithShader(IScalable *var, sf::Shader *shader, uint transmission,
                        std::map<std::string, PISfloat> sharedValuesf = {},
                        std::map<std::string, PISint> sharedValuesi = {},
                        std::map<std::string, PISbool> sharedValuesb = {},
                        std::map<std::string, PISValue<sf::Color>> sharedValuesc = {},
                        std::map<std::string, PSRVec2f> sharedValuesv = {},
                        bool optimize = true, sf::Vector2f minSize = {});

		void setUniform(std::string name, float var);

		void setUniform(std::string name, int var);

		void setUniform(std::string name, bool var);

		void setUniform(std::string name, sf::Color var);

		void setUniform(std::string name, sf::Vector2f var);

        void setSize(sf::Vector2f size) override;

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;
    };
	
	bool convertPointer(const YAML::Node &node, LayerWithShader *&layerWithShader);
}