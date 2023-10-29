#pragma once

#include "../ISizing2.hpp"
#include "../../ISizing/ISizing.hpp"

namespace ie {
	class Sizing2 : public virtual ISizing2 {
	public:
		struct Make : public virtual ISizing2::Make {
			BoxPtr<ISizing::Make> horizontal;
			BoxPtr<ISizing::Make> vertical;
			
			Make(BoxPtr<ISizing::Make>&& horizontal, BoxPtr<ISizing::Make>&& vertical);
			
			Make(bool relative_parent);
			
			Make(sf::Vector2f const_size);
			
			Make(sf::Vector2f coefficient, sf::Vector2f addition, bool relative_target = false);
			
			Make(sf::Vector2f target_coefficient, sf::Vector2f parent_coefficient, sf::Vector2f addition);
			
			Sizing2* make(Sizing2InitInfo init_info) override;
		};
		
		Sizing2(Make&& make, Sizing2InitInfo init_info);
		
		Sizing2(BoxPtr<ISizing>&& horizontal, BoxPtr<ISizing>&& vertical);
		
		Sizing2(bool relative_parent);
		
		Sizing2(sf::Vector2f const_size);
		
		Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relative_target = false);
		
		Sizing2(sf::Vector2f target_coefficient, sf::Vector2f parent_coefficient, sf::Vector2f addition);
		
		void init(sf::RenderTarget& render_target, sf::Vector2f normal_size) override;
		
		sf::Vector2f find_size(sf::Vector2f parent_size) override;
		
		sf::Vector2f get_parent_size(sf::Vector2f object_size) override;
		
		Sizing2* copy() override;
	
	protected:
		BoxPtr<ISizing> horizontal_;
		BoxPtr<ISizing> vertical_;
		sf::RenderTarget* render_target_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<Sizing2> {
		static bool decode_pointer(const YAML::Node& node, Sizing2*& sizing2);
	};
	*/
}
