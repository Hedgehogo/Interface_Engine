#pragma once

#include "../Box.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"
#include "../../IUninteractive/OnlyDrawable/Empty/Empty.hpp"
#include "IE/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"
#include "IE/IComponent/IComponentLayout/IComponentBackground/IComponentBackground.hpp"
#include "IE/IComponent/IComponentLayout/IComponentTwoObjects/IComponentTwoObjects.hpp"
#include "../../IUninteractive/OnlyDrawable/Empty/Empty.hpp"

namespace ie {
	class BoxConstRatioCenter : public Box, public virtual IComponentObject, public virtual IComponentBackground, public virtual IComponentTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IComponentObject::Make, public virtual IComponentBackground::Make, public virtual IComponentTwoObjects::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IScalable::Make> firstObject;
			BoxPtr<IScalable::Make> secondObject;
			BoxPtr<IUninteractive::Make> background;
			float aspectRatio;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, float aspectRatio, sf::Vector2f minSize = {});
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IScalable::Make>&& firstObject,
				BoxPtr<IScalable::Make>&& secondObject,
				BoxPtr<IUninteractive::Make>&& background,
				float aspectRatio = 1.f,
				sf::Vector2f minSize = {}
			);
			
			BoxConstRatioCenter* make(InitInfo initInfo) override;
		};
		
		BoxConstRatioCenter(Make&& make, InitInfo initInfo);
		
		BoxConstRatioCenter(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, float aspectRatio, sf::Vector2f minSize = {});
		
		BoxConstRatioCenter(
			BoxPtr<IScalable>&& object,
			BoxPtr<IScalable>&& firstObject,
			BoxPtr<IScalable>&& secondObject,
			BoxPtr<IUninteractive>&& background,
			float aspectRatio,
			sf::Vector2f minSize = {}
		);
		
		BoxConstRatioCenter(const BoxConstRatioCenter& other);
		
		void init(InitInfo initInfo) override;
		
		void setAspectRatio(float aspectRatio);
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IUninteractive& getBackground() override;
		
		const IUninteractive& getBackground() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxConstRatioCenter* copy() override;
		
		void draw() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
		float aspectRatio;
		bool renderFirst;
		bool renderSecond;
	};
	
	template<>
	struct DecodePointer<BoxConstRatioCenter> {
		static bool decodePointer(const YAML::Node& node, BoxConstRatioCenter*& boxWithConstRatioCenter);
	};
}
