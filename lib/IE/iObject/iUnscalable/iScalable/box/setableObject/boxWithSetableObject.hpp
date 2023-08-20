#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../panel/manager/general/panelManager.hpp"
#include "../../../../panel/manager/interceptor/panelManagerInterceptor.hpp"

namespace ui {
	class BoxWithSetableObject : public Box, public ILayoutWithObject, public IDrawable, public IUpdatable {
	public:
		struct Make : public Box::Make, public ILayoutWithObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxWithSetableObject* make(InitInfo initInfo) override;
		};
		
		BoxWithSetableObject(Make&& make, InitInfo initInfo);
		
		BoxWithSetableObject(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize, InitInfo initInfo);
		
		BoxWithSetableObject(BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setObject(BoxPtr<IScalable>&& newObject);
		
		void setObject(BoxPtr<IScalable::Make>&& newObject);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxWithSetableObject* copy() override;
	
	protected:
		DrawManager drawManager;
		UpdateManager updateManager;
		sf::RenderWindow* window;
		sf::RenderTarget* renderTarget;
		InteractionManager interactionManager;
		InteractionStack* interactionStack;
		PanelManagerInterceptor panelManagerInterceptor;
		BoxPtr<IScalable> object;
	};
}
