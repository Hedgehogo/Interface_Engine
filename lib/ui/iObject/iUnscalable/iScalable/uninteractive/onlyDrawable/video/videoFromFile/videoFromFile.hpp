#pragma once

#include "ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/onlyDrawable.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"
#include "ui/updatable/iUpdatable/iUpdatable.hpp"

namespace ui {
	class VideoFromFile : public OnlyDrawable{
    protected:
        sf::Vector2i sizeVideo;
        sf::Vector2f size;
		std::string path;

		std::vector<sf::Texture> bufferTexture;
		sf::Sprite sprite;
		PSCoefficient viewingProgress;
    public:

		VideoFromFile(std::string path, PSCoefficient viewingProgress, sf::IntRect rect = {0, 0, 0, 0});

        void setCurrentFrame(float viewingProgress);

        void draw() override;

        sf::Vector2f getAreaPosition() override;

        sf::Vector2f getAreaSize() override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

    protected:
        VideoFromFile(std::vector<sf::Texture> bufferTexture, PSCoefficient viewingProgress);

    public:

        VideoFromFile *copy() override;
    };
}