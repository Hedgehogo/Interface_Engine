#include "ObjectTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"

namespace ie {
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, const sf::Vector2f& size, bool is_character) : object(std::move(object)), size(size), is_character(is_character), full_line(false) {
	}
	
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, float height) : object(std::move(object)), height(height), full_line(true) {
	}
	
	ObjectTextBlock* ObjectTextBlock::Make::make(TextBockInitInfo text_block_init_info) {
		return new ObjectTextBlock{std::move(*this), text_block_init_info};
	}
	
	ObjectTextBlock::ObjectTextBlock(
		Make&& make,
		TextBockInitInfo text_block_init_info
	) :
		is_character(make.is_character && !make.full_line),
		object_character(
			new ObjectCharacter{
				BoxPtr{
					[&](){
						auto result{make.object->make(static_cast<InitInfo>(text_block_init_info))};
						sf::Vector2f size{make.size.x, make.full_line ? make.height : make.size.y};
						sf::Vector2f min_size{result->get_size()};
						result->set_size({std::max(size.x, min_size.x), std::max(size.y, min_size.y)});
						return result;
					}()
				},
				make.full_line
			}
		){
	}
	
	void ObjectTextBlock::init(TextBockInitInfo) {
		throw std::runtime_error("ObjectTextBlock::init() not correct");
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mouse_position) {
		return object_character->in(mouse_position);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::get_characters() {
		std::vector<BaseCharacter*> result;
		if(!is_character) {
			result.push_back(new Character{L'\n', text_variables, lines, {}});
		}
		
		result.push_back(object_character.get());
		
		if(!is_character) {
			result.push_back(new Character{L'\n', text_variables, lines, {}});
		}
		
		return result;
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::update_interactions(sf::Vector2f mouse_position) {
		return object_character->update_interactions(mouse_position);
	}
	
	BaseTextBlock* ObjectTextBlock::copy() {
		return new ObjectTextBlock{*this};
	}
	
	bool DecodePointer<ObjectTextBlock>::decode_pointer(const YAML::Node&, ObjectTextBlock*&) {
		throw std::runtime_error("DecodePointer<ObjectTextBlock>::decode_pointer() not correct");
		return false;
	}
}
