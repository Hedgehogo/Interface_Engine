#pragma once

#include "../OnlyDrawable.hpp"
#include "../../INonInteractiveLayout/INonInteractiveLayout.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Empty : public OnlyDrawable, public virtual INonInteractiveLayout {
	public:
		struct Make : public virtual INonInteractiveLayout::Make {
			auto make(InitInfo init_info) -> Empty* override;
		};
		
		Empty(Make&& make, InitInfo init_info);
		
		Empty();
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget&, int, int, size_t, size_t) -> void override;
	
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
	};
}

template<>
struct ieml::Decode<char, ie::Empty::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Empty::Make>;
};
