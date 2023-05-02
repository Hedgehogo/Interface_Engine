#include "boxSwitcherTabs.hpp"

#include "../switcher/boxSwitcher.hpp"
#include "ui/enums/keyHandler/keyHandler.hpp"
#include "ui/interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "modules/appendix/yaml-cpp/shared/value/converts/toBool/equals/sConvertToBoolEquals.hpp"
#include "event/switcherTabsEvent.hpp"

namespace ui {
	BoxSwitcherTabs::BoxSwitcherTabs(std::vector<IScalable*> objects, PSint value, Key key, bool isHorizontal, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray(objects), Interactive_Simple(new OneKeyInteraction{new SwitcherTabsEvent{value, this}, key}), isHorizontal(isHorizontal), value(value) {
	}
	
	void BoxSwitcherTabs::init(InitInfo initInfo) {
		LayoutWithObjectsArray::init(initInfo);
		Interactive::init(initInfo);
	}
	
	void BoxSwitcherTabs::setPosition(sf::Vector2f position) {
		LayoutWithObjectsArray::setPosition(position);
		LayoutWithObjectsArray::move(position - this->position);
	}
	
	void BoxSwitcherTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		LayoutWithObjectsArray::resize(size, position);
		
		if (isHorizontal){
			sf::Vector2f objectSize{size.x / objects.size(), size.y};
			float positionX = position.x;
			for(const auto& object: objects){
				object->resize(objectSize, {positionX, position.y});
				positionX += objectSize.x;
			}
		} else {
			sf::Vector2f objectSize{size.x, size.y / objects.size()};
			float positionY = position.y;
			for(const auto& object: objects) {
				object->resize(objectSize, {position.x, positionY});
				positionY += objectSize.y;
			}
		}
		
	}
	
	int BoxSwitcherTabs::getTab(sf::Vector2f position) {
		return static_cast<int>(isHorizontal ? (position.x - this->position.x) / (size.x / objects.size()) : (position.y - this->position.y) / (size.y / objects.size()));
	}
	
	BoxSwitcherTabs* BoxSwitcherTabs::copy() {
		BoxSwitcherTabs* switcherTabsCopy{new BoxSwitcherTabs{ui::copy(objects), value, dynamic_cast<OneKeyInteraction*>(interaction)->getKey(), isHorizontal, minimumSize}};
		Interactive_Simple::copy(switcherTabsCopy);
		Layout::copy(switcherTabsCopy);
		return switcherTabsCopy;
	}
	
	bool DecodePointer<BoxSwitcherTabs>::decodePointer(const YAML::Node& node, BoxSwitcherTabs*& switcherTabs) {
		switcherTabs = new BoxSwitcherTabs {
			node["objects"].as<std::vector<IScalable*>>(),
			Buffer::get<Sint>(node["value"]),
			convDef(node["key"], Key::mouseLeft),
			convBoolDef(node["direction"], "horizontal", "vertical"),
			convDef(node["min-size"], sf::Vector2f{})
		};
		
		return true;
	}
}