#pragma once

#include "../../ILayout/ILayoutObject/ILayoutObject.hpp"
#include "../../../sizingAndPositioning/sizing/make/makeSize.hpp"
#include "../../../sizingAndPositioning/positioning/make/makePositioning.hpp"
#include "../../../sizingAndPositioning/sizing2/iSizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/general/sizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/constRatio/constRatioSizing2.hpp"
#include "../../../sizingAndPositioning/sizing2/lambda/lambdaSizing2.hpp"
#include "../../../sizingAndPositioning/positioning2/iPositioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/general/positioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/internal/internalPositioning2.hpp"
#include "../../../sizingAndPositioning/positioning2/lambda/lambdaPositioning2.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"

namespace ui {
	class BasePanel : public ILayoutObject, public IDrawable, public IUpdatable {
	public:
		struct Make : public ILayoutObject::Make {
			BasePanel* make(InitInfo initInfo) override = 0;
		};
		
		BasePanel(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed, InitInfo objectInitInfo, InitInfo initInfo);
		
		BasePanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed = false);
		
		BasePanel(const BasePanel& other);
		
		void init(InitInfo initInfo) override;
		
		virtual bool isIndependent() = 0;
		
		virtual bool isFree() = 0;
		
		virtual void setDisplayed();
		
		virtual void setParentProcessed(bool parentProcessed);
		
		virtual bool getParentProcessed();
		
		virtual bool inPanel(sf::Vector2f pointPosition);
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition, bool active);
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BasePanel* copy() override = 0;
		
		static void setFullDebug(bool fullDebug);
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		DrawManager drawManager;
		UpdateManager updateManager;
		BoxPtr<IScalable> object;
		BoxPtr<ISizing2> sizing;
		BoxPtr<IPositioning2> positioning;
		bool parentProcessed;
		bool oldDisplayed;
		bool displayed;
		bool active;
		
		static bool fullDebug;
	};
}
