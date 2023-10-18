#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxSwitch : public Box, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> inactive_object;
			BoxPtr<IScalable::Make> active_object;
			PSbool value;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& inactive_object, BoxPtr<IScalable::Make>&& active_object, PSbool value, const sf::Vector2f& min_size = {});
			
			BoxSwitch* make(InitInfo init_info) override;
		};
		
		BoxSwitch(Make&& make, InitInfo init_info);
		
		BoxSwitch(BoxPtr<IScalable>&& inactive_object, BoxPtr<IScalable>&& active_object, PSbool value, const sf::Vector2f& min_size = {});
		
		BoxSwitch(const BoxSwitch& other);
		
		void init(InitInfo init_info) override;
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		BoxSwitch* copy() override;
	
	protected:
		DrawManager inactive_draw_manager;
		DrawManager active_draw_manager;
		BoxPtr<IScalable> inactive_object;
		BoxPtr<IScalable> active_object;
		PSbool value;
	};
	
	template<>
	struct DecodePointer<BoxSwitch> {
		static bool decode_pointer(const YAML::Node& node, BoxSwitch*& box_switcher);
	};
}
