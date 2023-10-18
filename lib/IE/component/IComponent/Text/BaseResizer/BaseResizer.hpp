#pragma once

#include "../BaseCharacter/BaseCharacter.hpp"
#include "ResizerInitInfo/ResizerInitInfo.hpp"

namespace ie {
	class BaseResizer {
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
			virtual BaseResizer* make(ResizerInitInfo resizer_init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		BaseResizer(float line_spacing, Align align, Algorithm algorithm, ResizerInitInfo init_info);
	
		BaseResizer(float line_spacing = 1.15, Align align = Align::Left, Algorithm algorithm = Algorithm::Base);
		
		void init(ResizerInitInfo init_info);
		
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
		
		virtual BaseResizer* copy() = 0;
		
		virtual ~BaseResizer() = default;
	
	protected:
		std::vector<BaseCharacter*>* characters;
		std::vector<BoxPtr<BaseLine> >* lines;
		
		const float line_spacing;
		const Align align;
		const Algorithm algorithm;
	};
	
	template<>
	struct Decode<BaseResizer::Align> {
		static bool decode(const YAML::Node& node, BaseResizer::Align& align);
	};
	
	template<>
	struct Decode<BaseResizer::Algorithm> {
		static bool decode(const YAML::Node& node, BaseResizer::Algorithm& align);
	};
}