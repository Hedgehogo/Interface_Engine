#pragma once

#include "../onlyDrawable.hpp"
#include "../../../../../layout/layout.hpp"

namespace ui {
	class Empty : public OnlyDrawable, public Layout {
	public:
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		Empty* copy() override;
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
	
	
	template<>
	struct DecodePointer<Empty> {
		static bool decodePointer(const YAML::Node& node, Empty*& empty);
	};
}
