#include "boxWithTabs.hpp"

#include <utility>

namespace ui {
	BoxWithTabs::BoxWithTabs(const std::vector<IScalable*>& objects, PISint  value, const sf::Vector2f& minSize) :
		Box(minSize, size), LayoutWithObjectsArray(objects), value(std::move(value)), drawManagers(objects.size()) {}
	
	void BoxWithTabs::init(InitInfo initInfo) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
		initInfo.drawManager.add(*this);
	}
	
	void BoxWithTabs::setPosition(sf::Vector2f position) {
		Layout::setPosition(position);
		for (auto & object : objects) {
			object->setPosition(position);
		}
	}
	
	void BoxWithTabs::move(sf::Vector2f position) {
		Layout::move(position);
		for (auto & object: objects) {
			object->move(position);
		}
	}
	
	void BoxWithTabs::setSize(sf::Vector2f size) {
		Layout::setSize(size);
		for (auto & object: objects) {
			object->setSize(size);
		}
	}
	
	void BoxWithTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		for (auto & object: objects) {
			object->resize(size, position);
		}
	}
	
	void BoxWithTabs::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	bool BoxWithTabs::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	BoxWithTabs* BoxWithTabs::copy() {
		auto boxWithTabsCopy{new BoxWithTabs{ui::copy(objects), value, minimumSize}};
		Layout::copy(boxWithTabsCopy);
		return boxWithTabsCopy;
	}
	
	bool DecodePointer<BoxWithTabs>::decodePointer(const YAML::Node& node, BoxWithTabs*& boxWithTabs) {
		boxWithTabs = new BoxWithTabs{
			node["objects"].as<std::vector<IScalable*>>(),
			Buffer::get<ISint>(node["value"]),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}