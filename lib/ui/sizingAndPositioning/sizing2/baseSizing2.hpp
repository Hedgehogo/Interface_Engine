#pragma once
#include "../sizing/sizing.hpp"
#include "../sizing/const/constSizing.hpp"
#include "../sizing/relative/normal/relativeNormalSizing.hpp"
#include "../sizing/relative/parent/relativeParentSizing.hpp"
#include "../sizing/coefficient/parent/parentCoefficientSizing.hpp"
#include "../sizing/coefficient/target/targetCoefficientSizing.hpp"
#include "../sizing/smart/smartSizing.hpp"
#include "../sizing/lambda/lambdaSizing.hpp"

namespace ui {
	class BaseSizing2 {
	public:
		virtual ~BaseSizing2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) = 0;
		
		virtual sf::Vector2f findSize(sf::Vector2f parentSize) = 0;
		
		virtual sf::Vector2f getParentSize(sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentSize);
		
		virtual BaseSizing2* copy() = 0;
		
		static BaseSizing2* createFromYaml(const YAML::Node &node);
	};
	
	Sizing* createSize(bool relativeParent);
	
	Sizing* createSize(float coefficient, float addition, bool relativeTarget);
}
