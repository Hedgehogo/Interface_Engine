#pragma once

#include "ui/iObject/iUnscalable/iScalable/box/box.hpp"
#include "ui/iObject/iLayout/twoObjects/iLayoutWithTwoObjects.hpp"

namespace ui {
	class BoxSwitcher : public Box, public ILayoutWithTwoObjects, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutWithTwoObjects::Make {
			BoxPtr<IScalable::Make> firstObject;
			BoxPtr<IScalable::Make> secondObject;
			PSbool value;
			sf::Vector2f minSize = {};
			
			BoxSwitcher* make(InitInfo initInfo) override;
		};
		
		BoxSwitcher(Make&& make, InitInfo initInfo);
		
		BoxSwitcher(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, PSbool value, const sf::Vector2f& minSize = {});
		
		BoxSwitcher(const BoxSwitcher& other);
		
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
		
		BoxSwitcher* copy() override;
	
	protected:
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
		PSbool value;
	};
	
	template<>
	struct DecodePointer<BoxSwitcher> {
		static bool decodePointer(const YAML::Node& node, BoxSwitcher*& boxSwitcher);
	};
}
