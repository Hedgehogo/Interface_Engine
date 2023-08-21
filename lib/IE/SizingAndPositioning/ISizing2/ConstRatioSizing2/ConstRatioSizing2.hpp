#pragma once

#include "../ISizing2.hpp"
#include "../../ISizing/ISizing.hpp"

namespace ui {
	class ConstRatioSizing2 : public ISizing2 {
	public:
		struct Make : public ISizing2::Make {
			BoxPtr<ISizing::Make> sizing;
			float ratio;
			bool horizontal;
			
			Make(BoxPtr<ISizing::Make>&& sizing, float ratio = 1.0f, bool horizontal = true);
			
			Make(float ratio = 1.0f, bool horizontal = true, bool relativeParent = true);
			
			Make(float constSize, float ratio, bool horizontal = true);
			
			Make(float coefficient, float addition, float ratio, bool horizontal = true, bool relativeTarget = false);
			
			Make(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal = true);
			
			ConstRatioSizing2* make(Sizing2InitInfo initInfo) override;
		};
		
		ConstRatioSizing2(Make&& make, Sizing2InitInfo initInfo);
		
		explicit ConstRatioSizing2(BoxPtr<ISizing>&& sizing, float ratio = 1.0f, bool horizontal = true);
		
		explicit ConstRatioSizing2(float ratio = 1.0f, bool horizontal = true, bool relativeParent = true);
		
		ConstRatioSizing2(float constSize, float ratio, bool horizontal = true);
		
		ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal = true, bool relativeTarget = false);
		
		ConstRatioSizing2(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal = true);
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		ConstRatioSizing2* copy() override;
	
	protected:
		sf::RenderTarget* renderTarget;
		BoxPtr<ISizing> sizing;
		float ratio;
		bool horizontal;
	};
	
	template<>
	struct DecodePointer<ConstRatioSizing2> {
		static bool decodePointer(const YAML::Node& node, ConstRatioSizing2*& constRatioSizing2);
	};
}
