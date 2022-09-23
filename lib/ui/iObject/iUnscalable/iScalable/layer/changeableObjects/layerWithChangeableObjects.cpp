#include "LayerWithChangeableObjects.hpp"

namespace ui
{
	LayerWithChangeableObjects::LayerWithChangeableObjects(std::vector<IScalable *> objects, std::shared_ptr<WithValue<uint>> value, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value( value), drawManagers( this->objects.size()) {}

	LayerWithChangeableObjects::LayerWithChangeableObjects(std::vector<IScalable *> objects, uint index, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(objects), objects(std::move(objects)), value( std::make_shared<WithValue<uint>>( index)), drawManagers( this->objects.size()) {}

	void LayerWithChangeableObjects::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager)
	{
		drawManager.add(*this);

		for ( int i = 0; i < objects.size(); ++i ) {
			objects[i]->init(renderTarget, drawManagers[i], updateManager, interactionManager, interactionStack, panelManager);
		}
	}


	void LayerWithChangeableObjects::setValue(std::shared_ptr<WithValue<uint>> index)
	{
		value = index;
	}

	std::shared_ptr<WithValue<uint>> LayerWithChangeableObjects::getValue()
	{
		return value;
	}

	void LayerWithChangeableObjects::setIndex(uint index)
	{
		value->setValue( index);
	}

	uint LayerWithChangeableObjects::getIndex()
	{
		return value->getValue();
	}

	IScalable *LayerWithChangeableObjects::getObject()
	{
		return objects[value->getValue()];
	}

	void LayerWithChangeableObjects::draw()
	{
		drawManagers[value->getValue()].draw();
	}

	void LayerWithChangeableObjects::resize(sf::Vector2f size, sf::Vector2f position)
	{
		Layer::resize( size, position );
		objects[value->getValue()]->resize( size, position );
	}

	bool LayerWithChangeableObjects::updateInteractions(sf::Vector2f mousePosition)
	{
		return objects[value->getValue()]->updateInteractions( mousePosition);
	}

	LayerWithChangeableObjects *LayerWithChangeableObjects::copy()
	{
		return new LayerWithChangeableObjects{ objects, value, minimumSize};
	}

	LayerWithChangeableObjects *LayerWithChangeableObjects::createFromYaml(const YAML::Node &node)
	{
		std::vector<IScalable *> objects;
		sf::Vector2f minSize {0,0};

		for ( auto &object : node["objects"] ) {
			IScalable* newObject;
			object >> newObject;
			objects.push_back(newObject);
		}

		if (node["minSize"]) node["minSize"] >> minSize;

		if (node["value"]) {
			std::shared_ptr<WithValue<uint>> value;
			value = ui::Buffer::get<WithValue<uint>>(node["value"]);
			return new LayerWithChangeableObjects { objects, value, minSize };
		}

		uint index {0};
		if (node["index"]) node["index"] >> index;
		return new LayerWithChangeableObjects { objects, index, minSize };
	}

	void LayerWithChangeableObjects::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset)
	{
		objects[value->getValue()]->drawDebug( renderTarget, indent, indentAddition, hue, hueOffset);
	}
} // ui