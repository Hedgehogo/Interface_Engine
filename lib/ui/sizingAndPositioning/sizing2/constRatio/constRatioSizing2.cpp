#include "constRatioSizing2.hpp"
#include "../../sizing/make/makeSize.hpp"

namespace ui {
	ConstRatioSizing2::ConstRatioSizing2(ISizing *sizing, float ratio, bool horizontal) : sizing(sizing), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float ratio, bool horizontal, bool relativeParent) : sizing(makeSize(relativeParent)), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float constSize, float ratio, bool horizontal) :
		sizing(new ConstSizing{constSize}), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal, bool relativeTarget) :
		sizing(makeSize(coefficient, addition, relativeTarget)), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal) :
		sizing(new SmartSizing{targetCoefficient, parentCoefficient, addition}), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::~ConstRatioSizing2() {
		delete sizing;
	}
	
	void ConstRatioSizing2::init(sf::RenderTarget &renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		sizing->init((horizontal ? normalSize.x : normalSize.y));
	}
	
	sf::Vector2f ConstRatioSizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		float size = (horizontal ? sizing->findSize(parentSize.x, targetSize.x) : sizing->findSize(parentSize.y, targetSize.y));
		return (horizontal ? sf::Vector2f{size, size / ratio} : sf::Vector2f{size * ratio, size});
	}
	
	sf::Vector2f ConstRatioSizing2::getParentSize(sf::Vector2f objectSize) {
		float size = (horizontal ? sizing->getParentSize(objectSize.x) : sizing->getParentSize(objectSize.y));
		return (horizontal ? sf::Vector2f{size, size / ratio} : sf::Vector2f{size * ratio, size});
	}
	
	void ConstRatioSizing2::copy(ConstRatioSizing2 *constRatioSizing2) {
		constRatioSizing2->renderTarget = this->renderTarget;
	}
	
	ConstRatioSizing2 *ConstRatioSizing2::copy() {
		ConstRatioSizing2* constRatioSizing2{new ConstRatioSizing2{sizing->copy(), ratio, horizontal}};
		ConstRatioSizing2::copy(constRatioSizing2);
		return constRatioSizing2;
	}
	
	bool convertPointer(const YAML::Node &node, ConstRatioSizing2 *&constRatioSizing2) {
		float ratio{convDef(node["ratio"], 1.f)};
		bool horizontal{convBoolDef(node["direction"], "horizontal", "vertical", true)};
		
		if(node["sizing"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				node["sizing"].as<ISizing*>(),
				ratio,
				horizontal
			};
		} else if(node["relative"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				ratio,
				horizontal,
				convertBool(node["relative"], "parent", "normal")
			};
		} else if(node["const-size"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				node["const-size"].as<float>(),
				ratio,
				horizontal
			};
		} else if(node["coefficient"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				node["coefficient"].as<float>(),
				convDef(node["addition"], 0.f),
				ratio,
				horizontal,
				convBoolDef(node["relative"], "target", "parent")
			};
		} else if(node["target-coefficient"] && node["parent-coefficient"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				node["target-coefficient"].as<float>(),
				node["parent-coefficient"].as<float>(),
				convDef(node["addition"], 0.f),
				ratio,
				horizontal
			};
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
}