#pragma once

#include "../baseResizer.h"

namespace ui {
    class Resizer : public BaseResizer{
    public:
        Resizer(float lineSpacing = 1.15, Align align = Align::left);

        void move(sf::Vector2f position) override;

        void setPosition(sf::Vector2f position) override;

    protected:
        uint distanceEnter = 0;
        uint distanceSpace = 0;

        sf::Vector2f nextPosition;

        sf::Vector2f startRender;
        sf::Vector2f endRender;

        virtual void printCharacter(BaseCharacter *character, float kerning);

        virtual void porting(int i);
        virtual void autoPorting(int i);

        virtual float equalize(uint i);

    public:
        void resize(sf::Vector2f size, sf::Vector2f position) override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        Resizer * copy();

        static Resizer* createFromYaml(const YAML::Node &node);
    };
}