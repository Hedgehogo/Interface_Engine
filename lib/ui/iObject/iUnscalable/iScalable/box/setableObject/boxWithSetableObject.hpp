#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../panel/manager/general/panelManager.hpp"
#include "../../../../panel/manager/interceptor/panelManagerInterceptor.hpp"

namespace ui {
	class BoxWithSetableObject : public Box, public ILayoutWithObject, public IDrawable, public IUpdatable {
	public:
		BoxWithSetableObject(BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setObject(BoxPtr<IScalable>&& newObject, bool);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
	
	protected:
		BoxPtr<IScalable> object;
		sf::Vector2f minSize;
		DrawManager drawManager;
		UpdateManager updateManager;
		sf::RenderWindow* window;
		sf::RenderTarget* renderTarget;
		InteractionManager interactionManager;
		InteractionStack* interactionStack;
		PanelManagerInterceptor panelManagerInterceptor;
	};
}
