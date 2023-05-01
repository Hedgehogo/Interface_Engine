#include "switcher.hpp"
#include "../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "event/switcherEvent.hpp"

namespace ui {
	Switcher::Switcher(IScalable* inactiveBackground, IScalable* activeBackground, PSbool value, Key key) :
		Interactive_Simple(new OneKeyInteraction{new SwitcherEvent{value}, key}), activeBackground(activeBackground), inactiveBackground(inactiveBackground), active(value) {
	}
	
	Switcher::Switcher(IScalable* inactiveBackground, IScalable* activeBackground, Key key, bool startActive) :
		Switcher(inactiveBackground, activeBackground, std::make_shared<Sbool>(startActive), key) {
	}
	
	void Switcher::init(InteractiveInitInfo interactiveInitInfo) {
		Interactive_Simple::init(interactiveInitInfo);
		interactiveInitInfo.drawManager.add(*this);
		activeBackground->init(interactiveInitInfo.copy(activeDrawManager).toGeneral(*interactionManager, *interactionStack));
		inactiveBackground->init(interactiveInitInfo.copy(inactiveDrawManager).toGeneral(*interactionManager, *interactionStack));
	}
	
	void Switcher::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		activeBackground->setPosition(position);
		inactiveBackground->setPosition(position);
	}
	
	void Switcher::move(sf::Vector2f position) {
		Layout::move(position);
		activeBackground->move(position);
		inactiveBackground->move(position);
	}
	
	void Switcher::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		activeBackground->setSize(size);
		inactiveBackground->setSize(size);
	}
	
	sf::Vector2f Switcher::getMinSize() {
		return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
	}
	
	sf::Vector2f Switcher::getNormalSize() {
		return max(activeBackground->getNormalSize(), inactiveBackground->getNormalSize());
	}
	
	void Switcher::draw() {
		if(active->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	void Switcher::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		activeBackground->resize(size, position);
		inactiveBackground->resize(size, position);
	}
	
	bool Switcher::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate;
		if(active->getValue())
			backgroundUpdate = activeBackground->updateInteractions(mousePosition);
		else
			backgroundUpdate = inactiveBackground->updateInteractions(mousePosition);
		return Interactive_Simple::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	Switcher* Switcher::copy() {
		Switcher* switcher{new Switcher(inactiveBackground->copy(), activeBackground->copy(), active, dynamic_cast<OneKeyInteraction*>(interaction)->getKey())};
		Layout::copy(switcher);
		return switcher;
	}
	
	bool DecodePointer<Switcher>::decodePointer(const YAML::Node& node, Switcher*& switcher) {
		auto inactiveBackground{node["inactive-background"].as<IScalable*>()};
		auto activeBackground{node["active-background"].as<IScalable*>()};
		Key key{convDef<Key>(node["key"], Key::mouseLeft)};
		
		if(node["value"]) {
			switcher = new Switcher{
				inactiveBackground,
				activeBackground,
				Buffer::get<Sbool>(node["value"]),
				key
			};
		} else if(node["state"]) {
			switcher = new Switcher{
				inactiveBackground,
				activeBackground,
				key,
				convertBool(node["state"], "active", "inactive")
			};
		} else {
			switcher = new Switcher{
				inactiveBackground,
				activeBackground,
				key,
				convDef(node["start-active"], false)
			};
		}
		return true;
	}
	
	void Switcher::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(active->getValue()) {
			activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		} else {
			inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
	
	Switcher::~Switcher() {
		delete activeBackground;
		delete inactiveBackground;
	}
}