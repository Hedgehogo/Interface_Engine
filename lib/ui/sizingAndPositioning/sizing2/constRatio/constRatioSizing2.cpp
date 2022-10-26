#include "constRatioSizing2.hpp"
#include "../../sizing/create/CreateSize.hpp"

namespace ui {
	ConstRatioSizing2::ConstRatioSizing2(Sizing *sizing, float ratio, bool horizontal) : sizing(sizing), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float ratio, bool horizontal, bool relativeParent) : sizing(createSize(relativeParent)), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float constSize, float ratio, bool horizontal) :
		sizing(new ConstSizing{constSize}), ratio(ratio), horizontal(horizontal) {}
	
	ConstRatioSizing2::ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal, bool relativeTarget) :
		sizing(createSize(coefficient, addition, relativeTarget)), ratio(ratio), horizontal(horizontal) {}
	
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
		float ratio{1.0f};
		bool horizontal{true};
		
		if(node["ratio"])
			node["ratio"] >> ratio;
		if(node["direction"]) {
			std::string direction;
			
			node["direction"] >> direction;
			
			if(direction == "vertical") {
				horizontal = false;
			} else if(direction != "horizontal") {
				throw YAML::BadConversion{node["direction"].Mark()};
			}
		}
		
		if(node["sizing"]) {
			Sizing* sizing;
			
			node["sizing"] >> sizing;
			
			{ constRatioSizing2 = new ConstRatioSizing2{sizing}; return true; }
		} else if(node["relative"]) {
			std::string relative;
			
			node["relative"] >> relative;
			
			if(relative == "parent") {
				{ constRatioSizing2 = new ConstRatioSizing2{ratio, horizontal, true}; return true; }
			} else if(relative == "normal") {
				{ constRatioSizing2 = new ConstRatioSizing2{ratio, horizontal, false}; return true; }
			} else {
				throw YAML::BadConversion{node["relative"].Mark()};
			}
		} else if(node["const-size"]) {
			float constSize;
			
			node["const-size"] >> constSize;
			
			{ constRatioSizing2 = new ConstRatioSizing2{constSize, ratio, horizontal}; return true; }
		} else if(node["coefficient"]) {
			float coefficient;
			float addition{};
			bool relativeTarget{false};
			
			node["coefficient"] >> coefficient;
			if(node["addition"])
				node["addition"] >>  addition;
			if(node["relative"]) {
				std::string relative;
				
				node["relative"] >> relative;
				
				if(relative == "target") {
					relativeTarget = true;
				} else if(relative != "parent") {
					throw YAML::BadConversion{node["relative"].Mark()};
				}
			}
			
			{ constRatioSizing2 = new ConstRatioSizing2{coefficient, addition, ratio, horizontal, relativeTarget}; return true; }
		} else if(node["target-coefficient"] && node["parent-coefficient"]) {
			float targetCoefficient;
			float parentCoefficient;
			float addition{};
			
			node["target-coefficient"] >> targetCoefficient;
			node["parent-coefficient"] >> parentCoefficient;
			if(node["addition"])
				node["addition"] >> addition;
			
			{ constRatioSizing2 = new ConstRatioSizing2{targetCoefficient, parentCoefficient, addition, ratio, horizontal}; return true; }
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
}