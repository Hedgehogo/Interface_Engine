#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/ObjectCharacter/ObjectCharacter.hpp"

namespace ie {
	class ObjectTextBlock : public BaseTextBlock {
	public:
		struct Make : public BaseTextBlock::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f size = {0, 0};
			bool is_character = true;
			float height = 0;
			bool full_line;
			
			explicit Make(BoxPtr<IScalable::Make>&& object, const sf::Vector2f& size = {0, 0}, bool is_character = true);
			
			Make(BoxPtr<IScalable::Make>&& object, float height);
			
			ObjectTextBlock* make(TextBockInitInfo text_block_init_info) override;
		};
		
		ObjectTextBlock(Make&& make, TextBockInitInfo text_block_init_info);
		
		void init(TextBockInitInfo text_block_init_info) override;
		
		bool in(sf::Vector2f mouse_position) override;
		
		std::vector<BaseCharacter*> get_characters() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BaseTextBlock* copy() override;
	
	protected:
		std::vector<BoxPtr<BaseLine>> lines;
		bool is_character;
		BoxPtr<ObjectCharacter> object_character;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ObjectTextBlock> {
		static bool decode_pointer(const YAML::Node& node, ObjectTextBlock*& object_text_block);
	};
	*/
}