#include "layerWithConstBezel.hpp"
#include "../../../../../drawable/manager/drawManager.h"

namespace ui {
	LayerWithConstBezel::LayerWithConstBezel(IScalable *object, OnlyDrawable *bezel, float thickness, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), bezel(bezel), thickness(thickness) {
		sf::Vector2f minimumSize{object->getMinSize() + sf::Vector2f(thickness * 2.0f, thickness * 2.0f)};
		if(this->minimumSize.x < minimumSize.x) {
			this->minimumSize.x = minimumSize.x;
		}
		if(this->minimumSize.y < minimumSize.y) {
			this->minimumSize.y = minimumSize.y;
		}
	}
	
	void LayerWithConstBezel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		bezel->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		object->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithConstBezel::~LayerWithConstBezel() {
		delete bezel;
	}
	
	void LayerWithConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool LayerWithConstBezel::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return false;
	}
	
	sf::Vector2f LayerWithConstBezel::getMinSize() {
		return max(object->getMinSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f LayerWithConstBezel::getNormalSize() {
		return max(object->getNormalSize() + sf::Vector2f{thickness * 2, thickness * 2}, bezel->getNormalSize());
	}
	
	LayerWithConstBezel *LayerWithConstBezel::copy() {
		LayerWithConstBezel* layerWithConstBezel{new LayerWithConstBezel{object->copy(), bezel->copy(), thickness}};
		Layer::copy(layerWithConstBezel);
		return layerWithConstBezel;
	}
	
	LayerWithConstBezel *LayerWithConstBezel::createFromYaml(const YAML::Node &node) {
		IScalable *object;
		OnlyDrawable *bezel;
		float thickness;
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		node["bezel"] >> bezel;
		node["thickness"] >> thickness;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		return new LayerWithConstBezel{object, bezel, thickness, minSize};
	}
	
	void LayerWithConstBezel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        bezel->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        object->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
}
