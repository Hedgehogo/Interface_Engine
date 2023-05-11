#pragma once

#include "../iObject/iUnscalable/iScalable/box/box.hpp"

namespace ui {
	class BoxDebug : public Box, public IDrawable {
	protected:
		IScalable* object;
		sf::RenderTarget* renderTarget;
		bool active;
		bool drawn;
		
		void init(InitInfo initInfo) override;
	
	public:
		BoxDebug(IScalable* object);
		
		~BoxDebug() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		BoxDebug* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxDebug> {
		static bool decodePointer(const YAML::Node& node, BoxDebug*& boxDebug);
	};
}
