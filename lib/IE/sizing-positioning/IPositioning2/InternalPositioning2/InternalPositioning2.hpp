#pragma once

#include "../IPositioning2.hpp"
#include "../../IPositioning/InternalPositioning/InternalPositioning.hpp"

namespace ie {
	class InternalPositioning2 : public virtual IPositioning2 {
	public:
		struct Make : public virtual IPositioning2::Make {
			sf::Vector2f coefficient;
			
			Make(sf::Vector2f coefficient);
		
			InternalPositioning2* make(Positioning2InitInfo init_info) override;
		};
		
		InternalPositioning2(Make&& make, Positioning2InitInfo init_info);
		
		InternalPositioning2(sf::Vector2f coefficient);
		
		void init(sf::RenderTarget&);
		
		sf::Vector2f find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size);
	
		InternalPositioning2* copy();
	
	protected:
		InternalPositioning vertical_;
		InternalPositioning horizontal_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<InternalPositioning2> {
		static bool decode_pointer(const YAML::Node& node, InternalPositioning2*& internal_positioning2);
	};
	*/
}