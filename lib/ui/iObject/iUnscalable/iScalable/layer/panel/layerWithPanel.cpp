#include "layerWithPanel.hpp"

namespace ui {
	LayerWithPanel::LayerWithPanel(ConstPanel* panel, IScalable* object, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), panel(panel) {}
	
	void LayerWithPanel::init(InitInfo initInfo) {
		object->init(initInfo);
		panel->init(initInfo);
	}
	
	LayerWithPanel::~LayerWithPanel() {
		delete panel;
	}
	
	void LayerWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithObject::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f LayerWithPanel::getMinSize() {
		return max(object->getMinSize(), panel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f LayerWithPanel::getNormalSize() {
		return max(object->getNormalSize(), panel->getNormalSize());
	}
	
	LayerWithPanel *LayerWithPanel::copy() {
		LayerWithPanel* layerWithPanel{new LayerWithPanel{panel->copy(), object->copy(), minimumSize}};
		Layer::copy(layerWithPanel);
		return layerWithPanel;
	}
	
	void LayerWithPanel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithPanel *&layerWithPanel) {
		ConstPanel* panel;
		IScalable* object;
		sf::Vector2f minSize{};
		
		node["panel"] >> panel;
		node["object"] >> object;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		{ layerWithPanel = new LayerWithPanel{panel, object, minSize}; return true; }
	}
}