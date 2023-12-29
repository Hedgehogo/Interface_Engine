#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxMakePermeable : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			BoxMakePermeable* make(InitInfo init_info) override;
		};
		
		BoxMakePermeable(Make&& make, InitInfo init_info);
		
		BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f min_size);
		
		void init(InitInfo init_info) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxMakePermeable* copy() override;
		
	protected:
		BoxPtr<IScalable> object_;
	};
	
	template<>
	struct DecodePointer<BoxMakePermeable> {
		static bool decode_pointer(const YAML::Node& node, BoxMakePermeable*& box_make_permeable);
	};
}