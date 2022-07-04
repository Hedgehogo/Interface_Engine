#pragma once
#include "../sizing/sizing.h"
#include "../sizing/const/constSizing.h"
#include "../sizing/relative/normal/relativeNormalSizing.h"
#include "../sizing/relative/parent/relativeParentSizing.h"
#include "../sizing/coefficient/parent/parentCoefficientSizing.h"
#include "../sizing/coefficient/target/targetCoefficientSizing.h"
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
	
	Sizing* createSize(bool relativeParent);
	
	Sizing* createSize(float coefficient, float addition, bool relativeTarget);
}
