#include "boxWithTabs.hpp"

#include <utility>

namespace ui {
	BoxWithTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f minSize) :
		objects(std::move(objects)), value(value), minSize(minSize) {
	}
	
	BoxWithTabs* BoxWithTabs::Make::make(InitInfo initInfo) {
		return new BoxWithTabs{std::move(*this), initInfo};
	}
	
	BoxWithTabs::BoxWithTabs(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		drawManagers(make.objects.size()),
		objects(mapMake(std::move(make.objects), [&](std::size_t i) {
			return initInfo.copy(drawManagers[i]);
		})),
		value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxWithTabs::BoxWithTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(std::move(value)) {
	}
	
	BoxWithTabs::BoxWithTabs(const BoxWithTabs& other) :
		Box(other), drawManagers(other.objects.size()), objects(other.objects), value(other.value) {
	}
	
	void BoxWithTabs::init(InitInfo initInfo) {
		for(std::size_t i = 0; i < objects.size(); ++i) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
		initInfo.drawManager.add(*this);
	}
	
	void BoxWithTabs::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
		for(auto& object: objects) {
			object->setPosition(position);
		}
	}
	
	void BoxWithTabs::move(sf::Vector2f position) {
		ILayout::move(position);
		for(auto& object: objects) {
			object->move(position);
		}
	}
	
	void BoxWithTabs::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
		for(auto& object: objects) {
			object->setSize(size);
		}
	}
	
	void BoxWithTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayout::resize(size, position);
		for(auto& object: objects) {
			object->resize(size, position);
		}
	}
	
	void BoxWithTabs::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	bool BoxWithTabs::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	std::size_t BoxWithTabs::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxWithTabs::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxWithTabs::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxWithTabs* BoxWithTabs::copy() {
		return new BoxWithTabs{*this};
	}
	
	bool DecodePointer<BoxWithTabs>::decodePointer(const YAML::Node& node, BoxWithTabs*& boxWithTabs) {
		boxWithTabs = new BoxWithTabs{
			node["objects"].as<std::vector<BoxPtr<IScalable> > >(),
			Buffer::get<ISint>(node["value"]),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}