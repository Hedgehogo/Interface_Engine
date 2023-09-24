#include "BoxSwitch.hpp"

namespace ie {
	BoxSwitch::Make::Make(BoxPtr<IScalable::Make>&& inactiveObject, BoxPtr<IScalable::Make>&& activeObject, PSbool value, const sf::Vector2f& minSize) :
		inactiveObject(std::move(inactiveObject)), activeObject(std::move(activeObject)), value(value), minSize(minSize) {
	}
	
	BoxSwitch* BoxSwitch::Make::make(InitInfo initInfo) {
		return new BoxSwitch{std::move(*this), initInfo};
	}
	
	BoxSwitch::BoxSwitch(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		inactiveObject(make.inactiveObject->make(initInfo.copy(inactiveDrawManager))),
		activeObject(make.activeObject->make(initInfo.copy(activeDrawManager))),
		value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxSwitch::BoxSwitch(BoxPtr<IScalable>&& inactiveObject, BoxPtr<IScalable>&& activeObject, PSbool value, const sf::Vector2f& minSize) :
		Box(minSize), inactiveObject(std::move(inactiveObject)), activeObject(std::move(activeObject)), value(value) {
	}
	
	BoxSwitch::BoxSwitch(const BoxSwitch& other) :
		Box(other), inactiveObject(other.inactiveObject), activeObject(other.activeObject), value(other.value) {
	}
	
	void BoxSwitch::init(InitInfo initInfo) {
		inactiveObject->init(initInfo.copy(inactiveDrawManager));
		activeObject->init(initInfo.copy(activeDrawManager));
		initInfo.drawManager.add(*this);
	}
	
	void BoxSwitch::setPosition(sf::Vector2f position) {
		layout.setPosition(position);
		inactiveObject->setPosition(position);
		activeObject->setPosition(position);
	}
	
	void BoxSwitch::move(sf::Vector2f position) {
		layout.move(position);
		inactiveObject->move(position);
		activeObject->move(position);
	}
	
	void BoxSwitch::setSize(sf::Vector2f size) {
		layout.setSize(size);
		inactiveObject->setSize(size);
		activeObject->setSize(size);
	}
	
	void BoxSwitch::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		inactiveObject->resize(size, position);
		activeObject->resize(size, position);
	}
	
	void BoxSwitch::draw() {
		if(value->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	bool BoxSwitch::updateInteractions(sf::Vector2f mousePosition) {
		return value->getValue() ? activeObject->updateInteractions(mousePosition) : inactiveObject->updateInteractions(mousePosition);
	}
	
	IScalable& BoxSwitch::getFirstObject() {
		return *inactiveObject;
	}
	
	const IScalable& BoxSwitch::getFirstObject() const {
		return *inactiveObject;
	}
	
	IScalable& BoxSwitch::getSecondObject() {
		return *activeObject;
	}
	
	const IScalable& BoxSwitch::getSecondObject() const {
		return *activeObject;
	}
	
	BoxSwitch* BoxSwitch::copy() {
		return new BoxSwitch{*this};
	}
	
	bool DecodePointer<BoxSwitch>::decodePointer(const YAML::Node& node, BoxSwitch*& boxSwitcher) {
		boxSwitcher = new BoxSwitch{
			node["inactive-object"].as<BoxPtr<IScalable>>(),
			node["active-object"].as<BoxPtr<IScalable> >(),
			Buffer::get<Sbool>(node["value"]),
			convDef(node["min-size"],sf::Vector2f{})
		};
		return true;
	}
}