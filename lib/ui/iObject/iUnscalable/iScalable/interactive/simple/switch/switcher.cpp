#include "switcher.hpp"
#include "../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "event/switcherEvent.hpp"

namespace ui {
	Switcher::Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, PSbool value, Key key) :
		BaseInteractive(makeBoxPtr<IInteraction, OneKeyInteraction>(makeBoxPtr<KeyEvent, SwitcherEvent>(value), key)),
		activeBackground(std::move(activeBackground)), inactiveBackground(std::move(inactiveBackground)), active(value) {
	}
	
	Switcher::Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, Key key, bool startActive) :
		Switcher(std::move(inactiveBackground), std::move(activeBackground), std::make_shared<Sbool>(startActive), key) {
	}
	
	void Switcher::init(InitInfo initInfo) {
		BaseInteractive::init(initInfo);
		initInfo.drawManager.add(*this);
		activeBackground->init(initInfo.copy(activeDrawManager));
		inactiveBackground->init(initInfo.copy(inactiveDrawManager));
	}
	
	void Switcher::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
		activeBackground->setPosition(position);
		inactiveBackground->setPosition(position);
	}
	
	void Switcher::move(sf::Vector2f position) {
		ILayout::move(position);
		activeBackground->move(position);
		inactiveBackground->move(position);
	}
	
	void Switcher::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
		activeBackground->setSize(size);
		inactiveBackground->setSize(size);
	}
	
	sf::Vector2f Switcher::getMinSize() const {
		return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
	}
	
	sf::Vector2f Switcher::getNormalSize() const {
		return max(activeBackground->getNormalSize(), inactiveBackground->getNormalSize());
	}
	
	LayoutData& Switcher::getLayoutData() {
		return layout;
	}
	
	const LayoutData& Switcher::getLayoutData() const {
		return layout;
	}
	
	void Switcher::draw() {
		if(active->getValue()) {
			activeDrawManager.draw();
		} else {
			inactiveDrawManager.draw();
		}
	}
	
	void Switcher::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayout::resize(size, position);
		activeBackground->resize(size, position);
		inactiveBackground->resize(size, position);
	}
	
	bool Switcher::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate;
		if(active->getValue())
			backgroundUpdate = activeBackground->updateInteractions(mousePosition);
		else
			backgroundUpdate = inactiveBackground->updateInteractions(mousePosition);
		return BaseInteractive::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	Switcher* Switcher::copy() {
		return new Switcher{*this};
	}
	
	bool DecodePointer<Switcher>::decodePointer(const YAML::Node& node, Switcher*& switcher) {
		auto inactiveBackground{node["inactive-background"].as<BoxPtr<IScalable> >()};
		auto activeBackground{node["active-background"].as<BoxPtr<IScalable> >()};
		Key key{convDef<Key>(node["key"], Key::mouseLeft)};
		
		if(node["value"]) {
			switcher = new Switcher{
				std::move(inactiveBackground),
				std::move(activeBackground),
				Buffer::get<Sbool>(node["value"]),
				key
			};
		} else if(node["state"]) {
			switcher = new Switcher{
				std::move(inactiveBackground),
				std::move(activeBackground),
				key,
				convertBool(node["state"], "active", "inactive")
			};
		} else {
			switcher = new Switcher{
				std::move(inactiveBackground),
				std::move(activeBackground),
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
}