#pragma once

#include "../box.hpp"
#include "../../../../panel/panel/const/constPanel.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui {
	class BoxWithPanel : public Box, public LayoutWithObject {
	protected:
		ConstPanel* panel;
	
	public:
		void init(InitInfo initInfo) override;
		
		BoxWithPanel(ConstPanel* panel, IScalable* object, sf::Vector2f minSize = {});
		
		~BoxWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		BoxWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithPanel> {
		static bool decodePointer(const YAML::Node& node, BoxWithPanel*& boxWithPanel);
	};
	
	using BoxWPanel = BoxWithPanel;
	using BWP = BoxWithPanel;
}
