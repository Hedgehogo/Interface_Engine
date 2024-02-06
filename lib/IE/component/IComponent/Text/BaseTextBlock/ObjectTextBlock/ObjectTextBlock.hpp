#pragma once

#include "../BaseTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"
#include "../../BaseCharacter/ObjectCharacter/ObjectCharacter.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

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

		bool in(sf::Vector2f mouse_position) override;
		
		std::vector<BaseCharacter*> get_characters() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
	
	protected:
		ObjectCharacter object_character;
		std::vector<BoxPtr<BaseLine>> lines;
	};
}

template<>
struct ieml::Decode<char, ie::ObjectTextBlock::Make> {
	static orl::Option<ie::ObjectTextBlock::Make> decode(ieml::Node const& node);
};