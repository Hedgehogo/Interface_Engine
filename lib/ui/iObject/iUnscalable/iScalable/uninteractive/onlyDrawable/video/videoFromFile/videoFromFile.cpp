#include "videoFromFile.hpp"
#include <Magick++.h>

namespace ui {

    VideoFromFile::VideoFromFile(std::string path, PSCoefficient viewingProgress, sf::IntRect rect) :
            path(path), viewingProgress(viewingProgress){
        viewingProgress->addSetter([=](float viewingProgress){ setCurrentFrame(viewingProgress);});

        std::list<Magick::Image> images;
        Magick::readImages(&images, path);

        bufferTexture.resize(images.size());

        rect.width = images.begin()->baseColumns();
        rect.height = images.begin()->baseRows();
        sizeVideo = {rect.width, rect.height};

        int i = 0;
        for (auto &frame : images) {
            frame.magick("RGBA");
            frame.backgroundColor(Magick::Color("transparent"));
            frame.extent({static_cast<size_t>(rect.width), static_cast<size_t>(rect.height)}, Magick::CenterGravity);

            sf::Image sfImage;
            sfImage.create(rect.width, rect.height);
            for (int x = rect.left; x < rect.left + rect.width; ++x) {
                for (int y = rect.top; y < rect.top + rect.height; ++y) {
                    Magick::Color pixel = frame.pixelColor(x, y);
                    sfImage.setPixel(x, y, {
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumRed() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumGreen() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumBlue() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumAlpha() * 255),
                        }
                    );
                }
            }
            bufferTexture[i].loadFromImage(sfImage);
            ++i;
        }
        sprite.setTexture(bufferTexture[0]);
    }

    void VideoFromFile::setCurrentFrame(float viewingProgress) {
        if (viewingProgress >= 1) {
            sprite.setTexture(bufferTexture[bufferTexture.size()]);
            return;
        }
        if (viewingProgress <= 0){
            sprite.setTexture(bufferTexture[0]);
            return;
        }
        sprite.setTexture(bufferTexture[bufferTexture.size() * viewingProgress]);
    }

    void VideoFromFile::draw() {
		renderTarget->draw(sprite);
    }

    void VideoFromFile::resize(sf::Vector2f size, sf::Vector2f position) {
        this->size = size;
        sprite.setPosition(position);
        sprite.setScale(size / sf::Vector2f{sizeVideo});
    }

    sf::Vector2f VideoFromFile::getAreaPosition() {
        return sprite.getPosition();
    }

    sf::Vector2f VideoFromFile::getAreaSize() {
        return size;
    }

    sf::Vector2f VideoFromFile::getMinSize() {
        return {0, 0};
    }

    sf::Vector2f VideoFromFile::getNormalSize() {
        return sf::Vector2f{sizeVideo};
    }

    VideoFromFile::VideoFromFile(std::vector<sf::Texture> bufferTexture, PSCoefficient viewingProgress) : bufferTexture(bufferTexture), viewingProgress(viewingProgress) {}

    VideoFromFile *VideoFromFile::copy() {
        VideoFromFile* video{new VideoFromFile{bufferTexture, viewingProgress}};
        OnlyDrawable::copy(video);
        return video;
    }
}