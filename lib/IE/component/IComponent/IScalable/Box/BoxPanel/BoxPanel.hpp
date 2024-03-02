#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/panel/BasePanel/ConstPanel/ConstPanel.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxPanel : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<ConstPanel::Make> panel;
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<ConstPanel::Make>&& panel, BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxPanel* override;
		};
		
		BoxPanel(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto get_panel() const -> ConstPanel const&;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<IScalable> object_;
		BoxPtr<ConstPanel> panel_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxPanel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxPanel::Make>;
};
