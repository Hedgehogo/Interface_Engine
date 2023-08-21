#include "BoxConstBezel.hpp"

namespace ui {
	BoxConstBezel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f minSize) :
		object(std::move(object)), bezel(std::move(bezel)), thickness(thickness), minSize(minSize) {
	}
	
	BoxConstBezel* BoxConstBezel::Make::make(InitInfo initInfo) {
		return new BoxConstBezel{std::move(*this), initInfo};
	}
	
	BoxConstBezel::BoxConstBezel(Make&& make, InitInfo initInfo) :
		Box(make.minSize), bezel(make.bezel->make(initInfo)), object(make.object->make(initInfo)), thickness(make.thickness) {
	}
	
	BoxConstBezel::BoxConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize) :
		Box(minSize), bezel(std::move(bezel)), object(std::move(object)), thickness(thickness) {
	}
	
	void BoxConstBezel::init(InitInfo initInfo) {
		bezel->init(initInfo);
		object->init(initInfo);
	}
	
	void BoxConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool BoxConstBezel::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return bezel->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxConstBezel::getMinSize() const {
		return max(object->getMinSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxConstBezel::getNormalSize() const {
		return max(object->getNormalSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getNormalSize());
	}
	
	IScalable& BoxConstBezel::getObject() {
		return *object;
	}
	
	const IScalable& BoxConstBezel::getObject() const {
		return *object;
	}
	
	BoxConstBezel* BoxConstBezel::copy() {
		return new BoxConstBezel{*this};
	}
	
	void BoxConstBezel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		bezel->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxConstBezel>::decodePointer(const YAML::Node& node, BoxConstBezel*& boxWithConstBezel) {
		boxWithConstBezel = new BoxConstBezel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["bezel"].as<BoxPtr<IUninteractive> >(),
			node["thickness"].as<float>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}

