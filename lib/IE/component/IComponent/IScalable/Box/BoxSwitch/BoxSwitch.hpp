#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISValue/ISValue.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxSwitch : public Box, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> inactive_object;
			BoxPtr<IScalable::Make> active_object;
			MakeDyn<ISBool> value;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& inactive_object, BoxPtr<IScalable::Make>&& active_object, MakeDyn<ISBool> value, const sf::Vector2f& min_size = {});
			
			BoxSwitch* make(InitInfo init_info) override;
		};
		
		BoxSwitch(Make&& make, InitInfo init_info);
		
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
		
	protected:
		DrawManager inactive_draw_manager_;
		DrawManager active_draw_manager_;
		BoxPtr<IScalable> inactive_object_;
		BoxPtr<IScalable> active_object_;
		ISBool& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitch::Make> {
	static orl::Option<ie::BoxSwitch::Make> decode(ieml::Node const& node);
};
