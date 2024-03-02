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
		
		static sf::String make(BasicCaption<sf::String>& caption, Make&& make, InitInfo init_info);
		
		static sf::String get(sf::String const& object);
		
		static void set(sf::String& first, sf::String const& second);
	};
	
	template<>
	struct CaptionString<SReader<ISString> > {
		using Make = MakeDyn<ISString>;
		
		static SReader<ISString> make(BasicCaption<SReader<ISString> >& caption, Make&& make, InitInfo init_info);
		
		static sf::String get(SReader<ISString> const& object);
		
		static void set(SReader<ISString>& first, sf::String const& second);
	};
	
	namespace make_system {
		template<typename StringStorage_>
		struct BasicCaption : public ie::INonInteractive::Make {
		public:
			typename CaptionString<StringStorage_>::Make text;
			BoxPtr<ie::INonInteractive::Make> background;
			sf::Font& font;
			int font_size = default_size_;
			sf::Color color = default_color_;
			sf::Text::Style style = {};
			InternalPositioning2::Make positioning = {{0, 0}};
			bool cut_back = true;
			sf::Vector2f min_size = {};
			
			static void set_default_color(sf::Color color = sf::Color::White);
			
			static void set_default_size(int size);
			
			static sf::Color get_default_color();
			
			static int get_default_size();
			
			BasicCaption(
				typename CaptionString<StringStorage_>::Make text,
				BoxPtr<INonInteractive::Make>&& background,
				sf::Font& font
			);
			
			BasicCaption set_font_size(int font_size)&&;
			
			BasicCaption set_color(sf::Color color)&&;
			
			BasicCaption set_style(sf::Text::Style style)&&;
			
			BasicCaption set_positioning(InternalPositioning2::Make positioning)&&;
			
			BasicCaption set_cut_back(bool cut_back)&&;
			
			BasicCaption set_min_size(sf::Vector2f min_size)&&;
			
			ie::BasicCaption<StringStorage_>* make(InitInfo init_info) override;
			
		protected:
			static sf::Color default_color_;
			static int default_size_;
		};
	}
	
	template<typename StringStorage_>
	class BasicCaption : public OnlyDrawable {
	public:
		using Make = make_system::BasicCaption<StringStorage_>;
		
		BasicCaption(Make&& make, InitInfo init_info);
		
		void set_string(sf::String str);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		static sf::Vector2f get_text_size(sf::Text const& text);
		
		void text_resize(sf::Vector2f size, sf::Vector2f position);
		
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
	static orl::Option<ie::make_system::BasicCaption<StringStorage_> > decode(ieml::Node const& node);
};

#include "Caption.inl"
