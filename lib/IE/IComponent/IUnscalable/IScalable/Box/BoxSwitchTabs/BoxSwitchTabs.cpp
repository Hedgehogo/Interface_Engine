#include "BoxSwitchTabs.hpp"

namespace ui {
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<uint> value, sf::Vector2f minSize) :
		objects(std::move(objects)), value(value), minSize(minSize) {
	}
	
	BoxSwitchTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, uint index, sf::Vector2f minSize) :
		objects(std::move(objects)), value(std::make_shared<SValue<uint> >(index)), minSize(minSize) {
	}
	
	BoxSwitchTabs* BoxSwitchTabs::Make::make(InitInfo initInfo) {
		return new BoxSwitchTabs{std::move(*this), initInfo};
	}
	
	BoxSwitchTabs::BoxSwitchTabs(Make&& make, InitInfo initInfo) :
		Box(make.minSize), drawManagers(make.objects.size()),
		objects(mapMake(std::move(make.objects), [&](std::size_t i) {
			return initInfo.copy(drawManagers[i]);
		})), value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, PSValue<uint> value, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(value) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, uint index, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(std::make_shared<SValue<uint>>(index)) {
	}
	
	BoxSwitchTabs::BoxSwitchTabs(const BoxSwitchTabs& other) :
		Box(other), drawManagers(other.objects.size()), objects(other.objects), value(other.value) {
	}
	
	void BoxSwitchTabs::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		
		for(std::size_t i = 0; i < objects.size(); ++i) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
	}
	
	void BoxSwitchTabs::setValue(std::shared_ptr<SValue<uint>> index) {
		value = index;
	}
	
	std::shared_ptr<SValue<uint>> BoxSwitchTabs::getValue() {
		return value;
	}
	
	void BoxSwitchTabs::setIndex(uint index) {
		value->setValue(index);
	}
	
	uint BoxSwitchTabs::getIndex() {
		return value->getValue();
	}
	
	void BoxSwitchTabs::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	void BoxSwitchTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		for(auto& object : objects) {
			object->resize(size, position);
		}
	}
	
	bool BoxSwitchTabs::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	std::size_t BoxSwitchTabs::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxSwitchTabs::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxSwitchTabs::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxSwitchTabs* BoxSwitchTabs::copy() {
		return new BoxSwitchTabs{*this};
	}
	
	bool DecodePointer<BoxSwitchTabs>::decodePointer(const YAML::Node& node, BoxSwitchTabs*& boxWithChangeableObjects) {
		auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
		auto minSize{convDef(node["min-size"], sf::Vector2f{})};
		
		if(node["value"]) {
			boxWithChangeableObjects = new BoxSwitchTabs{
				std::move(objects),
				Buffer::get<SValue<uint>>(node["value"]),
				minSize
			};
		} else {
			boxWithChangeableObjects = new BoxSwitchTabs{
				std::move(objects),
				convDef(node["index"], 0u),
				minSize
			};
		}
		return true;
	}
	
	void BoxSwitchTabs::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		objects[value->getValue()]->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}