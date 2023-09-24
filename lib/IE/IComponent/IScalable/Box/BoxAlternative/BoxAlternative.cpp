#include "BoxAlternative.hpp"
#include <algorithm>

namespace ie {
	BoxAlternative::Make::Make(BoxPtr<IScalable::Make>&& topObject, BoxPtr<IScalable::Make>&& bottomObject, sf::Vector2f minSize) :
		topObject(std::move(topObject)), bottomObject(std::move(bottomObject)), minSize(minSize) {
	}
	
	BoxAlternative* BoxAlternative::Make::make(InitInfo initInfo) {
		return new BoxAlternative{std::move(*this), initInfo};
	}
	
	BoxAlternative::BoxAlternative(Make&& make, InitInfo initInfo) :
		Box(make.minSize), bottomObject(make.bottomObject->make(initInfo)), topObject(make.topObject->make(initInfo)) {
	}
	
	BoxAlternative::BoxAlternative(BoxPtr<IScalable>&& topObject, BoxPtr<IScalable>&& bottomObject, sf::Vector2f minSize) :
		Box(minSize), bottomObject(std::move(bottomObject)), topObject(std::move(topObject)) {
	}
	
	void BoxAlternative::init(InitInfo initInfo) {
		topObject->init(initInfo);
		bottomObject->init(initInfo);
	}
	
	bool BoxAlternative::updateInteractions(sf::Vector2f mousePosition) {
		return topObject->updateInteractions(mousePosition) || bottomObject->updateInteractions(mousePosition);
	}
	
	void BoxAlternative::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		topObject->resize(size, position);
		bottomObject->resize(size, position);
	}
	
	IScalable& BoxAlternative::getFirstObject() {
		return *topObject;
	}
	
	const IScalable& BoxAlternative::getFirstObject() const {
		return *topObject;
	}
	
	IScalable& BoxAlternative::getSecondObject() {
		return *bottomObject;
	}
	
	const IScalable& BoxAlternative::getSecondObject() const {
		return *bottomObject;
	}
	
	BoxAlternative* BoxAlternative::copy() {
		return new BoxAlternative{*this};
	}
	
	bool DecodePointer<BoxAlternative>::decodePointer(const YAML::Node& node, BoxAlternative*& boxWithAlternativeObject) {
		boxWithAlternativeObject = new BoxAlternative{
			node["top-object"].as<BoxPtr<IScalable> >(),
			node["bottom-object"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}
