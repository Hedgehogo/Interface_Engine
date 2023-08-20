#include "boxWithChangeableObjects.hpp"

namespace ui {
	BoxWithChangeableObjects::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<uint> value, sf::Vector2f minSize) :
		objects(std::move(objects)), value(value), minSize(minSize) {
	}
	
	BoxWithChangeableObjects::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, uint index, sf::Vector2f minSize) :
		objects(std::move(objects)), value(std::make_shared<SValue<uint> >(index)), minSize(minSize) {
	}
	
	BoxWithChangeableObjects* BoxWithChangeableObjects::Make::make(InitInfo initInfo) {
		return new BoxWithChangeableObjects{std::move(*this), initInfo};
	}
	
	BoxWithChangeableObjects::BoxWithChangeableObjects(Make&& make, InitInfo initInfo) :
		Box(make.minSize), drawManagers(make.objects.size()),
		objects(mapMake(std::move(make.objects), [&](std::size_t i) {
			return initInfo.copy(drawManagers[i]);
		})), value(make.value) {
		initInfo.drawManager.add(*this);
	}
	
	BoxWithChangeableObjects::BoxWithChangeableObjects(std::vector<BoxPtr<IScalable> >&& objects, PSValue<uint> value, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(value) {
	}
	
	BoxWithChangeableObjects::BoxWithChangeableObjects(std::vector<BoxPtr<IScalable> >&& objects, uint index, sf::Vector2f minSize) :
		Box(minSize), drawManagers(objects.size()), objects(std::move(objects)), value(std::make_shared<SValue<uint>>(index)) {
	}
	
	BoxWithChangeableObjects::BoxWithChangeableObjects(const BoxWithChangeableObjects& other) :
		Box(other), drawManagers(other.objects.size()), objects(other.objects), value(other.value) {
	}
	
	void BoxWithChangeableObjects::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		
		for(std::size_t i = 0; i < objects.size(); ++i) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
	}
	
	void BoxWithChangeableObjects::setValue(std::shared_ptr<SValue<uint>> index) {
		value = index;
	}
	
	std::shared_ptr<SValue<uint>> BoxWithChangeableObjects::getValue() {
		return value;
	}
	
	void BoxWithChangeableObjects::setIndex(uint index) {
		value->setValue(index);
	}
	
	uint BoxWithChangeableObjects::getIndex() {
		return value->getValue();
	}
	
	void BoxWithChangeableObjects::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	void BoxWithChangeableObjects::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		for(auto& object : objects) {
			object->resize(size, position);
		}
	}
	
	bool BoxWithChangeableObjects::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	std::size_t BoxWithChangeableObjects::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxWithChangeableObjects::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxWithChangeableObjects::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxWithChangeableObjects* BoxWithChangeableObjects::copy() {
		return new BoxWithChangeableObjects{*this};
	}
	
	bool DecodePointer<BoxWithChangeableObjects>::decodePointer(const YAML::Node& node, BoxWithChangeableObjects*& boxWithChangeableObjects) {
		auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
		auto minSize{convDef(node["min-size"], sf::Vector2f{})};
		
		if(node["value"]) {
			boxWithChangeableObjects = new BoxWithChangeableObjects{
				std::move(objects),
				Buffer::get<SValue<uint>>(node["value"]),
				minSize
			};
		} else {
			boxWithChangeableObjects = new BoxWithChangeableObjects{
				std::move(objects),
				convDef(node["index"], 0u),
				minSize
			};
		}
		return true;
	}
	
	void BoxWithChangeableObjects::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		objects[value->getValue()]->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}