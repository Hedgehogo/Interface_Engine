#pragma once

#include "../box.hpp"
#include "ui/iObject/iLayout/twoObjects/iLayoutWithTwoObjects.hpp"

namespace ui {
	class BoxWithConstCenter : public Box, public ILayoutWithTwoObjects {
	public:
		BoxWithConstCenter(BoxPtr<IScalable> constObject, BoxPtr<IScalable> background, const sf::Vector2f& constSize, const sf::Vector2f& minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithConstCenter* copy() override;
	
	protected:
		BoxPtr<IScalable> constObject;
		BoxPtr<IScalable> background;
		sf::Vector2f constSize;
	};
	
	template<>
	struct DecodePointer<BoxWithConstCenter> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstCenter*& boxWithConstCenter);
	};
}
