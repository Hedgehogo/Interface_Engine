#include "switch.hpp"
#include "../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "event/switchEvent.hpp"

namespace ui {
	Switch::Switch(IUninteractive *inactiveBackground, IUninteractive *activeBackground, PSbool value, Key key) :
		Interactive_Simple(new OneKeyInteraction{new SwitchEvent{*this}, key}), activeBackground(activeBackground), inactiveBackground(inactiveBackground), active(value) {}
	
	Switch::Switch(IUninteractive *inactiveBackground, IUninteractive *activeBackground, Key key, bool startActive) :
		Switch(inactiveBackground, activeBackground, std::make_shared<Sbool>(), key) {
		active->setValue(startActive);
	}
	
	void Switch::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		interactiveInitInfo.drawManager.add(*this);
		activeBackground->init(interactiveInitInfo.copy(activeDrawManager).toGeneral(*interactionManager, *interactionStack));
		inactiveBackground->init(interactiveInitInfo.copy(inactiveDrawManager).toGeneral(*interactionManager, *interactionStack));
	}
	
	void Switch::switchValue() {
		active->setValue(!active->getValue());
	}
	
	void Switch::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		activeBackground->setPosition(position);
		inactiveBackground->setPosition(position);
	}
	
	void Switch::move(sf::Vector2f position) {
		Layout::move(position);
		activeBackground->move(position);
		inactiveBackground->move(position);
	}
	
	void Switch::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		activeBackground->setSize(size);
		inactiveBackground->setSize(size);
	}
	
	sf::Vector2f Switch::getMinSize() {
		return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
	}
	
	sf::Vector2f Switch::getNormalSize() {
		return max(activeBackground->getNormalSize(), inactiveBackground->getNormalSize());
	}
	
	void Switch::draw() {
		if(active->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	void Switch::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		activeBackground->resize(size, position);
		inactiveBackground->resize(size, position);
	}
	
	Switch *Switch::copy() {
		Switch *switcher{new Switch(inactiveBackground->copy(), activeBackground->copy(), active, dynamic_cast<OneKeyInteraction *>(interaction)->getKey())};
		Layout::copy(switcher);
		return switcher;
	}
	
	bool convertPointer(const YAML::Node &node, Switch *&switcher) {
		auto inactiveBackground{node["inactive-background"].as<IUninteractive *>()};
		auto activeBackground{node["active-background"].as<IUninteractive *>()};
		Key key{convDef<Key>(node["key"], Key::mouseLeft)};
		
		if(node["value"]) {
			switcher = new Switch {
				inactiveBackground, activeBackground,
				Buffer::get<Sbool>(node["value"]),
				key
			};
		} else if(node["state"]) {
			switcher = new Switch {
				inactiveBackground, activeBackground, key,
				convertBool(node["state"], "active", "inactive")
			};
		} else {
			switcher = new Switch {
				inactiveBackground, activeBackground, key,
				convDef(node["start-active"], false)
			};
		}
		return true;
	}
	
	void Switch::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(active->getValue()) {
			activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		} else {
			inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
	
	Switch::~Switch() {
		delete activeBackground;
		delete inactiveBackground;
	}
}