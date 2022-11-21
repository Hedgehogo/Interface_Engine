#pragma once

#include "../character/baseCharacter.hpp"

namespace ui {
    class BaseResizer {
    public:
        enum Align{
            left,
            right,
            center
        };
    protected:
        std::vector<BaseCharacter*>* characters;
        std::vector<BaseLine*>* lines;

        float lineSpacing;
        Align align;
    public:
        BaseResizer(float lineSpacing = 1.15, Align align = Align::left);

        void init(std::vector<BaseCharacter*>& characters, std::vector<BaseLine* >& lines);

        virtual void move(sf::Vector2f position) = 0;

        virtual void setPosition(sf::Vector2f position) = 0;

        virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;

		virtual sf::Vector2f getPosition() = 0;

		virtual sf::Vector2f getSize() = 0;

        virtual sf::Vector2f getMinSize() = 0;

        virtual sf::Vector2f getNormalSize() = 0;

        virtual BaseResizer * copy() = 0;

        virtual ~BaseResizer() = default;
    };
	
	template<>
	bool convert(const YAML::Node &node, BaseResizer::Align &align);
}