#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"
#include "../OnlyDrawable/Empty/Empty.hpp"
#include "../INonInteractiveLayout/INonInteractiveBackground/INonInteractiveBackground.hpp"

namespace ie {
	class Bar : public virtual INonInteractiveBackground {
	public:
		struct Make : public virtual INonInteractiveBackground::Make {
			BoxPtr<INonInteractive::Make> background;
			BoxPtr<INonInteractive::Make> strip;
			float offset = 0;
			bool horizontal = true;
			int division = 0;
			
			Make(BoxPtr<INonInteractive::Make>&& background, BoxPtr<INonInteractive::Make>&& strip, float offset = 0, bool horizontal = true);
			
			Make(
				BoxPtr<INonInteractive::Make>&& background,
				BoxPtr<INonInteractive::Make>&& strip,
				int division,
				float offset = 0,
				bool horizontal = true
			);
			
			auto make(InitInfo init_info) -> Bar* override;
		};
		
		Bar(Make&& make, InitInfo init_info);
		
		auto get_value() -> float;
		
		auto set_value(float value) -> void;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_background() -> INonInteractive& override;
		
		auto get_background() const -> INonInteractive const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		BoxPtr<INonInteractive> background_;
		BoxPtr<INonInteractive> strip_;
		bool horizontal_;
		float offset_;
		int division_;
		float value_;
	};
}

template<>
struct ieml::Decode<char, ie::Bar::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Bar::Make>;
};
