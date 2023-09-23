#pragma once

#include "../BaseCharacter/BaseCharacter.hpp"
#include "InitInfo/ResizerInitInfo.hpp"

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
		
		struct Make{
			virtual BaseResizer* make(ResizerInitInfo resizerInitInfo);
		};
		
		BaseResizer(float lineSpacing, Align align, Algorithm algorithm, ResizerInitInfo initInfo);
	
		BaseResizer(float lineSpacing = 1.15, Align align = Align::Left, Algorithm algorithm = Algorithm::Base);
		
		void init(ResizerInitInfo initInfo);
		
		virtual void move(sf::Vector2f position) = 0;
		
		virtual void setPosition(sf::Vector2f position) = 0;
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual sf::Vector2f getPosition() = 0;
		
		virtual sf::Vector2f getSize() = 0;
	
	protected:
		virtual sf::Vector2f getMinSizeBase() = 0;
		
		virtual sf::Vector2f getMinSizeConsole() = 0;
		
		virtual sf::Vector2f getMinSizeAbsolute() = 0;
	
	public:
		virtual sf::Vector2f getMinSize();
		
		virtual sf::Vector2f getNormalSize() = 0;
		
		virtual BaseResizer* copy() = 0;
		
		virtual ~BaseResizer() = default;
	
	protected:
		std::vector<BaseCharacter*>* characters;
		std::vector<BoxPtr<BaseLine> >* lines;
		
		const float lineSpacing;
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