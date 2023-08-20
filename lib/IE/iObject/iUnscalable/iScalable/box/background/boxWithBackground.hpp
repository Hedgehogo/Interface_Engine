#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../iLayout/background/iLayoutWithBackground.hpp"

namespace ui {
	class BoxWithBackground : public Box, public ILayoutWithBackground, public ILayoutWithObject {
	public:
	struct Make : public Box::Make, public ILayoutWithBackground::Make, public ILayoutWithObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> background;
			sf::Vector2f offset = {};
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset = {}, sf::Vector2f minSize = {});
			
			BoxWithBackground* make(InitInfo initInfo) override;
		};
		
		BoxWithBackground(Make&& make, InitInfo initInfo);
		
		BoxWithBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset = {}, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IUninteractive& getBackground() override;
		
		const IUninteractive& getBackground() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithBackground* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		sf::Vector2f offset;
	};
	
	template<>
	struct DecodePointer<BoxWithBackground> {
		static bool decodePointer(const YAML::Node& node, BoxWithBackground*& boxWithBackground);
	};
}