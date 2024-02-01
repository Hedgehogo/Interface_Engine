#include "ObjectTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"

namespace ie {
	ObjectTextBlock::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		const sf::Vector2f& size,
		bool is_character
	) : object(std::move(object)),
		size(size),
		special(is_character ? ObjectCharacter::ObjectSpecial::No : ObjectCharacter::ObjectSpecial::Object) {
	}
	
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, float height) : object(std::move(object)), size(0, height), special(ObjectCharacter::ObjectSpecial::FullLine) {
	}
	
	ObjectTextBlock* ObjectTextBlock::Make::make(TextBockInitInfo init_info) {
		return new ObjectTextBlock{std::move(*this), init_info};
	}
	
	ObjectTextBlock::ObjectTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) :
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
	
	void ObjectTextBlock::init(TextBockInitInfo) {
		throw std::runtime_error("ObjectTextBlock::init() not correct");
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mouse_position) {
		return object_character.in(mouse_position);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::get_characters() {
		return std::vector<BaseCharacter*> {&object_character};
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::update_interactions(sf::Vector2f mouse_position) {
		return object_character.update_interactions(mouse_position);
	}
	
	BaseTextBlock* ObjectTextBlock::copy() {
		return new ObjectTextBlock{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<ObjectTextBlock>::decode_pointer(const YAML::Node&, ObjectTextBlock*&) {
		throw std::runtime_error("DecodePointer<ObjectTextBlock>::decode_pointer() not correct");
		return false;
	}
	*/
}
