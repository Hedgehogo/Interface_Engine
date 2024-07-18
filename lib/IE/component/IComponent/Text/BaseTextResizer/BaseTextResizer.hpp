#pragma once

#include "../BaseCharacter/BaseCharacter.hpp"
#include "IE/component/IComponent/Text/BaseTextResizer/TextResizerInitInfo/TextResizerInitInfo.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

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
			virtual auto make(TextResizerInitInfo resizer_init_info) -> BaseTextResizer* = 0;
			
			virtual ~Make() = default;
		};
		
		BaseTextResizer(float line_spacing, Align align, Algorithm algorithm, TextResizerInitInfo init_info);
		
		virtual auto get_lines() const -> std::vector<BoxPtr<BaseLine> > const&;
		
		virtual auto move(sf::Vector2f offset) -> void = 0;
		
		virtual auto set_position(sf::Vector2f position) -> void = 0;
		
		virtual auto resize(sf::Vector2f size, sf::Vector2f position) -> void = 0;
		
		virtual auto get_position() -> sf::Vector2f = 0;
		
		virtual auto get_size() -> sf::Vector2f = 0;
	
	protected:
		virtual auto get_min_size_base() -> sf::Vector2f = 0;
		
		virtual auto get_min_size_console() -> sf::Vector2f = 0;
		
		virtual auto get_min_size_absolute() -> sf::Vector2f = 0;
	
	public:
		virtual auto get_min_size() -> sf::Vector2f;
		
		virtual auto get_normal_size() -> sf::Vector2f = 0;
		
		virtual ~BaseTextResizer() = default;
	
	protected:
		std::vector<BaseCharacter*>& characters_;
		std::vector<BoxPtr<BaseLine> > lines_;
		
		float const line_spacing_;
		Align const align_;
		Algorithm const algorithm_;
	};
}

template<>
struct ieml::Decode<char, ie::BaseTextResizer::Align> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BaseTextResizer::Align>;
};

template<>
struct ieml::Decode<char, ie::BaseTextResizer::Algorithm> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BaseTextResizer::Algorithm>;
};