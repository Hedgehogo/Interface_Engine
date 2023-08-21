#include "BoxUninteractive.hpp"

namespace ui {
	BoxUninteractive* BoxUninteractive::Make::make(InitInfo initInfo) {
		return new BoxUninteractive{std::move(*this), initInfo};
	}
	
	BoxUninteractive::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		object(std::move(object)), minSize(minSize) {
	}
	
	BoxUninteractive::BoxUninteractive(Make&& make, InitInfo initInfo) :
		Box(make.minSize), object(make.object->make(initInfo)) {
	}
	
	BoxUninteractive::BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f minSize) : Box(minSize), object(std::move(object)) {
	}
	
	void BoxUninteractive::init(InitInfo initInfo) {
		object->init(initInfo);
	}
	
	void BoxUninteractive::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutObject::resize(size, position);
	}
	
	bool BoxUninteractive::updateInteractions(sf::Vector2f mousePosition) {
		return IUninteractive::updateInteractions(mousePosition);
	}
	
	IScalable& BoxUninteractive::getObject() {
		return *object;
	}
	
	const IScalable& BoxUninteractive::getObject() const {
		return *object;
	}
	
	bool DecodePointer<BoxUninteractive>::decodePointer(const YAML::Node& node, BoxUninteractive*& boxUninteractive) {
		boxUninteractive = new BoxUninteractive{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
	
	BoxUninteractive* BoxUninteractive::copy() {
		return new BoxUninteractive{*this};
	}
}