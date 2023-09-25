#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/ObjectCharacter/ObjectCharacter.hpp"

namespace ie {
	class ObjectTextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f size = {0, 0};
			bool isCharacter = true;
			float height = 0;
			bool fullLine;
			
			explicit Make(BoxPtr<IScalable::Make>&& object, const sf::Vector2f& size = {0, 0}, bool isCharacter = true);
			
			Make(BoxPtr<IScalable::Make>&& object, float height);
			
			ObjectTextBlock* make(TextBockInitInfo textBlockInitInfo) override;
		};
		
		ObjectTextBlock(Make&& make, TextBockInitInfo textBlockInitInfo);
		
		void init(TextBockInitInfo textBlockInitInfo) override;
		
		bool in(sf::Vector2f mousePosition) override;
		
		std::vector<BaseCharacter*> getCharacters() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BaseTextBlock* copy() override;
	
	protected:
		std::vector<BoxPtr<BaseLine>> lines;
		bool isCharacter;
		BoxPtr<ObjectCharacter> objectCharacter;
	};
	
	template<>
	struct DecodePointer<ObjectTextBlock> {
		static bool decodePointer(const YAML::Node& node, ObjectTextBlock*& objectTextBlock);
	};
}