#include "boxWithConstBezel.hpp"

namespace ui {
	BoxWithConstBezel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f minSize) :
		object(std::move(object)), bezel(std::move(bezel)), thickness(thickness), minSize(minSize) {
	}
	
	BoxWithConstBezel* BoxWithConstBezel::Make::make(InitInfo initInfo) {
		return new BoxWithConstBezel{std::move(*this), initInfo};
	}
	
	BoxWithConstBezel::BoxWithConstBezel(Make&& make, InitInfo initInfo) :
		Box(make.minSize), object(make.object->make(initInfo)), bezel(make.bezel->make(initInfo)), thickness(make.thickness) {
	}
	
	BoxWithConstBezel::BoxWithConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)), bezel(std::move(bezel)), thickness(thickness) {
	}
	
	void BoxWithConstBezel::init(InitInfo initInfo) {
		bezel->init(initInfo);
		object->init(initInfo);
	}
	
	void BoxWithConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool BoxWithConstBezel::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return false;
	}
	
	sf::Vector2f BoxWithConstBezel::getMinSize() const {
		return max(object->getMinSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithConstBezel::getNormalSize() const {
		return max(object->getNormalSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getNormalSize());
	}
	
	IScalable& BoxWithConstBezel::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithConstBezel::getObject() const {
		return *object;
	}
	
	BoxWithConstBezel* BoxWithConstBezel::copy() {
		return new BoxWithConstBezel{*this};
	}
	
	void BoxWithConstBezel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		bezel->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxWithConstBezel>::decodePointer(const YAML::Node& node, BoxWithConstBezel*& boxWithConstBezel) {
		boxWithConstBezel = new BoxWithConstBezel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["bezel"].as<BoxPtr<IUninteractive> >(),
			node["thickness"].as<float>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}

