#include "BoxPanel.hpp"

namespace ie {
	BoxPanel::Make::Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		panel(std::move(panel)), object(std::move(object)), minSize(minSize) {
	}
	
	BoxPanel* BoxPanel::Make::make(InitInfo initInfo) {
		return new BoxPanel{std::move(*this), initInfo};
	}
	
	BoxPanel::BoxPanel(Make&& make, InitInfo initInfo) :
		Box(make.minSize), object(make.object->make(initInfo)), panel(make.panel->make(initInfo)) {
	}
	
	BoxPanel::BoxPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)), panel(std::move(panel)) {
	}
	
	void BoxPanel::init(InitInfo initInfo) {
		object->init(initInfo);
		panel->init(initInfo);
	}
	
	void BoxPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutObject::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f BoxPanel::getMinSize() const {
		return max(object->getMinSize(), panel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxPanel::getNormalSize() const {
		return max(object->getNormalSize(), panel->getNormalSize());
	}
	
	IScalable& BoxPanel::getObject() {
		return *object;
	}
	
	const IScalable& BoxPanel::getObject() const {
		return *object;
	}
	
	const ConstPanel& BoxPanel::getPanel() const {
		return *panel;
	}
	
	BoxPanel* BoxPanel::copy() {
		return new BoxPanel{*this};
	}
	
	void BoxPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<BoxPanel>::decodePointer(const YAML::Node& node, BoxPanel*& boxWithPanel) {
		boxWithPanel = new BoxPanel{
			node["panel"].as<BoxPtr<ConstPanel> >(),
			node["panel"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}