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
	class BasePanel : public virtual ILayoutObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make {
			virtual ~Make() = default;
			
			virtual BasePanel* make(InitInfo initInfo) = 0;
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
		
		virtual ~BasePanel() = default;
		
		virtual void init(InitInfo initInfo);
		
		virtual bool isIndependent() = 0;
		
		virtual bool isFree() = 0;
		
		virtual void setDisplayed();
		
		virtual void setParentProcessed(bool parentProcessed);
		
		virtual bool getParentProcessed();
		
		virtual bool inPanel(sf::Vector2f pointPosition);
		
		bool inArea(sf::Vector2f pointPosition);
		
		bool in(sf::Vector2f pointPosition);
		
		void draw() override;
		
		void setPosition(sf::Vector2f position);
		
		void move(sf::Vector2f offset);
		
		void resize(sf::Vector2f parentSize, sf::Vector2f parentPosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition);
		
		virtual bool updateInteractions(sf::Vector2f mousePosition, bool active);
		
		sf::Vector2f getAreaPosition() const;
		
		sf::Vector2f getAreaSize() const;
		
		sf::Vector2f getMinSize() const;
		
		sf::Vector2f getNormalSize() const;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		virtual BasePanel* copy() = 0;
		
		static void setFullDebug(bool fullDebug);
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	
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
