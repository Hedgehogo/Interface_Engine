#pragma once

#include "../BaseResizer.hpp"

namespace ie {
	class Resizer : public BaseResizer {
	public:
		Resizer(float lineSpacing = 1.15, Align align = Align::left, Algorithm algorithm = Algorithm::base);
		
		void move(sf::Vector2f position) override;
		
		void setPosition(sf::Vector2f position) override;
	
	protected:
		virtual void printCharacter(std::vector<BaseCharacter*>::iterator character, float kerning);
		
		virtual void porting(std::vector<BaseCharacter*>::iterator endCharacter);
		
		virtual void autoPorting(std::vector<BaseCharacter*>::iterator endCharacter);
		
		virtual float equalize(std::vector<BaseCharacter*>::iterator endCharacter);
		
		virtual void deleteOldCash(sf::Vector2f size, sf::Vector2f position);
		
		virtual void characterResize(float kerning);
		
		virtual void spaceResize(float kerning);
		
		virtual void fullObjectResize();
		
		virtual void enterResize();
		
		virtual void endLineEqualize();
	
	public:
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getSize() override;
	
	protected:
		sf::Vector2f getMinSizeBase() override;
		
		sf::Vector2f getMinSizeConsole() override;
		
		sf::Vector2f getMinSizeAbsolute() override;
	
	public:
		sf::Vector2f getNormalSize() override;
		
		Resizer* copy();
	
	protected:
		std::vector<BaseCharacter*>::iterator afterEnter;
		std::vector<BaseCharacter*>::iterator afterSpace;
		std::vector<BaseCharacter*>::iterator currentCharacter;
		
		sf::Vector2f nextPosition;
		
		sf::Vector2f startRender;
		sf::Vector2f endRender;
	};
	
	template<>
	struct DecodePointer<Resizer> {
		static bool decodePointer(const YAML::Node& node, Resizer*& resizer);
	};
}