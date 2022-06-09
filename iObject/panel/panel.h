#pragma once
#include "../../enums/enums.h"
#include "../iFlat/iFlat.h"

namespace ui {
	class HidePanelInteraction;
	class Panel : public IObject {
	protected:
		sf::Vector2f position;
		sf::Vector2f size;
		Size verticalSize;
		Size horizontalSize;
		IFlat *object;
		InteractionManager* interactionManager;
		HidePanelInteraction* interaction;
		bool displayed;
		bool active;
		bool parentProcessed;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &panelStack) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	
	public:
		Panel(IFlat *object, Size verticalSize, Size horizontalSize, sf::Vector2f size = sf::Vector2f{}, bool displayed = false);
		
		Panel(IFlat *object, sf::Vector2f size, bool displayed = false);
		
		~Panel() override;
		
		void setParentProcessed(bool parentProcessed);
		
		bool getParentProcessed();
		
		void hide();
		
		bool isActive();
		
		bool inPanel(sf::Vector2f position);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		virtual bool updateInteractions(bool active, sf::Vector2f mousePosition);
		
		sf::Vector2f getNormalSize() override;
		
		sf::Vector2f getMinSize() override;
	};
}
