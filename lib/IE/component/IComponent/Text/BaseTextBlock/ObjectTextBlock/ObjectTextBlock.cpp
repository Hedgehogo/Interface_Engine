#include "ObjectTextBlock.hpp"

namespace ie {
	ObjectTextBlock::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		const sf::Vector2f& size,
		bool is_character
	) : object(std::move(object)),
		size(size),
		special(is_character ? ObjectCharacter::ObjectSpecial::No : ObjectCharacter::ObjectSpecial::Object) {
	}
	
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, float height) : object(std::move(object)), size(0, height),
																				  special(ObjectCharacter::ObjectSpecial::FullLine) {
	}
	
	ObjectTextBlock* ObjectTextBlock::Make::make(TextBockInitInfo init_info) {
		return new ObjectTextBlock{std::move(*this), init_info};
	}
	
	ObjectTextBlock::ObjectTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) :
		BaseTextBlock({}),
		object_character(
			BoxPtr<IScalable>{
				[&]() {
					auto result{make.object->make(static_cast<InitInfo>(init_info))};
					sf::Vector2f min_size{result->get_size()};
					result->set_size({std::max(make.size.x, min_size.x), std::max(make.size.y, min_size.y)});
					return result;
				}()
			},
			make.special
		) {
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mouse_position) {
		return object_character.in(mouse_position);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::get_characters() {
		return std::vector<BaseCharacter*>{&object_character};
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::update_interactions(sf::Vector2f mouse_position) {
		return object_character.update_interactions(mouse_position);
	}
}

orl::Option<ie::ObjectTextBlock::Make> ieml::Decode<char, ie::ObjectTextBlock::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto object{map.at("object").except().as<bp::BoxPtr<ie::IScalable::Make> >().except()};
	for(auto& size: map.at("size").ok_or_none()) {
		auto is_character{map.get_as<bool>("is-character").except().ok_or(true)};
		return {{std::move(object), size.as<sf::Vector2f>().except(), is_character}};
	}
	auto height{map.at("height").except().as<float>().except()};
	return {{std::move(object), height}};
}
