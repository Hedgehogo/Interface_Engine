#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/sizing-positioning/IPositioning2/InternalPositioning2/InternalPositioning2.hpp"
#include "../OnlyDrawable/OnlyDrawable.hpp"

namespace ie {
	template<typename StringStorage_>
	class BasicCaption;
	
	template<typename StringStorage_>
	struct CaptionString {
	};
	
	template<>
	struct CaptionString<sf::String> {
		using Make = sf::String;
		
		static auto make(BasicCaption<sf::String>& caption, Make&& make, InitInfo init_info) -> sf::String;
		
		static auto get(sf::String const& object) -> sf::String;
		
		static auto set(sf::String& first, sf::String const& second) -> void;
	};
	
	template<>
	struct CaptionString<SReader<ISString> > {
		using Make = MakeDyn<ISString>;
		
		static auto make(BasicCaption<SReader<ISString> >& caption, Make&& make, InitInfo init_info) -> SReader<ISString>;
		
		static auto get(SReader<ISString> const& object) -> sf::String;
		
		static auto set(SReader<ISString>& first, sf::String const& second) -> void;
	};
	
	namespace make_system {
		template<typename StringStorage_>
		struct BasicCaption : public ie::INonInteractive::Make {
		public:
			typename CaptionString<StringStorage_>::Make text;
			BoxPtr<ie::INonInteractive::Make> background;
			sf::Font& font;
			int font_size;
			sf::Color color;
			sf::Text::Style style = {};
			InternalPositioning2::Make positioning = {{0, 0}};
			bool cut_back = true;
			sf::Vector2f min_size = {};
			
			BasicCaption(
				typename CaptionString<StringStorage_>::Make text,
				BoxPtr<INonInteractive::Make>&& background,
				sf::Font& font
			);
			
			auto set_font_size(int font_size)&& -> BasicCaption;
			
			auto set_color(sf::Color color)&& -> BasicCaption;
			
			auto set_style(sf::Text::Style style)&& -> BasicCaption;
			
			auto set_positioning(InternalPositioning2::Make positioning)&& -> BasicCaption;
			
			auto set_cut_back(bool cut_back)&& -> BasicCaption;
			
			auto set_min_size(sf::Vector2f min_size)&& -> BasicCaption;
			
			auto make(InitInfo init_info) -> ie::BasicCaption<StringStorage_>* override;
		};
	}
	
	template<typename StringStorage_>
	class BasicCaption : public OnlyDrawable {
	public:
		using Make = make_system::BasicCaption<StringStorage_>;
		
		static auto set_default_color(sf::Color color = sf::Color::White) -> void;
		
		static auto set_default_size(int size) -> void;
		
		static auto get_default_color() -> sf::Color;
		
		static auto get_default_size() -> int;
		
		BasicCaption(Make&& make, InitInfo init_info);
		
		auto set_string(sf::String str) -> void;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		static auto get_text_size(sf::Text const& text) -> sf::Vector2f;
		
		auto text_resize(sf::Vector2f size, sf::Vector2f position) -> void;
		
		static sf::Color default_color_;
		static int default_size_;
		
		bool cut_back_;
		
		sf::Text text_;
		StringStorage_ str_;
		DrawManager draw_manager_;
		BoxPtr<INonInteractive> background_;
		sf::Vector2f minimum_size_;
		InternalPositioning2 positioning_;
	};
	
	using Caption = BasicCaption<sf::String>;
	using EditCaption = BasicCaption<SReader<ISString> >;
}

template<typename StringStorage_>
struct ieml::Decode<char, ie::make_system::BasicCaption<StringStorage_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicCaption<StringStorage_> >;
};

#include "Caption.inl"
