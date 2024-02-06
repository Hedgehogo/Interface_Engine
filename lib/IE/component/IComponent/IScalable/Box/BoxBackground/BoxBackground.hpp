#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxBackground : public Box, public virtual IScalableBackground, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableBackground::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<INonInteractive::Make> background;
			sf::Vector2f offset = {};
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<INonInteractive::Make>&& background, sf::Vector2f offset = {}, sf::Vector2f min_size = {});
			
			BoxBackground* make(InitInfo init_info) override;
		};
		
		BoxBackground(Make&& make, InitInfo init_info);
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		INonInteractive& get_background() override;
		
		const INonInteractive& get_background() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<INonInteractive> background_;
		BoxPtr<IScalable> object_;
		sf::Vector2f offset_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxBackground::Make> {
	static orl::Option<ie::BoxBackground::Make> decode(ieml::Node const& node);
};
