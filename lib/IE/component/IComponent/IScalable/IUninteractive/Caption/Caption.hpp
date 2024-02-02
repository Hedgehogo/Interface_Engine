#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../OnlyDrawable/OnlyDrawable.hpp"
#include "IE/sizing-positioning/IPositioning2/InternalPositioning2/InternalPositioning2.hpp"

namespace ie {
	class Caption : public OnlyDrawable {
	public:
		static void set_default_color(sf::Color color = sf::Color::White);
		
		static void set_default_size(int size);
		
		static sf::Color get_default_color();
		
		static int get_default_size();
		
		struct Make : public IUninteractive::Make {
			sf::String text;
			BoxPtr<IUninteractive::Make> background;
			sf::Font& font;
			int font_size = default_size_;
			sf::Color color = default_color_;
			sf::Text::Style style = {};
			float rotation = 0;
			InternalPositioning2::Make positioning = {{0, 0}};
			bool cut_back = true;
			sf::Vector2f min_size = {};
			
			Make(
				sf::String text,
				BoxPtr<IUninteractive::Make>&& background,
				sf::Font& font,
				sf::Vector2f min_size,
				int font_size = default_size_,
				sf::Color color = default_color_,
				sf::Text::Style style = {},
				float rotation = 0,
				InternalPositioning2::Make positioning = {{0, 0}},
				bool cut_back = true
			);
			
			Make(
				sf::String text,
				BoxPtr<IUninteractive::Make>&& background,
				sf::Font& font,
				int font_size = default_size_,
				sf::Color color = default_color_,
				sf::Text::Style style = {},
				float rotation = 0,
				InternalPositioning2::Make positioning = {{0, 0}},
				bool cut_back = true
			);
			
			Caption* make(InitInfo init_info) override;
		};
		
		Caption(Make&& make, InitInfo init_info);
		
		void draw() override;
		
		sf::FloatRect get_bounds(const sf::Text& text) const;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		static sf::Color default_color_;
		static int default_size_;
		
		bool cut_back_;
		
		sf::Text text_;
		sf::String str_;
		DrawManager draw_manager_;
		BoxPtr<IUninteractive> background_;
		sf::Vector2f minimum_size_;
		InternalPositioning2 positioning_;
	};
}

template<>
struct ieml::Decode<char, ie::Caption::Make> {
	static orl::Option<ie::Caption::Make> decode(ieml::Node const& node);
};
