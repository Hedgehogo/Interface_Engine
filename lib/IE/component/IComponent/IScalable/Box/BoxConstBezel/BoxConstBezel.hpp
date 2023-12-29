#pragma once

#include "../Box.hpp"
#include "../../IUninteractive/IUninteractive.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"

namespace ie {
	class BoxConstBezel : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> bezel;
			float thickness;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f min_size = {});
			
			BoxConstBezel* make(InitInfo init_info) override;
		};
		
		BoxConstBezel(Make&& make, InitInfo init_info);
		
		BoxConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxConstBezel* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<IUninteractive> bezel_;
		BoxPtr<IScalable> object_;
		float thickness_;
	};
	
	template<>
	struct DecodePointer<BoxConstBezel> {
		static bool decode_pointer(const YAML::Node& node, BoxConstBezel*& box_with_const_bezel);
	};
}