#include "layerWithAlternativeObject.h"
#include <algorithm>

ui::LayerWithAlternativeObject::LayerWithAlternativeObject(ui::IScalable *topObject, ui::IScalable *bottomObject, sf::Vector2f minimumSize) :
	ILayer(minimumSize), topObject(topObject), bottomObject(bottomObject) {}

void ui::LayerWithAlternativeObject::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	initObject(topObject, renderTarget, interactionStack, interactionManager, panelManager);
	initObject(bottomObject, renderTarget, interactionStack, interactionManager, panelManager);
}

ui::LayerWithAlternativeObject::~LayerWithAlternativeObject() {
	delete topObject;
	delete bottomObject;
}

void ui::LayerWithAlternativeObject::draw() {
	bottomObject->draw();
	topObject->draw();
}

void ui::LayerWithAlternativeObject::update() {
	topObject->update();
	bottomObject->update();
}

bool ui::LayerWithAlternativeObject::updateInteractions(sf::Vector2f mousePosition) {
	return topObject->updateInteractions(mousePosition) || bottomObject->updateInteractions(mousePosition);
	
	/*  //same as on top
	if(!topObject->updateInteractions(mousePosition)) {
		return bottomObject->updateInteractions(mousePosition);
	}
	return true;
	*/
}

void ui::LayerWithAlternativeObject::resize(sf::Vector2f size, sf::Vector2f position) {
	this->size = size;
	this->position = position;
	topObject->resize(size, position);
	bottomObject->resize(size, position);
}

sf::Vector2f ui::LayerWithAlternativeObject::getMinSize() {
	sf::Vector2f topMinSize {topObject->getMinSize()};
	sf::Vector2f bottomMinSize {bottomObject->getMinSize()};
	return {std::max({topMinSize.x, bottomMinSize.x, minimumSize.x}), std::max({topMinSize.y, bottomMinSize.y, minimumSize.y})};
}

sf::Vector2f ui::LayerWithAlternativeObject::getNormalSize() {
	sf::Vector2f topNormalSize {topObject->getNormalSize()};
	sf::Vector2f bottomNormalSize {bottomObject->getNormalSize()};
	return {std::max(topNormalSize.x, bottomNormalSize.x), std::max(topNormalSize.y, bottomNormalSize.y)};
}

ui::LayerWithAlternativeObject *ui::LayerWithAlternativeObject::copy() {
	LayerWithAlternativeObject* layerWithAlternativeObject{new LayerWithAlternativeObject{topObject->copy(), bottomObject->copy(), minimumSize}};
	ILayer::copy(layerWithAlternativeObject);
	return layerWithAlternativeObject;
}

void ui::LayerWithAlternativeObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
    IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    topObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
    bottomObject->drawDebug(renderTarget, indent + indentAddition * 2, indentAddition, hue + hueOffset, hueOffset);
}
