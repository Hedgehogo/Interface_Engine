#include "Switcher.hpp"
#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "SwitherEvent/SwitcherEvent.hpp"

namespace ui {
	Switcher::Make::Make(BoxPtr<IScalable::Make>&& inactiveBackground, BoxPtr<IScalable::Make>&& activeBackground, PSbool value, Key key) :
		inactiveBackground(std::move(inactiveBackground)), activeBackground(std::move(activeBackground)), value(value), key(key) {
	}
	
	Switcher::Make::Make(BoxPtr<IScalable::Make>&& inactiveBackground, BoxPtr<IScalable::Make>&& activeBackground, Key key, bool startActive) :
		inactiveBackground(std::move(inactiveBackground)), activeBackground(std::move(activeBackground)), value(std::make_shared<Sbool>(startActive)), key(key) {
	}
	
	Switcher* Switcher::Make::make(InitInfo initInfo) {
		return new Switcher{std::move(*this), initInfo};
	}
	
	Switcher::Switcher(Make&& make, InitInfo initInfo) :
		BaseInteractive(makeBoxPtr<IBaseInteraction, OneKeyInteraction>(makeBoxPtr<KeyEvent, SwitcherEvent>(make.value), make.key), initInfo),
		inactiveBackground(make.inactiveBackground->make(initInfo.copy(inactiveDrawManager))),
		activeBackground(make.activeBackground->make(initInfo.copy(activeDrawManager))),
		active(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	Switcher::Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, PSbool value, Key key) :
		BaseInteractive(makeBoxPtr<IBaseInteraction, OneKeyInteraction>(makeBoxPtr<KeyEvent, SwitcherEvent>(value), key)),
		inactiveBackground(std::move(inactiveBackground)), activeBackground(std::move(activeBackground)), active(value) {
	}
	
	Switcher::Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, Key key, bool startActive) :
		Switcher(std::move(inactiveBackground), std::move(activeBackground), std::make_shared<Sbool>(startActive), key) {
	}
	
	void Switcher::init(InitInfo initInfo) {
		BaseInteractive::init(initInfo);
		initInfo.drawManager.add(*this);
		inactiveBackground->init(initInfo.copy(inactiveDrawManager));
		activeBackground->init(initInfo.copy(activeDrawManager));
	}
	
	void Switcher::setPosition(sf::Vector2f position) {
		layout.setPosition(position);
		inactiveBackground->setPosition(position);
		activeBackground->setPosition(position);
	}
	
	void Switcher::move(sf::Vector2f position) {
		layout.move(position);
		inactiveBackground->move(position);
		activeBackground->move(position);
	}
	
	void Switcher::setSize(sf::Vector2f size) {
		layout.setSize(size);
		inactiveBackground->setSize(size);
		activeBackground->setSize(size);
	}
	
	sf::Vector2f Switcher::getMinSize() const {
		return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
	}
	
	sf::Vector2f Switcher::getNormalSize() const {
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
		layout.resize(size, position);
		activeBackground->resize(size, position);
		inactiveBackground->resize(size, position);
	}
	
	bool Switcher::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate;
		if(active->getValue()) {
			backgroundUpdate = activeBackground->updateInteractions(mousePosition);
		} else {
			backgroundUpdate = inactiveBackground->updateInteractions(mousePosition);
		}
		return BaseInteractive::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	Switcher* Switcher::copy() {
		return new Switcher{*this};
	}
	
	void Switcher::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(active->getValue()) {
			activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		} else {
			inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
	
	LayoutData& Switcher::layoutGetData() {
		return layout;
	}
	
	const LayoutData& Switcher::layoutGetData() const {
		return layout;
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
}