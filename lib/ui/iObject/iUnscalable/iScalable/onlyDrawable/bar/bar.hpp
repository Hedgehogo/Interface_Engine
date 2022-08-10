#pragma once
#include "../onlyDrawable.hpp"
#include "../empty/empty.hpp"
#include "../../../../layout/background/layoutWithBackground.h"
#include "../../../../../drawable/manager/drawManager.h"

namespace ui {
	class Bar : public OnlyDrawable, public LayoutWithBackground {
	protected:
		OnlyDrawable* strip;
		bool horizontal;
		float offset;
		int division;
		float value;
		
		void copy(Bar* bar);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit Bar(OnlyDrawable* background, OnlyDrawable* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(OnlyDrawable *background, OnlyDrawable *strip, int division, float offset = 0, bool horizontal = true);
		
		~Bar() override;
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Bar* copy() override;
		
		static Bar* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
