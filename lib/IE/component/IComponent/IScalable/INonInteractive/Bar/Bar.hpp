#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"
#include "../OnlyDrawable/Empty/Empty.hpp"
#include "../INonInteractiveLayout/INonInteractiveBackground/INonInteractiveBackground.hpp"

namespace ie {
	class Bar : public OnlyDrawable, public virtual INonInteractiveBackground {
	public:
		struct Make : public virtual INonInteractiveBackground::Make {
			BoxPtr<INonInteractive::Make> background;
			BoxPtr<INonInteractive::Make> strip;
			float offset = 0;
			bool horizontal = true;
			int division = 0;
			
			Make(BoxPtr<INonInteractive::Make>&& background, BoxPtr<INonInteractive::Make>&& strip, float offset = 0, bool horizontal = true);
			
			Make(BoxPtr<INonInteractive::Make>&& background, BoxPtr<INonInteractive::Make>&& strip, int division, float offset = 0, bool horizontal = true);
			
			Bar* make(InitInfo init_info) override;
		};
		
		Bar(Make&& make, InitInfo init_info);
		
		float get_value();
		
		void set_value(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		INonInteractive& get_background() override;
		
		const INonInteractive& get_background() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
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
	static orl::Option<ie::Bar::Make> decode(ieml::Node const& node);
};
