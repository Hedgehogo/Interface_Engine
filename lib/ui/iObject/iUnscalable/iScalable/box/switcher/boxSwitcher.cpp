#include "boxSwitcher.hpp"

namespace ui {
	BoxSwitcher* BoxSwitcher::Make::make(InitInfo initInfo) {
		return new BoxSwitcher{std::move(*this), initInfo};
	}
	
	BoxSwitcher::BoxSwitcher(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		firstObject(make.firstObject->make(initInfo)),
		secondObject(make.secondObject->make(initInfo)),
		value(make.value) {
	}
	
	BoxSwitcher::BoxSwitcher(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, PSbool value, const sf::Vector2f& minSize) :
		Box(minSize), firstObject(std::move(firstObject)), secondObject(std::move(secondObject)), value(value) {
	}
	
	BoxSwitcher::BoxSwitcher(const BoxSwitcher& other) :
		Box(other), firstObject(other.firstObject), secondObject(other.secondObject), value(other.value) {
	}
	
	void BoxSwitcher::init(InitInfo initInfo) {
		firstObject->init(initInfo.copy(firstDrawManager));
		secondObject->init(initInfo.copy(secondDrawManager));
		initInfo.drawManager.add(*this);
	}
	
	void BoxSwitcher::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
		firstObject->setPosition(position);
		secondObject->setPosition(position);
	}
	
	void BoxSwitcher::move(sf::Vector2f position) {
		ILayout::move(position);
		firstObject->move(position);
		secondObject->move(position);
	}
	
	void BoxSwitcher::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
		firstObject->setSize(size);
		secondObject->setSize(size);
	}
	
	void BoxSwitcher::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayout::resize(size, position);
		firstObject->resize(size, position);
		secondObject->resize(size, position);
	}
	
	void BoxSwitcher::draw() {
		if(value->getValue()) {
			firstDrawManager.draw();
		} else {
			secondDrawManager.draw();
		}
	}
	
	bool BoxSwitcher::updateInteractions(sf::Vector2f mousePosition) {
		return value->getValue() ? firstObject->updateInteractions(mousePosition) : secondObject->updateInteractions(mousePosition);
	}
	
	IScalable& BoxSwitcher::getFirstObject() {
		return *firstObject;
	}
	
	const IScalable& BoxSwitcher::getFirstObject() const {
		return *firstObject;
	}
	
	IScalable& BoxSwitcher::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxSwitcher::getSecondObject() const {
		return *secondObject;
	}
	
	BoxSwitcher* BoxSwitcher::copy() {
		return new BoxSwitcher{*this};
	}
	
	bool DecodePointer<BoxSwitcher>::decodePointer(const YAML::Node& node, BoxSwitcher*& boxSwitcher) {
		boxSwitcher = new BoxSwitcher{
			node["first-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable>>(),
			Buffer::get<Sbool>(node["value"]),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}