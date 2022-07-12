#pragma once
#include "../baseSizing2.h"

namespace ui {
	class ConstRatioSizing2 : BaseSizing2 {
	protected:
		sf::RenderTarget* renderTarget;
		Sizing* sizing;
		float ratio;
		bool horizontal;
		
		void copy(ConstRatioSizing2* constRatioSizing2);
	
	public:
		explicit ConstRatioSizing2(Sizing* sizing, float ratio = 1.0f, bool horizontal = true);
		
		explicit ConstRatioSizing2(float ratio = 1.0f, bool horizontal = true);
		
		ConstRatioSizing2(float constSize, float ratio, bool horizontal = true);
		
		ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal = true, bool relativeTarget = false);
		
		ConstRatioSizing2(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal = true);
		
		~ConstRatioSizing2() override;
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentMinSize(sf::Vector2f objectMinSize) override;
		
		ConstRatioSizing2* copy() override;
	};
}
