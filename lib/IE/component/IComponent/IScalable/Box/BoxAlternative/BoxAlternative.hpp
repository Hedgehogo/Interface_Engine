#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxAlternative : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> top_object;
			BoxPtr<IScalable::Make> bottom_object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& top_object, BoxPtr<IScalable::Make>&& bottom_object, sf::Vector2f min_size = {});
			
			BoxAlternative* make(InitInfo init_info) override;
		};
		
		BoxAlternative(Make&& make, InitInfo init_info);
		
		BoxAlternative(BoxPtr<IScalable>&& top_object, BoxPtr<IScalable>&& bottom_object, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		BoxAlternative* copy() override;
		
	protected:
		BoxPtr<IScalable> bottom_object_;
		BoxPtr<IScalable> top_object_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxAlternative> {
		static bool decode_pointer(const YAML::Node& node, BoxAlternative*& box_with_alternative_object);
	};
	*/
}
