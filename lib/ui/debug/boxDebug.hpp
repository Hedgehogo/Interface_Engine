#pragma once

#include "../iObject/iUnscalable/iScalable/box/box.hpp"
#include "../iObject/iLayout/object/iLayoutWithObject.hpp"

namespace ui {
	class BoxDebug : public Box, public ILayoutWithObject, public IDrawable {
	protected:
		void init(InitInfo initInfo) override;
	
	public:
		BoxDebug(BoxPtr<IScalable>&& object);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxDebug* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> object;
		sf::RenderTarget* renderTarget;
		bool active;
		bool drawn;
	};
	
	template<>
	struct DecodePointer<BoxDebug> {
		static bool decodePointer(const YAML::Node& node, BoxDebug*& boxDebug);
	};
}
