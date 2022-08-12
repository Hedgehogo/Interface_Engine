#pragma once
#include "../../layout/object/layoutWithObject.h"
#include "../../iUnscalable/iScalable/iScalable.hpp"
#include "../../../sizingAndPositioning/sizing2/baseSizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/general/sizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/constRatio/constRatioSizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/lambda/lambdaSizing2.hpp"
#include "../../../sizingAndPositioning/positioning2/basePositioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/general/positioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/internal/internalPositioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/lambda/lambdaPositioning2.hpp"
#include "../../../enums/enums.hpp"

namespace ui {
	class BasePanel : public LayoutWithObject, public IDrawable, public IUpdatable {
	protected:
		BaseSizing2* sizing;
		BasePositioning2* positioning;
		DrawManager drawManager;
		UpdateManager updateManager;
		bool parentProcessed;
		bool oldDisplayed;
		bool displayed;
		bool active;
		
		void copy(BasePanel* panel);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		BasePanel(IScalable *object, BaseSizing2* sizing, BasePositioning2* positioning, bool displayed = false);
		
		~BasePanel() override;
		
		virtual bool isIndependent() = 0;
		
		virtual bool isFree() = 0;
		
		virtual void setDisplayed();
		
		void setParentProcessed(bool parentProcessed);
		
		bool getParentProcessed();
		
		bool inPanel(sf::Vector2f pointPosition);
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition, bool active);
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		BasePanel* copy() override = 0;
		
	private:
		static bool fullDebug;
		
	public:
		static void setFullDebug(bool fullDebug);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
