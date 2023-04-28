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

	    enum class Algorithm{
		    base,
		    console,
		    absolute
	    };

    protected:
        std::vector<BaseCharacter*>* characters;
        std::vector<BaseLine*>* lines;

        const float lineSpacing;
        const Align align;
		const Algorithm algorithm;
    public:
        BaseResizer(float lineSpacing = 1.15, Align align = Align::left, Algorithm algorithm = Algorithm::base);

        void init(std::vector<BaseCharacter*>& characters, std::vector<BaseLine* >& lines);

        virtual void move(sf::Vector2f position) = 0;

        virtual void setPosition(sf::Vector2f position) = 0;

        virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;

		virtual sf::Vector2f getPosition() = 0;

		virtual sf::Vector2f getSize() = 0;

	protected:
		virtual sf::Vector2f getMinSizeBase() = 0;

		virtual sf::Vector2f getMinSizeConsole() = 0;

		virtual sf::Vector2f getMinSizeAbsolute() = 0;

	public:

        virtual sf::Vector2f getMinSize();

        virtual sf::Vector2f getNormalSize() = 0;

        virtual BaseResizer * copy() = 0;

        virtual ~BaseResizer() = default;
    };

	
	
	template<>
	struct Decode<BaseResizer::Align> {
		static bool decode(const YAML::Node &node, BaseResizer::Align &align);
	};

	
	
	template<>
	struct Decode<BaseResizer::Algorithm> {
		static bool decode(const YAML::Node &node, BaseResizer::Algorithm &align);
	};
}