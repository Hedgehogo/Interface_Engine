#pragma once

#include "../onlyDrawable/onlyDrawable.hpp"
#include "../onlyDrawable/empty/empty.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../../drawable/manager/drawManager.hpp"

namespace ui {
	class Bar : public OnlyDrawable, public LayoutWithBackground {
	protected:
		void copy(Bar* bar);
	
	public:
		void init(InitInfo initInfo) override;
		
		explicit Bar(IUninteractive* background, IUninteractive* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(IUninteractive* background, IUninteractive* strip, int division, float offset = 0, bool horizontal = true);
		
		~Bar() override;
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		Bar* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		IUninteractive* strip;
		bool horizontal;
		float offset;
		int division;
		float value;
	};
	
	template<>
	struct DecodePointer<Bar> {
		static bool decodePointer(const YAML::Node& node, Bar*& bar);
	};
}
