#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/panel/IPanelManager/PanelManagerInterceptor/PanelManagerInterceptor.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"
#include "IE/component/IComponent/Text/TextStyle/TextStyle.hpp"

namespace ie {
	class BoxSettable : public Box, public virtual IScalableObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxSettable* override;
		};
		
		BoxSettable(Make&& make, InitInfo init_info);
		
		BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size, InitInfo init_info);
		
		auto set_object(BoxPtr<IScalable::Make>&& new_object) -> void;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update() -> void override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
	protected:
		DrawManager draw_manager_;
		UpdateManager update_manager_;
		sf::RenderWindow* window_;
		sf::RenderTarget* render_target_;
		DynBuffer* dyn_buffer_;
		absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer_;
		EventHandler* event_handler_;
		TriggerManager trigger_manager_;
		PanelManagerInterceptor panel_manager_interceptor_;
		BoxPtr<IScalable> object_;
	};
}