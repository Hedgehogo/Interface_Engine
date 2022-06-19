#pragma once
#include "../../enums/enums.h"
#include "../iFlat/iFlat.h"

namespace ui {
	class HidePanelInteraction;
	class Panel : public IObject {
	protected:
		sf::Vector2f position;
		sf::Vector2f offset;
		sf::Vector2f size;
		Size verticalSize;
		Size horizontalSize;
		IFlat *object;
		InteractionManager* interactionManager;
		HidePanelInteraction* interaction;
		Corner parentCorner;
		Corner panelCorner;
		bool parentProcessed;
		bool oldDisplayed;
		bool displayed;
		bool active;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &panelManager) override;
		
		static sf::Vector2f cornerToPositionOffset(Corner corner, sf::Vector2f size);
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void copy(Panel* panel);
	
	public:
		Panel(IFlat *object, HidePanelInteraction *interaction, Corner parentCorner, Corner panelCorner, sf::Vector2f offset, Size verticalSize, Size horizontalSize, sf::Vector2f size = sf::Vector2f{}, bool displayed = false);
		
		Panel(IFlat *object, HidePanelInteraction *interaction, sf::Vector2f size, Corner parentCorner = Corner::DownLeft, Corner panelCorner = Corner::UpLeft, sf::Vector2f offset = sf::Vector2f{}, bool displayed = false);
		
		~Panel() override;
		
		void setParentProcessed(bool parentProcessed);
		
		bool getParentProcessed();
		
		bool isActive();
		
		bool inPanel(sf::Vector2f position);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		virtual bool updateInteractions(bool active, sf::Vector2f mousePosition);
		
		sf::Vector2f getNormalSize() override;
		
		sf::Vector2f getMinSize() override;
		
		Panel* copy() override;
	};
}
