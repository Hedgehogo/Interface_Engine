#include "boxWithPanel.hpp"

namespace ui {
	BoxWithPanel::Make::Make(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		panel(std::move(panel)), object(std::move(object)), minSize(minSize) {
	}
	
	BoxWithPanel* BoxWithPanel::Make::make(InitInfo initInfo) {
		return new BoxWithPanel{std::move(*this), initInfo};
	}
	
	BoxWithPanel::BoxWithPanel(Make&& make, InitInfo initInfo) :
		Box(make.minSize), object(make.object->make(initInfo)), panel(std::move(make.panel)) {
		panel->init(initInfo);
	}
	
	BoxWithPanel::BoxWithPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)), panel(std::move(panel)) {
	}
	
	void BoxWithPanel::init(InitInfo initInfo) {
		object->init(initInfo);
		panel->init(initInfo);
	}
	
	void BoxWithPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutWithObject::resize(size, position);
		panel->resize(size, position);
	}
	
	sf::Vector2f BoxWithPanel::getMinSize() const {
		return max(object->getMinSize(), panel->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithPanel::getNormalSize() const {
		return max(object->getNormalSize(), panel->getNormalSize());
	}
	
	IScalable& BoxWithPanel::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithPanel::getObject() const {
		return *object;
	}
	
	BoxWithPanel* BoxWithPanel::copy() {
		return new BoxWithPanel{*this};
	}
	
	void BoxWithPanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		panel->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<BoxWithPanel>::decodePointer(const YAML::Node& node, BoxWithPanel*& boxWithPanel) {
		boxWithPanel = new BoxWithPanel{
			node["panel"].as<BoxPtr<ConstPanel> >(),
			node["panel"].as<BoxPtr<IScalable> >(),
			convDef(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}