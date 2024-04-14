#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../INonInteractive/OnlyDrawable/Empty/Empty.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstRatioCenter : public Box, public virtual IScalableObject, public virtual IScalableBackground, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make, public virtual IScalableBackground::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IScalable::Make> first_object;
			BoxPtr<IScalable::Make> second_object;
			BoxPtr<INonInteractive::Make> background;
			float aspect_ratio;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<INonInteractive::Make>&& background, float aspect_ratio, sf::Vector2f min_size = {});
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				BoxPtr<INonInteractive::Make>&& background,
				float aspect_ratio = 1.f,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> BoxConstRatioCenter* override;
		};
		
		BoxConstRatioCenter(Make&& make, InitInfo init_info);
		
		auto set_aspect_ratio(float aspect_ratio) -> void;
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_background() -> INonInteractive& override;
		
		auto get_background() const -> INonInteractive const& override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto draw() -> void override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		DrawManager first_draw_manager_;
		DrawManager second_draw_manager_;
		BoxPtr<INonInteractive> background_;
		BoxPtr<IScalable> object_;
		BoxPtr<IScalable> first_object_;
		BoxPtr<IScalable> second_object_;
		float aspect_ratio_;
		bool render_first_;
		bool render_second_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstRatioCenter::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxConstRatioCenter::Make>;
};
