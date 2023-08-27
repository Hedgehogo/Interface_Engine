#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/ObjectCharacter/ObjectCharacter.hpp"

namespace ie {
	class ObjectTextBlock : public BaseTextBlock {
	public:
		ObjectTextBlock(IScalable* object, sf::Vector2f size = {0, 0}, bool isCharacter = true);
		
		ObjectTextBlock(IScalable* object, float height);
		
		void init(InitInfo, InitInfo initInfo) override;
		
		bool in(sf::Vector2f mousePosition) override;
		
		std::vector<BaseCharacter*> getCharacters() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BaseTextBlock* copy() override;
	
	protected:
		std::vector<BaseLine*> lines;
		sf::Vector2f size;
		ObjectCharacter* objectCharacter;
		bool isCharacter;
		bool fullLine;
		IScalable* object;
	};
	
	template<>
	struct DecodePointer<ObjectTextBlock> {
		static bool decodePointer(const YAML::Node& node, ObjectTextBlock*& objectTextBlock);
	};
}