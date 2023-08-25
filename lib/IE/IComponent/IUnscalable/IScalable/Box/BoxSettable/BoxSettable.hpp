#pragma once

#include "../Box.hpp"
#include "../../../../ILayout/ILayoutObject/ILayoutObject.hpp"
#include "../../../../Panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "../../../../Panel/IPanelManager/PanelManagerInterceptor/PanelManagerInterceptor.hpp"

namespace ui {
	class BoxSettable : public Box, public ILayoutObject, public IDrawable, public IUpdatable {
	public:
		struct Make : public Box::Make, public ILayoutObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxSettable* make(InitInfo initInfo) override;
		};
		
		BoxSettable(Make&& make, InitInfo initInfo);
		
		BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize, InitInfo initInfo);
		
		BoxSettable(BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setObject(BoxPtr<IScalable>&& newObject);
		
		void setObject(BoxPtr<IScalable::Make>&& newObject);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxSettable* copy() override;
	
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