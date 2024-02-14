#pragma once

#include "../BaseTextResizer.hpp"

namespace ie {
	class TextResizer : public BaseTextResizer {
	public:
		struct Make : BaseTextResizer::Make{
			float line_spacing = 1.15;
			Align align = Align::Left;
			Algorithm algorithm = Algorithm::Base;
			
			Make(float line_spacing = 1.15, Align align = Align::Left, Algorithm algorithm = Algorithm::Base);
			
			TextResizer* make(TextResizerInitInfo init_info) override;
		};
		
		TextResizer(Make&& make, TextResizerInitInfo init_info);
		
		void move(sf::Vector2f position) override;
		
		void set_position(sf::Vector2f position) override;
	
	protected:
		virtual void print_character(std::vector<BaseCharacter*>::iterator character);
		
		virtual void porting(std::vector<BaseCharacter*>::iterator end_character);
		
		virtual void auto_porting(std::vector<BaseCharacter*>::iterator end_character);
		
		virtual void equalize_characters(std::vector<BaseCharacter*>::iterator end_character, float line_size, float length_end_character);
		
		virtual float equalize(std::vector<BaseCharacter*>::iterator end_character, float height_end_character);
		
		virtual void delete_old_cash(sf::Vector2f size, sf::Vector2f position);
		
		virtual void character_resize();
		
		virtual void space_resize();
		
		virtual void enter_resize();
		
		virtual void object_resize(bool full);
		
		virtual void end_line_equalize();
	
	public:
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_position() override;
		
		sf::Vector2f get_size() override;
	
	protected:
		sf::Vector2f get_min_size_base() override;
		
		sf::Vector2f get_min_size_console() override;
		
		sf::Vector2f get_min_size_absolute() override;
	
	public:
		sf::Vector2f get_normal_size() override;
	
	protected:
		std::vector<BaseCharacter*>::iterator after_enter;
		std::vector<BaseCharacter*>::iterator after_space;
		std::vector<BaseCharacter*>::iterator current_character;
		
		sf::Vector2f next_position;
		
		sf::Vector2f start_render;
		sf::Vector2f end_render;
	};
}

template<>
struct ieml::Decode<char, ie::TextResizer::Make> {
	static orl::Option<ie::TextResizer::Make> decode(ieml::Node const& node);
};