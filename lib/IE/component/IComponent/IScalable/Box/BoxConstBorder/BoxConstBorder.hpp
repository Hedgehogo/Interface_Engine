#pragma once

#include "IE/enums/Side/Side.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstBorder : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> second_object;
			float border_distance;
			Side side;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& second_object, float border_distance, Side side, sf::Vector2f min_size = {});
			
			BoxConstBorder* make(InitInfo init_info) override;
		};
		
		BoxConstBorder(Make&& make, InitInfo init_info);
		
		BoxConstBorder(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& second_object, Side side, float border_distance, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		BoxConstBorder* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> second_object_;
		float border_distance_;
		Side side_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxConstBorder> {
		static bool decode_pointer(const YAML::Node& node, BoxConstBorder*& box_with_const_border);
	};
	*/
}