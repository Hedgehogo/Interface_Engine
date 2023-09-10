#pragma once

#include "../Box.hpp"
#include "../../../../Panel/BasePanel/ConstPanel/ConstPanel.hpp"
#include "IE/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class BoxPanel : public Box, public virtual IComponentObject {
	public:
		struct Make : public virtual Box::Make, public virtual IComponentObject::Make {
			BoxPtr<ConstPanel::Make> panel;
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxPanel* make(InitInfo initInfo) override;
		};
		
		BoxPanel(Make&& make, InitInfo initInfo);
		
		BoxPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		const ConstPanel& getPanel() const;
		
		BoxPanel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> object;
		BoxPtr<ConstPanel> panel;
	};
	
	template<>
	struct DecodePointer<BoxPanel> {
		static bool decodePointer(const YAML::Node& node, BoxPanel*& boxWithPanel);
	};
}
