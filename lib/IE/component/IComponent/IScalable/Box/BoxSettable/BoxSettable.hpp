#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/panel/IPanelManager/PanelManagerInterceptor/PanelManagerInterceptor.hpp"

namespace ie {
	class BoxSettable : public Box, public virtual IScalableObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
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