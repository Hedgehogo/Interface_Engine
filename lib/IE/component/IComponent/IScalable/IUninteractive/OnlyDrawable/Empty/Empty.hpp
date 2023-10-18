#pragma once

#include "../OnlyDrawable.hpp"
#include "../../IUninteractiveLayout/IUninteractiveLayout.hpp"

namespace ie {
	class Empty : public OnlyDrawable, public virtual IUninteractiveLayout {
	public:
		struct Make : public virtual IUninteractiveLayout::Make {
			Empty* make(InitInfo init_info) override;
		};
		
		Empty(Make&& make, InitInfo init_info);
		
		Empty();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		Empty* copy() override;
		
		void draw_debug(sf::RenderTarget&, int, int, uint, uint) override;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout;
	};
	
	template<>
	struct DecodePointer<Empty> {
		static bool decode_pointer(const YAML::Node&, Empty*& empty);
	};
}
