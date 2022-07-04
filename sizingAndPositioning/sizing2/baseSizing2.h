#pragma once
#include "../sizing/sizing.h"
#include "../sizing/const/constSizing.h"
#include "../sizing/normalSize/normalSizeSizing.h"
#include "../sizing/relativeParent/relativeParentSizing.h"
#include "../sizing/coefficient/parentCoefficient/parentCoefficientSizing.h"
#include "../sizing/coefficient/targetCoefficient/targetCoefficientSizing.h"
#include "../sizing/smart/smartSizing.h"
#include "../sizing/lambda/lambdaSizing.h"

namespace ui {
	class BaseSizing2 {
	public:
		virtual ~BaseSizing2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) = 0;
		
		virtual sf::Vector2f findSize(sf::Vector2f parentSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentSize);
		
		virtual BaseSizing2* copy() = 0;
	};
	
	Sizing* createSize(float coefficient, float addition, bool relativeTarget);
}
