#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/panel/BasePanel/ConstPanel/ConstPanel.hpp"

namespace ie {
	class BoxPanel : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<ConstPanel::Make> panel;
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			BoxPanel* make(InitInfo init_info) override;
		};
		
		BoxPanel(Make&& make, InitInfo init_info);
		
		BoxPanel(BoxPtr<ConstPanel>&& panel, BoxPtr<IScalable>&& object, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		const ConstPanel& get_panel() const;
		
		BoxPanel* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<IScalable> object_;
		BoxPtr<ConstPanel> panel_;
	};
	
	template<>
	struct DecodePointer<BoxPanel> {
		static bool decode_pointer(const YAML::Node& node, BoxPanel*& box_with_panel);
	};
}