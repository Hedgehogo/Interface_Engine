#include "ObjectTextBlock.hpp"

namespace ie {
	ObjectTextBlock::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		const sf::Vector2f& size,
		bool is_character
	) :
		object(std::move(object)),
		size(size),
		special(is_character ? ObjectCharacter::ObjectSpecial::No : ObjectCharacter::ObjectSpecial::Object) {
	}
	
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, float height) :
		object(std::move(object)), size(0, height), special(ObjectCharacter::ObjectSpecial::FullLine) {
	}
	
	auto ObjectTextBlock::Make::make(TextBockInitInfo init_info) -> ObjectTextBlock* {
		return new ObjectTextBlock{std::move(*this), init_info};
	}
	
	ObjectTextBlock::ObjectTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) :
		BaseTextBlock({}),
		object_character_(
			BoxPtr<IScalable>{
				[&]() {
					auto result{make.object->make(static_cast<InitInfo>(init_info))};
					auto min_size{result->get_size()};
					result->set_size({std::max(make.size.x, min_size.x), std::max(make.size.y, min_size.y)});
					return result;
				}()
			},
			make.special
		) {
	}
	
	auto ObjectTextBlock::in(sf::Vector2f point_position) -> bool {
		return object_character_.in(point_position);
	}
	
	auto ObjectTextBlock::get_characters() -> std::vector<BaseCharacter*> {
		return std::vector<BaseCharacter*>{&object_character_};
	}
	
	auto ObjectTextBlock::update() -> void {
	}
	
	auto ObjectTextBlock::update_interactions(Event event) -> bool {
		return object_character_.update_interactions(event);
	}
}

auto ieml::Decode<char, ie::ObjectTextBlock::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ObjectTextBlock::Make> {
	auto map{node.get_map_view().except()};
	auto object{map.at("object").except().as<bp::BoxPtr<ie::IScalable::Make> >().except()};
	for(auto& size: map.at("size").ok_or_none()) {
		auto is_character{map.get_as<bool>("is-character").except().ok_or(true)};
		return {{std::move(object), size.as<sf::Vector2f>().except(), is_character}};
	}
	auto height{map.at("height").except().as<float>().except()};
	return {{std::move(object), height}};
}
