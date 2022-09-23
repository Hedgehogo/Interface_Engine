#pragma once

#include "../../iUnscalable/iScalable/iScalable.hpp"
#include "../panel/basePanel.hpp"

namespace ui
{
	class IPanelManager : public IUpdatable, public IDrawable
	{
	public:
		virtual bool isFree() = 0;

		virtual bool inConstPanels(sf::Vector2f pointPosition) = 0;

		virtual void addPanel(BasePanel *panel) = 0;

		virtual void removePanel(BasePanel *panel) = 0;

		virtual void displayPanel(BasePanel *panel) = 0;

		virtual void hidePanel(BasePanel *panel) = 0;

		void draw() override = 0 ;

		void update() override = 0;

		virtual bool updateInteractions(sf::Vector2f mousePosition, bool active) = 0;
	};
} // ui
