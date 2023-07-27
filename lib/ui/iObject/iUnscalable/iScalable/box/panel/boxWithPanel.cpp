#include "boxWithPanel.hpp"

namespace ui {
	BoxWithPanel::BoxWithPanel(ConstPanel* panel, IScalable* object, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), panel(panel) {
	}
	
	void BoxWithPanel::init(InitInfo initInfo) {
		object->init(initInfo);
		panel->init(initInfo);
	}
	
	BoxWithPanel::~BoxWithPanel() {
		delete panel;
	}
	
	void BoxWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithObject::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f BoxWithPanel::getMinSize() const {
		return max(object->getMinSize(), panel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithPanel::getNormalSize() const {
		return max(object->getNormalSize(), panel->getNormalSize());
	}
	
	BoxWithPanel* BoxWithPanel::copy() {
		BoxWithPanel* boxWithPanel{new BoxWithPanel{panel->copy(), object->copy(), minimumSize}};
		Box::copy(boxWithPanel);
		return boxWithPanel;
	}
	
	void BoxWithPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<BoxWithPanel>::decodePointer(const YAML::Node& node, BoxWithPanel*& boxWithPanel) {
		ConstPanel* panel;
		IScalable* object;
		sf::Vector2f minSize{};
		
		node["panel"] >> panel;
		node["object"] >> object;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithPanel = new BoxWithPanel{panel, object, minSize};
		return true;
	}
}