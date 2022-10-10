#pragma once

#include "../layer.hpp"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.hpp"

namespace ui
{

	class LayerWithChangeableObjects : public Layer, public LayoutWithObjectsArray, public IDrawable
	{
	protected:
		std::shared_ptr<WithValue<uint>> value;
		std::vector<IScalable *> objects;

		std::vector<DrawManager> drawManagers;
	public:
		LayerWithChangeableObjects(std::vector<IScalable*> objects, std::shared_ptr<WithValue<uint>> value, sf::Vector2f minSize = { 0, 0});

		LayerWithChangeableObjects(std::vector<IScalable*> objects, uint index = 0, sf::Vector2f minSize = { 0, 0});

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		void setValue(std::shared_ptr<WithValue<uint>> index);

		std::shared_ptr<WithValue<uint>> getValue();

		void setIndex(uint index);

		uint getIndex();

		IScalable* getObject();

		void draw() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		bool updateInteractions(sf::Vector2f mousePosition) override;

		LayerWithChangeableObjects * copy() override;

		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithChangeableObjects *&layerWithChangeableObjects);

} // ui
