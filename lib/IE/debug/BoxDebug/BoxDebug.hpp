#pragma once

#include "IE/component/IComponent/IScalable/Box/Box.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class BoxDebug : public Box, public virtual IComponentObject, public virtual IDrawable {
	public:
		struct Make : public Box::Make, public virtual IComponentObject::Make {
			BoxPtr<IScalable::Make> object;
			
			Make(BoxPtr<IScalable::Make>&& object);
			
			BoxDebug* make(InitInfo init_info) override;
		};
		
		BoxDebug(Make&& make, InitInfo init_info);
		
		BoxDebug(BoxPtr<IScalable>&& object);
		
		void init(InitInfo init_info) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxDebug* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<IScalable> object;
		sf::RenderTarget* render_target;
		bool active;
		bool drawn;
	};
	
	template<>
	struct DecodePointer<BoxDebug> {
		static bool decode_pointer(const YAML::Node& node, BoxDebug*& box_debug);
	};
}
