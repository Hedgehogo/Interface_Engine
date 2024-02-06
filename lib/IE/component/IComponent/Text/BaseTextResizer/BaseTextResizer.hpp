#pragma once

#include "../BaseCharacter/BaseCharacter.hpp"
#include "IE/component/IComponent/Text/BaseTextResizer/TextResizerInitInfo/TextResizerInitInfo.hpp"

namespace ie {
	class BaseTextResizer {
	public:
		enum class Align {
			Left,
			Right,
			Center
		};
		
		enum class Algorithm {
			Base,
			Console,
			Absolute
		};
		
		struct Make {
			virtual BaseTextResizer* make(TextResizerInitInfo resizer_init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseTextResizer(float line_spacing, Align align, Algorithm algorithm, TextResizerInitInfo init_info);
		
		virtual const std::vector<BoxPtr<BaseLine> >& get_lines() const;
		
		virtual void move(sf::Vector2f position) = 0;
		
		virtual void set_position(sf::Vector2f position) = 0;
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual sf::Vector2f get_position() = 0;
		
		virtual sf::Vector2f get_size() = 0;
	
	protected:
		virtual sf::Vector2f get_min_size_base() = 0;
		
		virtual sf::Vector2f get_min_size_console() = 0;
		
		virtual sf::Vector2f get_min_size_absolute() = 0;
	
	public:
		virtual sf::Vector2f get_min_size();
		
		virtual sf::Vector2f get_normal_size() = 0;
		
		virtual ~BaseTextResizer() = default;
	
	protected:
		std::vector<BaseCharacter*>& characters;
		std::vector<BoxPtr<BaseLine> > lines;
		
		const float line_spacing;
		const Align align;
		const Algorithm algorithm;
	};
}

template<>
struct ieml::Decode<char, ie::BaseTextResizer::Align> {
	static orl::Option<ie::BaseTextResizer::Align> decode(ieml::Node const& node);
};

template<>
struct ieml::Decode<char, ie::BaseTextResizer::Algorithm> {
	static orl::Option<ie::BaseTextResizer::Algorithm> decode(ieml::Node const& node);
};