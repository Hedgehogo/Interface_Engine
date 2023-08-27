#pragma once

#include "../Box.hpp"
#include "../../../../ILayout/ILayoutObject/ILayoutObject.hpp"
#include "../../../../ILayout/ILayoutBackground/ILayoutBackground.hpp"

namespace ie {
	class BoxBackground : public Box, public ILayoutBackground, public ILayoutObject {
	public:
	struct Make : public Box::Make, public ILayoutBackground::Make, public ILayoutObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> background;
			sf::Vector2f offset = {};
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset = {}, sf::Vector2f minSize = {});
			
			BoxBackground* make(InitInfo initInfo) override;
		};
		
		BoxBackground(Make&& make, InitInfo initInfo);
		
		BoxBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset = {}, sf::Vector2f minSize = {});
		
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
		
		BoxBackground* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		sf::Vector2f offset;
	};
	
	template<>
	struct DecodePointer<BoxBackground> {
		static bool decodePointer(const YAML::Node& node, BoxBackground*& boxWithBackground);
	};
}