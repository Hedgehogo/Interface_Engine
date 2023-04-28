#include "simpleSwither.hpp"
#include "../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "event/simpleSwitcherEvent.hpp"

namespace ui {
	SimpleSwitcher::SimpleSwitcher(IUninteractive* inactiveBackground, IUninteractive* activeBackground, PSbool value, Key key) :
		Interactive_Simple(new OneKeyInteraction{new SimpleSwitcherEvent{*this}, key}), activeBackground(activeBackground), inactiveBackground(inactiveBackground), active(value) {
	}
	
	SimpleSwitcher::SimpleSwitcher(IUninteractive* inactiveBackground, IUninteractive* activeBackground, Key key, bool startActive) :
		SimpleSwitcher(inactiveBackground, activeBackground, std::make_shared<Sbool>(), key) {
		active->setValue(startActive);
	}
	
	void SimpleSwitcher::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		interactiveInitInfo.drawManager.add(*this);
		activeBackground->init(interactiveInitInfo.copy(activeDrawManager).toGeneral(*interactionManager, *interactionStack));
		inactiveBackground->init(interactiveInitInfo.copy(inactiveDrawManager).toGeneral(*interactionManager, *interactionStack));
	}
	
	void SimpleSwitcher::switchValue() {
		active->setValue(!active->getValue());
	}
	
	void SimpleSwitcher::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		activeBackground->setPosition(position);
		inactiveBackground->setPosition(position);
	}
	
	void SimpleSwitcher::move(sf::Vector2f position) {
		Layout::move(position);
		activeBackground->move(position);
		inactiveBackground->move(position);
	}
	
	void SimpleSwitcher::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		activeBackground->setSize(size);
		inactiveBackground->setSize(size);
	}
	
	sf::Vector2f SimpleSwitcher::getMinSize() {
		return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
	}
	
	sf::Vector2f SimpleSwitcher::getNormalSize() {
		return max(activeBackground->getNormalSize(), inactiveBackground->getNormalSize());
	}
	
	void SimpleSwitcher::draw() {
		if(active->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	void SimpleSwitcher::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		activeBackground->resize(size, position);
		inactiveBackground->resize(size, position);
	}
	
	SimpleSwitcher* SimpleSwitcher::copy() {
		SimpleSwitcher* switcher{new SimpleSwitcher(inactiveBackground->copy(), activeBackground->copy(), active, dynamic_cast<OneKeyInteraction*>(interaction)->getKey())};
		Layout::copy(switcher);
		return switcher;
	}
	
	
	bool DecodePointer<SimpleSwitcher>::decodePointer(const YAML::Node& node, SimpleSwitcher*& simpleSwitcher) {
		auto inactiveBackground{node["inactive-background"].as<IUninteractive*>()};
		auto activeBackground{node["active-background"].as<IUninteractive*>()};
		Key key{convDef<Key>(node["key"], Key::mouseLeft)};
		
		if(node["value"]) {
			simpleSwitcher = new SimpleSwitcher{
				inactiveBackground, activeBackground,
				Buffer::get<Sbool>(node["value"]),
				key
			};
		} else if(node["state"]) {
			simpleSwitcher = new SimpleSwitcher{
				inactiveBackground, activeBackground, key,
				convertBool(node["state"], "active", "inactive")
			};
		} else {
			simpleSwitcher = new SimpleSwitcher{
				inactiveBackground, activeBackground, key,
				convDef(node["start-active"], false)
			};
		}
		return true;
	}
	
	void SimpleSwitcher::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(active->getValue()) {
			activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		} else {
			inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
	
	SimpleSwitcher::~SimpleSwitcher() {
		delete activeBackground;
		delete inactiveBackground;
	}
}