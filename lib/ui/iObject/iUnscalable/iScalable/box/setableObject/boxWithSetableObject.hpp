#pragma once

#include "../box.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../panel/manager/general/panelManager.hpp"
#include "../../../../panel/manager/interceptor/panelManagerInterceptor.hpp"

namespace ui {
	class BoxWithSetableObject : public IDrawable, public IUpdatable, public LayoutWithObject {
	public:
		BoxWithSetableObject(sf::Vector2f minSize, IScalable* object);
		
		void init(InitInfo initInfo) override;
		
		void setObject(IScalable* newObject, bool deleteOld);
		
		IScalable* getObject();
		
		void draw() override;
		
		void update() override;
	
	protected:
		IScalable* object = nullptr;
		sf::Vector2f minSize;
		DrawManager drawManager;
		UpdateManager updateManager;
		Window* window;
		sf::RenderTarget* renderTarget;
		InteractionManager interactionManager;
		InteractionStack* interactionStack;
		PanelManagerInterceptor panelManagerInterceptor;
	};
}
