#pragma once

#include "../layer.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../panel/manager/general/panelManager.hpp"
#include "../../../../panel/manager/interceptor/panelManagerInterceptor.hpp"

namespace ui
{
	class LayerWithSetableObject : public IDrawable, public IUpdatable, public LayoutWithObject
	{
	protected:
		IScalable* object = nullptr;

		sf::Vector2f minSize;

		DrawManager drawManager;

		UpdateManager updateManager;

		sf::RenderTarget *renderTarget;

		InteractionManager interactionManager;

		InteractionStack *interactionStack;

		PanelManagerInterceptor panelManagerInterceptor;
	public:
		LayerWithSetableObject(sf::Vector2f minSize, IScalable* object);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		void setObject(IScalable* newObject, bool deleteOld);

		IScalable* getObject();

		void draw() override;

		void update() override;
	};
} // ui
