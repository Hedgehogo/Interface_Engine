#pragma once

#include "IE/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"
#include "IE/SizingAndPositioning/IPositioning/Functions/makePositioning/makePositioning.hpp"
#include "IE/SizingAndPositioning/ISizing/Functions/makeSize/makeSize.hpp"
#include "IE/SizingAndPositioning/ISizing2/ISizing2.hpp"
#include "IE/SizingAndPositioning/ISizing2/Sizing2/Sizing2.hpp"
#include "IE/SizingAndPositioning/ISizing2/ConstRatioSizing2/ConstRatioSizing2.hpp"
#include "IE/SizingAndPositioning/ISizing2/FnSizing2/FnSizing2.hpp"
#include "IE/SizingAndPositioning/IPositioning2/IPositioning2.hpp"
#include "IE/SizingAndPositioning/IPositioning2/Positioning2/Positioning2.hpp"
#include "IE/SizingAndPositioning/IPositioning2/InternalPositioning2/InternalPositioning2.hpp"
#include "IE/SizingAndPositioning/IPositioning2/FnPositioning2/FnPositioning2.hpp"
#include "IE/Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class BasePanel : public virtual IComponentObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual IComponentObject::Make {
			BasePanel* make(InitInfo initInfo) override = 0;
		};
		
		BasePanel(
			BoxPtr<IScalable::Make>&& object,
			BoxPtr<ISizing2::Make> sizing,
			BoxPtr<IPositioning2::Make> positioning,
			bool displayed,
			InitInfo objectInitInfo,
			InitInfo initInfo
		);
		
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
