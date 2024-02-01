#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/panel/IPanelManager/PanelManagerInterceptor/PanelManagerInterceptor.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxSettable : public Box, public virtual IScalableObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			BoxSettable* make(InitInfo init_info) override;
		};
		
		BoxSettable(Make&& make, InitInfo init_info);
		
		BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size, InitInfo init_info);
		
		void set_object(BoxPtr<IScalable::Make>&& new_object);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
	protected:
		DrawManager draw_manager_;
		UpdateManager update_manager_;
		sf::RenderWindow* window_;
		sf::RenderTarget* render_target_;
		DynBuffer* dyn_buffer_;
		InteractionManager interaction_manager_;
		InteractionStack* interaction_stack_;
		PanelManagerInterceptor panel_manager_interceptor_;
		BoxPtr<IScalable> object_;
	};
}