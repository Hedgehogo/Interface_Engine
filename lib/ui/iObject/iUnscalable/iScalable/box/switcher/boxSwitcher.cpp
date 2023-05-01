#include "boxSwitcher.hpp"

namespace ui {
	
	BoxSwitcher::BoxSwitcher(IScalable* firstObject, IScalable* secondObject, PSbool value, const sf::Vector2f& minSize) :
		Box(minSize, size), LayoutWithTwoObjects(firstObject, secondObject), value(value) {}
	
	void BoxSwitcher::init(InitInfo initInfo) {
		firstObject->init(initInfo.copy(firstDrawManager));
		secondObject->init(initInfo.copy(secondDrawManager));
		initInfo.drawManager.add(*this);
	}
	
	void BoxSwitcher::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		firstObject->setPosition(position);
		secondObject->setPosition(position);
	}
	
	void BoxSwitcher::move(sf::Vector2f position) {
		Layout::move(position);
		firstObject->move(position);
		secondObject->move(position);
	}
	
	void BoxSwitcher::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		firstObject->setSize(size);
		secondObject->setSize(size);
	}
	
	void BoxSwitcher::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		firstObject->resize(size, position);
		secondObject->resize(size, position);
	}
	
	void BoxSwitcher::draw() {
		if (value->getValue())
			firstDrawManager.draw();
		else
			secondDrawManager.draw();
	}
	
	bool BoxSwitcher::updateInteractions(sf::Vector2f mousePosition) {
		return value->getValue() ? firstObject->updateInteractions(mousePosition) : secondObject->updateInteractions(mousePosition);
	}
	
	BoxSwitcher* BoxSwitcher::copy() {
		auto boxSwitcherCopy{new BoxSwitcher{firstObject->copy(), secondObject->copy(), value, minimumSize}};
		Layout::copy(boxSwitcherCopy);
		return boxSwitcherCopy;
	}
	
	bool DecodePointer<BoxSwitcher>::decodePointer(const YAML::Node& node, BoxSwitcher*& boxSwitcher) {
		boxSwitcher = new BoxSwitcher{
			node["first-object"].as<IScalable*>(),
			node["second-object"].as<IScalable*>(),
			Buffer::get<Sbool>(node["value"]),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}