#include "BoxTabs.hpp"

#include <utility>

namespace ui {
	BoxTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f minSize) :
		objects(std::move(objects)), value(value), minSize(minSize) {
	}
	
	BoxTabs* BoxTabs::Make::make(InitInfo initInfo) {
		return new BoxTabs{std::move(*this), initInfo};
	}
	
	BoxTabs::BoxTabs(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		drawManagers(make.objects.size()),
		objects(mapMake(std::move(make.objects), [&](std::size_t i) {
			return initInfo.copy(drawManagers[i]);
		})),
		value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxTabs::BoxTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(std::move(value)) {
	}
	
	BoxTabs::BoxTabs(const BoxTabs& other) :
		Box(other), drawManagers(other.objects.size()), objects(other.objects), value(other.value) {
	}
	
	void BoxTabs::init(InitInfo initInfo) {
		for(std::size_t i = 0; i < objects.size(); ++i) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
		initInfo.drawManager.add(*this);
	}
	
	void BoxTabs::setPosition(sf::Vector2f position) {
		layout.setPosition(position);
		for(auto& object: objects) {
			object->setPosition(position);
		}
	}
	
	void BoxTabs::move(sf::Vector2f position) {
		layout.move(position);
		for(auto& object: objects) {
			object->move(position);
		}
	}
	
	void BoxTabs::setSize(sf::Vector2f size) {
		layout.setSize(size);
		for(auto& object: objects) {
			object->setSize(size);
		}
	}
	
	void BoxTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		for(auto& object: objects) {
			object->resize(size, position);
		}
	}
	
	void BoxTabs::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	bool BoxTabs::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	std::size_t BoxTabs::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxTabs::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxTabs::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxTabs* BoxTabs::copy() {
		return new BoxTabs{*this};
	}
	
	bool DecodePointer<BoxTabs>::decodePointer(const YAML::Node& node, BoxTabs*& boxWithTabs) {
		boxWithTabs = new BoxTabs{
			node["objects"].as<std::vector<BoxPtr<IScalable> > >(),
			Buffer::get<ISint>(node["value"]),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}