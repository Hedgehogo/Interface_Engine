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
			
			auto make(TextResizerInitInfo init_info) -> TextResizer* override;
		};
		
		TextResizer(Make&& make, TextResizerInitInfo init_info);
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_position(sf::Vector2f position) -> void override;
	
	protected:
		virtual auto print_character(std::vector<BaseCharacter*>::iterator character) -> void;
		
		virtual auto porting(std::vector<BaseCharacter*>::iterator end_character) -> void;
		
		virtual auto auto_porting(std::vector<BaseCharacter*>::iterator end_character) -> void;
		
		virtual auto equalize_characters(std::vector<BaseCharacter*>::iterator end_character, float line_size, float length_end_character) -> void;
		
		virtual auto equalize(std::vector<BaseCharacter*>::iterator end_character, float height_end_character) -> float;
		
		virtual auto delete_old_cash(sf::Vector2f size, sf::Vector2f position) -> void;
		
		virtual auto character_resize() -> void;
		
		virtual auto space_resize() -> void;
		
		virtual auto enter_resize() -> void;
		
		virtual auto object_resize(bool full) -> void;
		
		virtual auto end_line_equalize() -> void;
	
	public:
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_position() -> sf::Vector2f override;
		
		auto get_size() -> sf::Vector2f override;
	
	protected:
		auto get_min_size_base() -> sf::Vector2f override;
		
		auto get_min_size_console() -> sf::Vector2f override;
		
		auto get_min_size_absolute() -> sf::Vector2f override;
	
	public:
		auto get_normal_size() -> sf::Vector2f override;
	
	protected:
		std::vector<BaseCharacter*>::iterator after_enter_;
		std::vector<BaseCharacter*>::iterator after_space_;
		std::vector<BaseCharacter*>::iterator current_character_;
		
		sf::Vector2f next_position_;
		
		sf::Vector2f start_render_;
		sf::Vector2f end_render_;
	};
}

template<>
struct ieml::Decode<char, ie::TextResizer::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TextResizer::Make>;
};