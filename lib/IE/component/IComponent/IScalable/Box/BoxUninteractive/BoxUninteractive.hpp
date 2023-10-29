#pragma once

#include "../Box.hpp"
#include "../../IUninteractive/IUninteractiveLayout/IUninteractiveObject/IUninteractiveObject.hpp"

namespace ie {
	class BoxUninteractive : public Box, public virtual IUninteractiveObject {
	public:
		struct Make : public virtual Box::Make, public virtual IUninteractiveObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			BoxUninteractive* make(InitInfo init_info) override;
		};
		
		BoxUninteractive(Make&& make, InitInfo init_info);
		
		BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		BoxUninteractive* copy() override;
		
	protected:
		BoxPtr<IScalable> object_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxUninteractive> {
		static bool decode_pointer(const YAML::Node& node, BoxUninteractive*& box_uninteractive);
	};
	*/
}