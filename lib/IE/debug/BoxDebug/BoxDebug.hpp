#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/component/IComponent/IScalable/Box/Box.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class BoxDebug : public Box, public virtual IComponentObject, public virtual IDrawable {
	public:
		struct Make : public Box::Make, public virtual IComponentObject::Make {
			BoxPtr<IScalable::Make> object;
			
			Make(BoxPtr<IScalable::Make>&& object);
			
			auto make(InitInfo init_info) -> BoxDebug* override;
		};
		
		BoxDebug(Make&& make, InitInfo init_info);
		
		BoxDebug(BoxPtr<IScalable>&& object);
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<IScalable> object_;
		sf::RenderTarget* render_target_;
		bool active_;
		bool drawn_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxDebug> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxDebug>;
};
