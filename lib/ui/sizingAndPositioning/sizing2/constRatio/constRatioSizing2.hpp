#pragma once
#include "../iSizing2.hpp"
#include "../../sizing/iSizing.hpp"

namespace ui {
	class ConstRatioSizing2 : public ISizing2 {
	protected:
		sf::RenderTarget* renderTarget;
		ISizing* sizing;
		float ratio;
		bool horizontal;
		
		void copy(ConstRatioSizing2* constRatioSizing2);
	
	public:
		explicit ConstRatioSizing2(ISizing* sizing, float ratio = 1.0f, bool horizontal = true);
		
		explicit ConstRatioSizing2(float ratio = 1.0f, bool horizontal = true, bool relativeParent = true);
		
		ConstRatioSizing2(float constSize, float ratio, bool horizontal = true);
		
		ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal = true, bool relativeTarget = false);
		
		ConstRatioSizing2(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal = true);
		
		~ConstRatioSizing2() override;
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		ConstRatioSizing2* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ConstRatioSizing2 *&constRatioSizing2);
}
