#pragma once

#include "../box.hpp"
#include "../../../../panel/panel/const/constPanel.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"

namespace ui {
	class BoxWithPanel : public Box, public ILayoutWithObject {
	public:
		struct Make : public Box::Make, public ILayoutWithObject::Make {
			BoxPtr<ConstPanel::Make> panel;
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxWithPanel* make(InitInfo initInfo) override;
		};
		
		BoxWithPanel(Make&& make, InitInfo initInfo);
		
		BoxWithPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> object;
		BoxPtr<ConstPanel> panel;
	};
	
	template<>
	struct DecodePointer<BoxWithPanel> {
		static bool decodePointer(const YAML::Node& node, BoxWithPanel*& boxWithPanel);
	};
	
	using BoxWPanel = BoxWithPanel;
	using BWP = BoxWithPanel;
}
