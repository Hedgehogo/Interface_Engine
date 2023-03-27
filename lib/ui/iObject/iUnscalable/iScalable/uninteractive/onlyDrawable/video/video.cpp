#include "video.h"
#include <Magick++.h>
#include <iostream>

namespace ui {

    Video::Video(std::string path, PSCoefficient viewingProgress, sf::IntRect rect) :
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
            std::cout << "Frame: " << i << "; Width: " << frame.baseColumns() << "; Height: " << frame.baseRows() << std::endl;
            for (int x = rect.left; x < rect.left + rect.width; ++x) {
                std::cout << x << (x - 10 < 0 ? " " : "") << " > ";
                for (int y = rect.top; y < rect.top + rect.height; ++y) {
                    Magick::Color pixel = frame.pixelColor(x, y);
                    sfImage.setPixel(x, y, {
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumRed() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumGreen() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumBlue() * 255),
                            static_cast<sf::Uint8>(QuantumScale * pixel.quantumAlpha() * 255),
                        }
                    );

                    printf(" [ %02x ", static_cast<sf::Uint8>(QuantumScale * pixel.quantumRed()   * 255));
                    printf("%02x ",    static_cast<sf::Uint8>(QuantumScale * pixel.quantumGreen() * 255));
                    printf("%02x ",    static_cast<sf::Uint8>(QuantumScale * pixel.quantumBlue()  * 255));
                    printf("%02x ]",   static_cast<sf::Uint8>(QuantumScale * pixel.quantumAlpha() * 255));
                }
                std::cout << std::endl;
            }
            bufferTexture[i].loadFromImage(sfImage);
            ++i;
        }
        sprite.setTexture(bufferTexture[0]);
    }

    void Video::setCurrentFrame(float viewingProgress) {
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

    void Video::draw() {
		renderTarget->draw(sprite);
    }

    void Video::resize(sf::Vector2f size, sf::Vector2f position) {
        this->size = size;
        sprite.setPosition(position);
        sprite.setScale(size / sf::Vector2f{sizeVideo});
    }

    sf::Vector2f Video::getAreaPosition() {
        return sprite.getPosition();
    }

    sf::Vector2f Video::getAreaSize() {
        return size;
    }

    sf::Vector2f Video::getMinSize() {
        return {0, 0};
    }

    sf::Vector2f Video::getNormalSize() {
        return sf::Vector2f{sizeVideo};
    }

    Video::Video(std::vector<sf::Texture> bufferTexture, PSCoefficient viewingProgress) : bufferTexture(bufferTexture), viewingProgress(viewingProgress) {}

    Video *Video::copy() {
        Video* video{new Video{bufferTexture, viewingProgress}};
        OnlyDrawable::copy(video);
        return video;
    }

    bool convertPointer(const YAML::Node &node, Video *&video){
        video = new Video{
            node["path"].as<std::string>(),
            Buffer::get<SCoefficientValue>(node["viewing-progress"]),
            convDef(node["rect"], sf::IntRect{0, 0, 0, 0})
        };
        return true;
    }
}