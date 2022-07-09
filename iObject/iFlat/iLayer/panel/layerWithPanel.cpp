#include "layerWithPanel.h"

namespace ui {
	LayerWithPanel::LayerWithPanel(IFlat *object, ConstPanel *panel, sf::Vector2f minSize) :
		ILayer(minSize), object(object), panel(panel) {}
	
	void LayerWithPanel::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		initObject(object, renderTarget, interactionStack, interactionManager, panelManager);
		initObject(panel, renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayerWithPanel::~LayerWithPanel() {
		delete object;
		delete panel;
	}
	
	void LayerWithPanel::draw() {
		object->draw();
	}
	
	void LayerWithPanel::update() {
		object->update();
	}
	
	bool LayerWithPanel::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	void LayerWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		object->resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f LayerWithPanel::getMinSize() {
		sf::Vector2f objectMinSize {object->getMinSize()};
		sf::Vector2f panelMinSize {panel->getMinSize()};
		return {std::max(objectMinSize.x, panelMinSize.x), std::max(objectMinSize.y, panelMinSize.y)};
	}
	
	sf::Vector2f LayerWithPanel::getNormalSize() {
		sf::Vector2f objectNormalSize {object->getNormalSize()};
		sf::Vector2f panelNormalSize {panel->getNormalSize()};
		return {std::max(objectNormalSize.x, panelNormalSize.x), std::max(objectNormalSize.y, panelNormalSize.y)};
	}
	
	LayerWithPanel *LayerWithPanel::copy() {
		return new LayerWithPanel{object->copy(), panel->copy(), minimumSize};
	}
	
	void LayerWithPanel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition) {
		object->drawDebug(renderTarget, indent, indentAddition);
		panel->drawDebug(renderTarget, 0, indentAddition);
	}
}