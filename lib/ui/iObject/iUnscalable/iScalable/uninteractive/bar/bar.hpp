#pragma once
#include "../onlyDrawable/onlyDrawable.hpp"
#include "../onlyDrawable/empty/empty.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../../drawable/manager/drawManager.hpp"

namespace ui {
	class Bar : public OnlyDrawable, public LayoutWithBackground {
	protected:
		IUninteractive* strip;
		bool horizontal;
		float offset;
		int division;
		float value;
		
		void copy(Bar* bar);
		
	public:
		void init(InitInfo initInfo) override;
		
		explicit Bar(IUninteractive* background, IUninteractive* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(IUninteractive *background, IUninteractive *strip, int division, float offset = 0, bool horizontal = true);
		
		~Bar() override;
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Bar* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, Bar *&bar);
	
	template<>
	struct DecodePointer<Bar> {
		static bool decodePointer(const YAML::Node &node, Bar *&bar);
	};
}
