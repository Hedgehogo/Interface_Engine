#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxBackground : public Box, public virtual IScalableBackground, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableBackground::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<INonInteractive::Make> background;
			sf::Vector2f offset = {};
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<INonInteractive::Make>&& background, sf::Vector2f offset = {}, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxBackground* override;
		};
		
		BoxBackground(Make&& make, InitInfo init_info);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_background() -> INonInteractive& override;
		
		auto get_background() const -> INonInteractive const& override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<INonInteractive> background_;
		BoxPtr<IScalable> object_;
		sf::Vector2f offset_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxBackground::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxBackground::Make>;
};
