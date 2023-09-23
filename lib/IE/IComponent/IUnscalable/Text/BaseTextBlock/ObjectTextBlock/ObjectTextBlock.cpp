#include "ObjectTextBlock.hpp"
#include "../../BaseCharacter/Character/Character.hpp"

namespace ie {
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, const sf::Vector2f& size, bool isCharacter) : object(std::move(object)), size(size), isCharacter(isCharacter), fullLine(false) {
	}
	
	ObjectTextBlock::Make::Make(BoxPtr<IScalable::Make>&& object, float height) : object(std::move(object)), height(height), fullLine(true) {
	}
	
	ObjectTextBlock* ObjectTextBlock::Make::make(TextBockInitInfo textBlockInitInfo) {
		return new ObjectTextBlock{std::move(*this), textBlockInitInfo};
	}
	
	ObjectTextBlock::ObjectTextBlock(
		ObjectTextBlock::Make&& make,
		TextBockInitInfo textBlockInitInfo
	) :
		isCharacter(make.isCharacter && !make.fullLine),
		objectCharacter(
			new ObjectCharacter{
				BoxPtr{
					[&](){
						auto result{make.object->make(static_cast<InitInfo>(textBlockInitInfo))};
						sf::Vector2f size{make.size.x, make.fullLine ? make.height : make.size.y};
						sf::Vector2f minSize{result->getSize()};
						result->setSize({std::max(size.x, minSize.x), std::max(size.y, minSize.y)});
						return result;
					}()
				},
				make.fullLine
			}
		){
	}
	
	void ObjectTextBlock::init(TextBockInitInfo textBlockInitInfo) {
		throw std::runtime_error("ObjectTextBlock::init() not correct");
	}
	
	bool ObjectTextBlock::in(sf::Vector2f mousePosition) {
		return objectCharacter->in(mousePosition);
	}
	
	std::vector<BaseCharacter*> ObjectTextBlock::getCharacters() {
		std::vector<BaseCharacter*> result;
		if(!isCharacter) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		result.push_back(objectCharacter.get());
		
		if(!isCharacter) {
			result.push_back(new Character{L'\n', textVariables, lines});
		}
		
		return result;
	}
	
	void ObjectTextBlock::update() {
	}
	
	bool ObjectTextBlock::updateInteractions(sf::Vector2f mousePosition) {
		return objectCharacter->updateInteractions(mousePosition);
	}
	
	BaseTextBlock* ObjectTextBlock::copy() {
		return new ObjectTextBlock{*this};
	}
	
	bool DecodePointer<ObjectTextBlock>::decodePointer(const YAML::Node& node, ObjectTextBlock*& objectTextBlock) {
		throw std::runtime_error("DecodePointer<ObjectTextBlock>::decodePointer() not correct");
		return false;
	}
}
