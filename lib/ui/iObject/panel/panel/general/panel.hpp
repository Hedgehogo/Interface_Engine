#pragma once
#include "../basePanel.hpp"
#include "../../manager/panelManager.hpp"
#include "../../../../drawable/manager/drawManager.hpp"

namespace ui {
	class HidePanelInteraction;
	class MovePanelInteraction;
	class Panel : public BasePanel {
	protected:
		PanelManager panelManager;
		InteractionManager* interactionManager;
		HidePanelInteraction* hideInteraction;
		MovePanelInteraction* moveInteraction;
		
		void copy(Panel* panel);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, MovePanelInteraction *moveInteraction, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed = false);
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed = false);
		
		~Panel() override;
		
		virtual void setDisplayed();
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		bool inConstPanels(sf::Vector2f pointPosition);
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active) override;
		
		Panel* copy() override;
		
		static Panel* createFromYaml(const YAML::Node &node);
	};
}
