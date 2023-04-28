#include "objectTextBlock.hpp"
#include "../../character/simple/character.hpp"

namespace ui {
	ObjectTextBlock::ObjectTextBlock(IScalable* object, sf::Vector2f size, bool isCharacter) : BaseTextBlock(), size(size), objectCharacter(new ObjectCharacter(object)), object(object), isCharacter(isCharacter), fullLine(false) {
	}
	
	ObjectTextBlock::ObjectTextBlock(IScalable* object, float height) : size(0, height), fullLine(true), isCharacter(false), object(object), objectCharacter(new ObjectCharacter{object, true}) {
	}
	
	void ObjectTextBlock::init(InitInfo textInitInfo, InitInfo initInfo) {
		object->init(initInfo);
		sf::Vector2f minSize{object->getMinSize()};
		object->setSize({std::max(size.x, minSize.x), std::max(size.y, minSize.y)});
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mousePosition) {
		return objectCharacter->in(mousePosition);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::getCharacters() {
		std::vector<BaseCharacter*> result;
		if(!isCharacter && !fullLine) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		result.push_back(objectCharacter);
		
		if(!isCharacter && !fullLine) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		return result;
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	BaseTextBlock* ObjectTextBlock::copy() {
		return new ObjectTextBlock{object->copy(), object->getAreaSize(), isCharacter};
	}
	
	bool convertPointer(const YAML::Node &node, ObjectTextBlock *&objectTextBlock) {
		IScalable* object;
		
		node["object"] >> object;
		
		if(node["size"]) {
			sf::Vector2f size{0, 0};
			bool isCharacter{true};
			
			node["size"] >> size;
			if(node["is-character"])
				node["is-character"] >> isCharacter;
			{
				objectTextBlock = new ObjectTextBlock{object, size, isCharacter};
				return true;
			}
		} else {
			float height{0};
			
			node["height"] >> height;
			{
				objectTextBlock = new ObjectTextBlock{object, height};
				return true;
			}
		}
	}
	
	bool DecodePointer<ObjectTextBlock>::decodePointer(const YAML::Node &node, ObjectTextBlock *&objectTextBlock) {
		IScalable* object;
		
		node["object"] >> object;
		
		if(node["size"]) {
			sf::Vector2f size{0, 0};
			bool isCharacter{true};
			
			node["size"] >> size;
			if(node["is-character"])
				node["is-character"] >> isCharacter;
			{
				objectTextBlock = new ObjectTextBlock{object, size, isCharacter};
				return true;
			}
		} else {
			float height{0};
			
			node["height"] >> height;
			{
				objectTextBlock = new ObjectTextBlock{object, height};
				return true;
			}
		}
	}
}
