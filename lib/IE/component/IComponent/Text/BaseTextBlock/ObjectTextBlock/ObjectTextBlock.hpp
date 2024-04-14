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
			
			auto make(TextBockInitInfo init_info) -> ObjectTextBlock* override;
		};
		
		ObjectTextBlock(Make&& make, TextBockInitInfo init_info);

		auto in(sf::Vector2f point_position) -> bool override;
		
		auto get_characters() -> std::vector<BaseCharacter*> override;
		
		auto update() -> void override;
		
		auto update_interactions(Event event) -> bool override;
	
	protected:
		ObjectCharacter object_character_;
		std::vector<BoxPtr<BaseLine> > lines_;
	};
}

template<>
struct ieml::Decode<char, ie::ObjectTextBlock::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ObjectTextBlock::Make>;
};