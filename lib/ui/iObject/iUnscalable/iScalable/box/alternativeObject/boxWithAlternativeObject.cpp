#include "boxWithAlternativeObject.hpp"
#include <algorithm>

namespace ui {
	BoxWithAlternativeObject::Make::Make(BoxPtr<IScalable::Make>&& topObject, BoxPtr<IScalable::Make>&& bottomObject, sf::Vector2f minSize) :
		topObject(std::move(topObject)), bottomObject(std::move(bottomObject)), minSize(minSize) {
	}
	
	BoxWithAlternativeObject* BoxWithAlternativeObject::Make::make(InitInfo initInfo) {
		return new BoxWithAlternativeObject{std::move(*this), initInfo};
	}
	
	BoxWithAlternativeObject::BoxWithAlternativeObject(Make&& make, InitInfo initInfo) :
		Box(make.minSize), topObject(make.topObject->make(initInfo)), bottomObject(make.bottomObject->make(initInfo)) {
	}
	
	BoxWithAlternativeObject::BoxWithAlternativeObject(BoxPtr<IScalable>&& topObject, BoxPtr<IScalable>&& bottomObject, sf::Vector2f minSize) :
		Box(minSize), topObject(std::move(topObject)), bottomObject(std::move(bottomObject)) {
	}
	
	void BoxWithAlternativeObject::init(InitInfo initInfo) {
		topObject->init(initInfo);
		bottomObject->init(initInfo);
	}
	
	bool BoxWithAlternativeObject::updateInteractions(sf::Vector2f mousePosition) {
		return topObject->updateInteractions(mousePosition) || bottomObject->updateInteractions(mousePosition);
	}
	
	void BoxWithAlternativeObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		topObject->resize(size, position);
		bottomObject->resize(size, position);
	}
	
	IScalable& BoxWithAlternativeObject::getFirstObject() {
		return *topObject;
	}
	
	const IScalable& BoxWithAlternativeObject::getFirstObject() const {
		return *topObject;
	}
	
	IScalable& BoxWithAlternativeObject::getSecondObject() {
		return *bottomObject;
	}
	
	const IScalable& BoxWithAlternativeObject::getSecondObject() const {
		return *bottomObject;
	}
	
	BoxWithAlternativeObject* BoxWithAlternativeObject::copy() {
		return new BoxWithAlternativeObject{*this};
	}
	
	bool DecodePointer<BoxWithAlternativeObject>::decodePointer(const YAML::Node& node, BoxWithAlternativeObject*& boxWithAlternativeObject) {
		boxWithAlternativeObject = new BoxWithAlternativeObject{
			node["top-object"].as<BoxPtr<IScalable> >(),
			node["bottom-object"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}
