#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxBackground : public Box, public virtual IScalableBackground, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableBackground::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> background;
			sf::Vector2f offset = {};
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset = {}, sf::Vector2f min_size = {});
			
			BoxBackground* make(InitInfo init_info) override;
		};
		
		BoxBackground(Make&& make, InitInfo init_info);
		
		BoxBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset = {}, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IUninteractive& get_background() override;
		
		const IUninteractive& get_background() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BoxBackground* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) override;
	
	protected:
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		sf::Vector2f offset;
	};
	
	template<>
	struct DecodePointer<BoxBackground> {
		static bool decode_pointer(const YAML::Node& node, BoxBackground*& box_with_background);
	};
}