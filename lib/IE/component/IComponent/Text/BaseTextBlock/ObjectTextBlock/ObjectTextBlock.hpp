#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "../../BaseCharacter/ObjectCharacter/ObjectCharacter.hpp"

namespace ie {
	class ObjectTextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f size;
			ObjectCharacter::ObjectSpecial special = ObjectCharacter::ObjectSpecial::No;
			
			Make(BoxPtr<IScalable::Make>&& object, const sf::Vector2f& size, bool is_character = true);
			
			Make(BoxPtr<IScalable::Make>&& object, float height);
			
			ObjectTextBlock* make(TextBockInitInfo init_info) override;
		};
		
		ObjectTextBlock(Make&& make, TextBockInitInfo init_info);
		
		void init(TextBockInitInfo text_block_init_info) override;
		
		bool in(sf::Vector2f mouse_position) override;
		
		std::vector<BaseCharacter*> get_characters() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BaseTextBlock* copy() override;
	
	protected:
		ObjectCharacter object_character;
		std::vector<BoxPtr<BaseLine>> lines;
	};
	
	template<>
	struct DecodePointer<ObjectTextBlock> {
		static bool decode_pointer(const YAML::Node& node, ObjectTextBlock*& object_text_block);
	};
}