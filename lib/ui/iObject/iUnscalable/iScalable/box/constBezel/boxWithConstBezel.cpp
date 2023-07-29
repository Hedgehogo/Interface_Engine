#include "boxWithConstBezel.hpp"
#include "../../../../../drawable/manager/drawManager.hpp"

namespace ui {
	BoxWithConstBezel::BoxWithConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize) :
		Box(minSize), object(object), bezel(bezel), thickness(thickness) {
		sf::Vector2f minimumSize{object->getMinSize() + sf::Vector2f(thickness * 2.0f, thickness * 2.0f)};
		if(this->minimumSize.x < minimumSize.x) {
			this->minimumSize.x = minimumSize.x;
		}
		if(this->minimumSize.y < minimumSize.y) {
			this->minimumSize.y = minimumSize.y;
		}
	}
	
	void BoxWithConstBezel::init(InitInfo initInfo) {
		bezel->init(initInfo);
		object->init(initInfo);
	}
	
	void BoxWithConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
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
	
	bool DecodePointer<BoxWithConstBezel>::decodePointer(const YAML::Node& node, BoxWithConstBezel*& boxWithConstBezel) {
		boxWithConstBezel = new BoxWithConstBezel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["bezel"].as<BoxPtr<IUninteractive> >(),
			node["thickness"].as<float>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
	
	void BoxWithConstBezel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		bezel->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
}

