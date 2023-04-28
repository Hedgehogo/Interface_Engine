#include "boxScroll.hpp"

namespace ui {
	BoxScroll::BoxScroll(IUnscalable* object, const PSRVec2f& normalObjectPosition, const sf::Vector2f& minSize) :
		IBoxWithView(minSize), object(object), normalObjectPosition(normalObjectPosition) {
		normalObjectPosition->addSetter([&](sf::Vector2f vec) {
			this->object->setPosition(getNewObjectPosition(vec));
		});
		setRangeBounds(normalObjectPosition, {0, 0}, {1, 1});
	}
	
	void BoxScroll::init(InitInfo initInfo) {
		IBoxWithView::init(initInfo);
		object->init(initInfo.copy(this->drawManager));
	}
	
	sf::Vector2f BoxScroll::getMinSize() {
		return max(minimumSize, object->getMinSize());
	}
	
	sf::Vector2f BoxScroll::getNormalSize() {
		return object->getNormalSize();
	}
	
	sf::Vector2f BoxScroll::getNewObjectPosition(sf::Vector2f normalObjectPosition) {
		sf::Vector2f maxOffset{object->getSize() - size};
		sf::Vector2f offset{maxOffset * normalObjectPosition};
		return position - offset;
	}
	
	void BoxScroll::resize(sf::Vector2f size, sf::Vector2f position) {
		IBoxWithView::resize(size, position);
		
		object->setSize(size);
		
		sf::Vector2f objectSize{object->getSize()};
		if(objectSize.x == size.x && objectSize.y == size.y)
			return object->setPosition(position);
		object->setPosition(getNewObjectPosition(normalObjectPosition->getValue()));
	}
	
	bool BoxScroll::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	BoxScroll* BoxScroll::copy() {
		return new BoxScroll{object->copy(), normalObjectPosition, minimumSize};
	}
	
	BoxScroll::~BoxScroll() {
		delete object;
	}
	
	
	bool DecodePointer<BoxScroll>::decodePointer(const YAML::Node& node, BoxScroll*& boxScroll) {
		boxScroll = new BoxScroll{
			node["object"].as<IUnscalable*>(),
			Buffer::get<SRVec2f>(node["normal-object-position"]),
			(node["min-size"] ? node["min-size"].as<sf::Vector2f>() : sf::Vector2f{0, 0})
		};
		return true;
	}
}