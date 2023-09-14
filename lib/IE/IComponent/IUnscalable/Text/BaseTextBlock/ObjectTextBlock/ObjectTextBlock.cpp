#include "ObjectTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"

namespace ie {
	ObjectTextBlock::ObjectTextBlock(BoxPtr<IScalable>&& object, sf::Vector2f size, bool isCharacter) :
		BaseTextBlock(), size(size), objectCharacter(new ObjectCharacter(std::move(object))), isCharacter(isCharacter), fullLine(false), object(*object) {
	}
	
	ObjectTextBlock::ObjectTextBlock(BoxPtr<IScalable>&& object, float height) :
		size(0, height), objectCharacter(new ObjectCharacter{std::move(object), true}), isCharacter(false), fullLine(true), object(*object) {
	}
	
	void ObjectTextBlock::init(InitInfo, InitInfo initInfo) {
		object.init(initInfo);
		sf::Vector2f minSize{object.getMinSize()};
		object.setSize({std::max(size.x, minSize.x), std::max(size.y, minSize.y)});
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mousePosition) {
		return objectCharacter->in(mousePosition);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::getCharacters() {
		std::vector<BaseCharacter*> result;
		if(!isCharacter && !fullLine) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		result.push_back(objectCharacter.get());
		
		if(!isCharacter && !fullLine) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		return result;
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::updateInteractions(sf::Vector2f mousePosition) {
		return object.updateInteractions(mousePosition);
	}
	
	BaseTextBlock* ObjectTextBlock::copy() {
		return new ObjectTextBlock{*this};
	}
	
	bool DecodePointer<ObjectTextBlock>::decodePointer(const YAML::Node& node, ObjectTextBlock*& objectTextBlock) {
		if(node["size"]) {
			objectTextBlock = new ObjectTextBlock{
				node["object"].as<BoxPtr<IScalable>>(),
				node["size"].as<sf::Vector2f>(),
				convDef(node["is-character"], true)
			};
		} else {
			objectTextBlock = new ObjectTextBlock{
				node["object"].as<BoxPtr<IScalable>>(),
				node["height"].as<float>()
			};
		}
		return true;
	}
}
