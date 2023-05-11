#include "boxWithConstCenter.hpp"

namespace ui {
	
	BoxWithConstCenter::BoxWithConstCenter(IScalable* constObject, IScalable* background, const sf::Vector2f& constSize, const sf::Vector2f& minSize) :
		Box(minSize), LayoutWithTwoObjects(constObject, background), constSize(constSize) {
		firstObject->setSize(constSize);
	}
	
	void BoxWithConstCenter::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		firstObject->setPosition(position + (size / 2.f) - (constSize / 2.f));
		secondObject->setPosition(position);
	}
	
	void BoxWithConstCenter::move(sf::Vector2f position) {
		Layout::move(position);
		
		firstObject->move(position);
		secondObject->move(position);
	}
	
	void BoxWithConstCenter::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		
		secondObject->setSize(size);
	}
	
	void BoxWithConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		firstObject->setPosition(position + (size / 2.f) - (constSize / 2.f));
		secondObject->resize(size, position);
	}
	
	sf::Vector2f BoxWithConstCenter::getMinSize() const {
		return max(LayoutWithTwoObjects::getMinSize(), constSize);
	}
	
	sf::Vector2f BoxWithConstCenter::getNormalSize() const {
		return max(LayoutWithTwoObjects::getNormalSize(), constSize);
	}
	
	bool BoxWithConstCenter::updateInteractions(sf::Vector2f mousePosition) {
		return secondObject->in(position) ? secondObject->updateInteractions(position) : firstObject->updateInteractions(position);
	}
	
	BoxWithConstCenter* BoxWithConstCenter::copy() {
		auto boxWithConstCenterCopy{new BoxWithConstCenter{firstObject->copy(), firstObject->copy(), constSize, minimumSize}};
		LayoutWithTwoObjects::copy(boxWithConstCenterCopy);
		return boxWithConstCenterCopy;
	}
	
	bool DecodePointer<BoxWithConstCenter>::decodePointer(const YAML::Node& node, BoxWithConstCenter*& boxWithConstCenter) {
		boxWithConstCenter = new BoxWithConstCenter{
			node["const-object"].as<IScalable*>(),
			node["background"].as<IScalable*>(),
			node["const-size"].as<sf::Vector2f>(),
			convDef<sf::Vector2f>(node["min-size"], {})
		};
		return true;
	}
}