#include "LayerWithChangeableObjects.hpp"

namespace ui
{
	LayerWithChangeableObjects::LayerWithChangeableObjects(std::vector<IScalable *> objects, uint current, sf::Vector2f minSize) :
	current(current), Layer(minSize), LayoutWithObjectsArray(objects), drawManagers(objects.size()), updateManagers(objects.size()) {}

	void LayerWithChangeableObjects::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager)
	{
		drawManager.add(*this);
		updateManager.add(*this);

		for ( int i = 0; i < objects.size(); ++i ) {
			drawManagers[i] = new DrawManager {};
			updateManagers[i] = new UpdateManager {};
			objects[i]->init(renderTarget, *drawManagers[i], *updateManagers[i], interactionManager, interactionStack, panelManager);
		}
	}


	void LayerWithChangeableObjects::setCurrent(uint index)
	{
		current = index;
	}

	IScalable *LayerWithChangeableObjects::getObject()
	{
		return objects[current];
	}

	uint LayerWithChangeableObjects::getIndex()
	{
		return current;
	}

	void LayerWithChangeableObjects::draw()
	{
		drawManagers[current]->draw();
	}

	void LayerWithChangeableObjects::resize(sf::Vector2f size, sf::Vector2f position)
	{
		Layer::resize( size, position );
		objects[current]->resize( size, position );
	}

	void LayerWithChangeableObjects::update()
	{
		updateManagers[current]->update();
	}

	bool LayerWithChangeableObjects::updateInteractions(sf::Vector2f mousePosition)
	{
		return objects[current]->updateInteractions(mousePosition);
	}

	LayerWithChangeableObjects *LayerWithChangeableObjects::copy()
	{
		return new LayerWithChangeableObjects{ objects, current, minimumSize};
	}

	void LayerWithChangeableObjects::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset)
	{
		objects[current]->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}

	LayerWithChangeableObjects *LayerWithChangeableObjects::createFromYaml(const YAML::Node &node)
	{
		std::vector<IScalable *> objects;
		uint current {0};
		sf::Vector2f minSize {0,0};

		for ( auto &object : node["objects"] ) {
			IScalable* newObject;
			object >> newObject;
			objects.push_back(newObject);
		}

		if (node["current"]) node["current"] >> current;

		if (node["minSize"]) node["minSize"] >> minSize;

		return new LayerWithChangeableObjects { objects, current, minSize };
	}
} // ui