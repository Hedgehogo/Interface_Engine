#include "LayerWithChangeableObjects.hpp"

namespace ui {
	LayerWithChangeableObjects::LayerWithChangeableObjects(std::vector<IScalable *> objects, std::shared_ptr<SValue<uint>> value, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value(value), drawManagers(this->objects.size()) {
	}
	
	LayerWithChangeableObjects::LayerWithChangeableObjects(std::vector<IScalable *> objects, uint index, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value(std::make_shared<SValue<uint>>(index)), drawManagers(this->objects.size()) {
	}
	
	void LayerWithChangeableObjects::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		
		for(int i = 0; i < objects.size(); ++i) {
			objects[i]->init(initInfo.copy(drawManagers[i]));
		}
	}
	
	
	void LayerWithChangeableObjects::setValue(std::shared_ptr<SValue<uint>> index) {
		value = index;
	}
	
	std::shared_ptr<SValue<uint>> LayerWithChangeableObjects::getValue() {
		return value;
	}
	
	void LayerWithChangeableObjects::setIndex(uint index) {
		value->setValue(index);
	}
	
	uint LayerWithChangeableObjects::getIndex() {
		return value->getValue();
	}
	
	IScalable *LayerWithChangeableObjects::getObject() {
		return objects[value->getValue()];
	}
	
	void LayerWithChangeableObjects::draw() {
		drawManagers[value->getValue()].draw();
	}
	
	void LayerWithChangeableObjects::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		objects[value->getValue()]->resize(size, position);
	}
	
	bool LayerWithChangeableObjects::updateInteractions(sf::Vector2f mousePosition) {
		return objects[value->getValue()]->updateInteractions(mousePosition);
	}
	
	LayerWithChangeableObjects *LayerWithChangeableObjects::copy() {
		return new LayerWithChangeableObjects{objects, value, minimumSize};
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithChangeableObjects *&layerWithChangeableObjects) {
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
			layerWithChangeableObjects = new LayerWithChangeableObjects{objects, value, minSize};
			return true;
		}
		
		uint index{0};
		if(node["index"])
			node["index"] >> index;
		layerWithChangeableObjects = new LayerWithChangeableObjects{objects, index, minSize};
		return true;
	}
	
	void LayerWithChangeableObjects::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		objects[value->getValue()]->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
} // ui