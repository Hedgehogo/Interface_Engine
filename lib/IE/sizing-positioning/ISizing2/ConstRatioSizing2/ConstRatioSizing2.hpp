#pragma once

#include "../ISizing2.hpp"
#include "../../ISizing/ISizing.hpp"

namespace ie {
	class ConstRatioSizing2 : public virtual ISizing2 {
	public:
		struct Make : public virtual ISizing2::Make {
			BoxPtr<ISizing::Make> sizing;
			float ratio;
			bool horizontal;
			
			Make(BoxPtr<ISizing::Make>&& sizing, float ratio = 1.0f, bool horizontal = true);
			
			Make(float ratio = 1.0f, bool horizontal = true, bool relative_parent = true);
			
			Make(float const_size, float ratio, bool horizontal = true);
			
			Make(float coefficient, float addition, float ratio, bool horizontal = true, bool relative_target = false);
			
			Make(float target_coefficient, float parent_coefficient, float addition, float ratio, bool horizontal = true);
			
			ConstRatioSizing2* make(Sizing2InitInfo init_info) override;
		};
		
		ConstRatioSizing2(Make&& make, Sizing2InitInfo init_info);
		
		explicit ConstRatioSizing2(BoxPtr<ISizing>&& sizing, float ratio = 1.0f, bool horizontal = true);
		
		explicit ConstRatioSizing2(float ratio = 1.0f, bool horizontal = true, bool relative_parent = true);
		
		ConstRatioSizing2(float const_size, float ratio, bool horizontal = true);
		
		ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal = true, bool relative_target = false);
		
		ConstRatioSizing2(float target_coefficient, float parent_coefficient, float addition, float ratio, bool horizontal = true);
		
		void init(sf::RenderTarget& render_target, sf::Vector2f normal_size) override;
		
		sf::Vector2f find_size(sf::Vector2f parent_size) override;
		
		sf::Vector2f get_parent_size(sf::Vector2f object_size) override;
		
		ConstRatioSizing2* copy() override;
	
	protected:
		sf::RenderTarget* render_target;
		BoxPtr<ISizing> sizing;
		float ratio;
		bool horizontal;
	};
	
	template<>
	struct DecodePointer<ConstRatioSizing2> {
		static bool decode_pointer(const YAML::Node& node, ConstRatioSizing2*& const_ratio_sizing2);
	};
}
