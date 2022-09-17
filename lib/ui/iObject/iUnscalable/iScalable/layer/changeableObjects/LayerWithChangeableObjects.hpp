#pragma once

#include "../layer.hpp"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.hpp"

namespace ui
{

	class LayerWithChangeableObjects : public Layer, public LayoutWithObjectsArray, public IUpdatable, public IDrawable
	{
	protected:
		uint current;

		std::vector<DrawManager*> drawManagers;
		std::vector<UpdateManager*> updateManagers;

	public:
		LayerWithChangeableObjects(std::vector<IScalable*> objects, uint current = 0, sf::Vector2f minSize = { 0, 0});

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;

		void setCurrent(uint index);

		IScalable* getObject();

		uint getIndex();

		void draw() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		void update() override;

		bool updateInteractions(sf::Vector2f mousePosition) override;

		LayerWithChangeableObjects * copy() override;

		static LayerWithChangeableObjects* createFromYaml(const YAML::Node &node);

		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};

} // ui
