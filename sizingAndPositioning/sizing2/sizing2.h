#pragma once

#include "../sizing/sizing.h"
#include "../sizing/const/constSizing.h"
#include "../sizing/normalSize/normalSizeSizing.h"
#include "../sizing/parentCoefficient/parentCoefficientSizing.h"
#include "../sizing/relativeParent/relativeParentSizing.h"

namespace ui {
	class Sizing2 {
	protected:
		Sizing* horizontal;
		Sizing* vertical;
		
	public:
		Sizing2(Sizing* horizontal, Sizing* vertical);
		
		Sizing2();
		
		Sizing2(sf::Vector2f constSize);
		
		Sizing2(sf::Vector2f coefficient, sf::Vector2f addition);
		
		virtual ~Sizing2();
		
		virtual void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize);
		
		virtual sf::Vector2f findSize(sf::Vector2f parentSize);
		
		virtual sf::Vector2f operator()(sf::Vector2f parentSize);
		
		virtual Sizing2* copy();
	};
}
