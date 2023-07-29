#pragma once

#include "../onlyDrawable.hpp"
#include "ui/iObject/iLayout/iLayout.hpp"

namespace ui {
	class Empty : public OnlyDrawable, public ILayout {
	public:
		Empty();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		LayoutData& getLayoutData() override;
		
		const LayoutData& getLayoutData() const override;
		
		Empty* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
		
	protected:
		LayoutData layout;
	};
	
	template<>
	struct DecodePointer<Empty> {
		static bool decodePointer(const YAML::Node& node, Empty*& empty);
	};
}
