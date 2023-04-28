#include "boxWithChangeableObjects.hpp"

namespace ui {
	BoxWithChangeableObjects::BoxWithChangeableObjects(std::vector<IScalable *> objects, std::shared_ptr<SValue<uint>> value, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value(value), drawManagers(this->objects.size()) {
	}
	
	BoxWithChangeableObjects::BoxWithChangeableObjects(std::vector<IScalable *> objects, uint index, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value(std::make_shared<SValue<uint>>(index)), drawManagers(this->objects.size()) {
	}
	
	void BoxWithChangeableObjects::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		
		for(int i = 0; i < objects.size(); ++i) {
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
	
	IScalable *BoxWithChangeableObjects::getObject() {
		return objects[value->getValue()];
	}
	
	void BoxWithChangeableObjects::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	void BoxWithChangeableObjects::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		objects[value->getValue()]->resize(size, position);
	}
	
	bool BoxWithChangeableObjects::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	BoxWithChangeableObjects *BoxWithChangeableObjects::copy() {
		return new BoxWithChangeableObjects{objects, value, minimumSize};
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithChangeableObjects *&boxWithChangeableObjects) {
		std::vector<IScalable *> objects;
		sf::Vector2f minSize{0, 0};
		
		for(auto &objectNode: node["objects"]) {
			IScalable *object;
			objectNode >> object;
			objects.push_back(object);
		}
		
		if(node["minSize"])
			node["minSize"] >> minSize;
		
		if(node["value"]) {
			std::shared_ptr<SValue<uint>> value;
			value = Buffer::get<SValue<uint>>(node["value"]);
			boxWithChangeableObjects = new BoxWithChangeableObjects{objects, value, minSize};
			return true;
		}
		
		uint index{0};
		if(node["index"])
			node["index"] >> index;
		
		boxWithChangeableObjects = new BoxWithChangeableObjects{objects, index, minSize};
		return true;
	}
	
	bool DecodePointer<BoxWithChangeableObjects>::decodePointer(const YAML::Node &node, BoxWithChangeableObjects *&boxWithChangeableObjects) {
		std::vector<IScalable *> objects;
		sf::Vector2f minSize{0, 0};
		
		for(auto &objectNode: node["objects"]) {
			IScalable *object;
			objectNode >> object;
			objects.push_back(object);
		}
		
		if(node["minSize"])
			node["minSize"] >> minSize;
		
		if(node["value"]) {
			std::shared_ptr<SValue<uint>> value;
			value = Buffer::get<SValue<uint>>(node["value"]);
			boxWithChangeableObjects = new BoxWithChangeableObjects{objects, value, minSize};
			return true;
		}
		
		uint index{0};
		if(node["index"])
			node["index"] >> index;
		
		boxWithChangeableObjects = new BoxWithChangeableObjects{objects, index, minSize};
		return true;
	}
	
	void BoxWithChangeableObjects::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		objects[value->getValue()]->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}