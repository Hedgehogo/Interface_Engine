#pragma once

#include "../onlyDrawable.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"
#include "ui/updatable/iUpdatable/iUpdatable.hpp"

namespace ui {
	class Video : public OnlyDrawable{
    protected:
        sf::Vector2i sizeVideo;
        sf::Vector2f size;
		std::string path;

		std::vector<sf::Texture> bufferTexture;
		sf::Sprite sprite;
		PSCoefficient viewingProgress;
    public:

		Video(std::string path, PSCoefficient viewingProgress, sf::IntRect rect = {0, 0, 0, 0});

        void setCurrentFrame(float viewingProgress);

        void draw() override;

        sf::Vector2f getAreaPosition() override;

        sf::Vector2f getAreaSize() override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

    protected:
        Video(std::vector<sf::Texture> bufferTexture, PSCoefficient viewingProgress);

    public:

        Video *copy() override;
    };

    bool convertPointer(const YAML::Node &node, Video *&video);
}