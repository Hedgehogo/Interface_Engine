#include "boxSwitcher.hpp"

namespace ui {
	BoxSwitcher::Make::Make(BoxPtr<IScalable::Make>&& inactiveObject, BoxPtr<IScalable::Make>&& activeObject, PSbool value, const sf::Vector2f& minSize) :
		inactiveObject(std::move(inactiveObject)), activeObject(std::move(activeObject)), value(value), minSize(minSize) {
	}
	
	BoxSwitcher* BoxSwitcher::Make::make(InitInfo initInfo) {
		return new BoxSwitcher{std::move(*this), initInfo};
	}
	
	BoxSwitcher::BoxSwitcher(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		inactiveObject(make.inactiveObject->make(initInfo.copy(inactiveDrawManager))),
		activeObject(make.activeObject->make(initInfo.copy(activeDrawManager))),
		value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxSwitcher::BoxSwitcher(BoxPtr<IScalable>&& inactiveObject, BoxPtr<IScalable>&& activeObject, PSbool value, const sf::Vector2f& minSize) :
		Box(minSize), inactiveObject(std::move(inactiveObject)), activeObject(std::move(activeObject)), value(value) {
	}
	
	BoxSwitcher::BoxSwitcher(const BoxSwitcher& other) :
		Box(other), inactiveObject(other.inactiveObject), activeObject(other.activeObject), value(other.value) {
	}
	
	void BoxSwitcher::init(InitInfo initInfo) {
		inactiveObject->init(initInfo.copy(inactiveDrawManager));
		activeObject->init(initInfo.copy(activeDrawManager));
		initInfo.drawManager.add(*this);
	}
	
	void BoxSwitcher::setPosition(sf::Vector2f position) {
		layout.setPosition(position);
		inactiveObject->setPosition(position);
		activeObject->setPosition(position);
	}
	
	void BoxSwitcher::move(sf::Vector2f position) {
		layout.move(position);
		inactiveObject->move(position);
		activeObject->move(position);
	}
	
	void BoxSwitcher::setSize(sf::Vector2f size) {
		layout.setSize(size);
		inactiveObject->setSize(size);
		activeObject->setSize(size);
	}
	
	void BoxSwitcher::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		inactiveObject->resize(size, position);
		activeObject->resize(size, position);
	}
	
	void BoxSwitcher::draw() {
		if(value->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	bool BoxSwitcher::updateInteractions(sf::Vector2f mousePosition) {
		return value->getValue() ? activeObject->updateInteractions(mousePosition) : inactiveObject->updateInteractions(mousePosition);
	}
	
	IScalable& BoxSwitcher::getFirstObject() {
		return *inactiveObject;
	}
	
	const IScalable& BoxSwitcher::getFirstObject() const {
		return *inactiveObject;
	}
	
	IScalable& BoxSwitcher::getSecondObject() {
		return *activeObject;
	}
	
	const IScalable& BoxSwitcher::getSecondObject() const {
		return *activeObject;
	}
	
	BoxSwitcher* BoxSwitcher::copy() {
		return new BoxSwitcher{*this};
	}
	
	bool DecodePointer<BoxSwitcher>::decodePointer(const YAML::Node& node, BoxSwitcher*& boxSwitcher) {
		boxSwitcher = new BoxSwitcher{
			node["inactive-object"].as<BoxPtr<IScalable>>(),
			node["active-object"].as<BoxPtr<IScalable> >(),
			Buffer::get<Sbool>(node["value"]),
			convDef(node["min-size"],sf::Vector2f{})
		};
		return true;
	}
}