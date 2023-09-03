#pragma once

#include "IE/IComponent/IUnscalable/IScalable/Box/Box.hpp"
#include "IE/IComponent/ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"

namespace ie {
	class BoxSwitch : public Box, public virtual ILayoutTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual ILayoutTwoObjects::Make {
			BoxPtr<IScalable::Make> inactiveObject;
			BoxPtr<IScalable::Make> activeObject;
			PSbool value;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& inactiveObject, BoxPtr<IScalable::Make>&& activeObject, PSbool value, const sf::Vector2f& minSize = {});
			
			BoxSwitch* make(InitInfo initInfo) override;
		};
		
		BoxSwitch(Make&& make, InitInfo initInfo);
		
		BoxSwitch(BoxPtr<IScalable>&& inactiveObject, BoxPtr<IScalable>&& activeObject, PSbool value, const sf::Vector2f& minSize = {});
		
		BoxSwitch(const BoxSwitch& other);
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxSwitch* copy() override;
	
	protected:
		DrawManager inactiveDrawManager;
		DrawManager activeDrawManager;
		BoxPtr<IScalable> inactiveObject;
		BoxPtr<IScalable> activeObject;
		PSbool value;
	};
	
	template<>
	struct DecodePointer<BoxSwitch> {
		static bool decodePointer(const YAML::Node& node, BoxSwitch*& boxSwitcher);
	};
}
