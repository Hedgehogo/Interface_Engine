#pragma once
#include "../onlyDrawable.hpp"
#include "../../../../layout/layout.h"

namespace ui {
	class Empty : public OnlyDrawable, public Layout {
	public:
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Empty* copy() override;
		
		static Empty* createFromYaml(const YAML::Node &node);
		
		virtual void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
}
