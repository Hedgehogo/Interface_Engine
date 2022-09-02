#include "switch.hpp"
#include "../../../../../../interaction/iInteraction/oneButton/oneButtonInteraction.hpp"
#include "event/switchEvent.hpp"

namespace ui{

    Switch::Switch(IUninteractive *inactiveBackground, IUninteractive *activeBackground, sf::Mouse::Button button, bool startActive) :
        Interactive_Simple(new OneButtonInteraction{new SwitchEvent{*this}, button}), activeBackground(activeBackground), inactiveBackground(inactiveBackground), active(startActive){}

    void Switch::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) {
		Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
        drawManager.add(*this);
		activeBackground->init(renderTarget, activeDrawManager, updateManager, *interactionManager, *interactionStack, panelManager);
		inactiveBackground->init(renderTarget, inactiveDrawManager, updateManager, *interactionManager, *interactionStack, panelManager);
    }

    void Switch::switchValue() {
        active = !active;
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
        if(active)
            activeDrawManager.draw();
        else
            inactiveDrawManager.draw();
    }

    void Switch::resize(sf::Vector2f size, sf::Vector2f position) {
        Layout::resize(size, position);
        activeBackground->resize(size, position);
        inactiveBackground->resize(size, position);
    }

    Switch *Switch::copy() {
        Switch* switcher{new Switch(inactiveBackground->copy(), activeBackground->copy(), sf::Mouse::ButtonCount, active)};
        Layout::copy(switcher);
        return switcher;
    }
	
	Switch *Switch::createFromYaml(const YAML::Node &node) {
		IUninteractive *inactiveBackground;
		IUninteractive *activeBackground;
		sf::Mouse::Button button{sf::Mouse::Button::Left};
		bool startActive{false};
		
		node["inactive-background"] >> inactiveBackground;
		node["active-background"] >> activeBackground;
		if(node["button"])
			node["button"] >> button;
		if(node["state"]) {
			startActive = createBoolFromYaml(node["state"], "active", "inactive");
		} else if(node["start-active"]) {
			node["start-active"] >> startActive;
		}
		
		return new Switch{inactiveBackground, activeBackground, button, startActive};
	}

    void Switch::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        if(active)
            activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        else
            inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
    }

    Switch::~Switch() {
        delete activeBackground;
        delete inactiveBackground;
    }
}