#include "sizing2.hpp"
#include "../../sizing/make/makeSize.hpp"

namespace ui {
	Sizing2::Sizing2(ISizing* horizontal, ISizing* vertical) :
		horizontal(horizontal), vertical(vertical), renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(bool relativeParent) :
		horizontal(makeSize(relativeParent)), vertical(makeSize(relativeParent)), renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f constSize) :
		horizontal(makeSize(constSize.x)), vertical(makeSize(constSize.y)), renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget) :
		horizontal(makeSize(coefficient.x, addition.x, relativeTarget)),
		vertical(makeSize(coefficient.y, addition.y, relativeTarget)),
		renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition) :
		horizontal(makeSize(targetCoefficient.x, parentCoefficient.x, addition.x)),
		vertical(makeSize(targetCoefficient.y, parentCoefficient.y, addition.y)),
		renderTarget(nullptr) {
	}
	
	Sizing2::~Sizing2() {
		delete horizontal;
		delete vertical;
	}
	
	void Sizing2::init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		horizontal->init(normalSize.x);
		vertical->init(normalSize.y);
	}
	
	sf::Vector2f Sizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{renderTarget->getSize()};
		return {horizontal->findSize(parentSize.x, targetSize.x), vertical->findSize(parentSize.y, targetSize.y)};
	}
	
	sf::Vector2f Sizing2::getParentSize(sf::Vector2f objectSize) {
		return {horizontal->getParentSize(objectSize.x), vertical->getParentSize(objectSize.y)};
	}
	
	void Sizing2::copy(Sizing2* sizing2) {
		sizing2->renderTarget = this->renderTarget;
	}
	
	Sizing2* Sizing2::copy() {
		Sizing2* sizing2{new Sizing2{horizontal->copy(), vertical->copy()}};
		Sizing2::copy(sizing2);
		return sizing2;
	}
	
	bool DecodePointer<Sizing2>::decodePointer(const YAML::Node& node, Sizing2*& sizing2) {
		if(node.IsScalar()) {
			sizing2 = new Sizing2{node.as<sf::Vector2f>()};
		} else {
			if(node["horizontal"] && node["vertical"]) {
				sizing2 = new Sizing2{
					node["horizontal"].as<ISizing*>(),
					node["vertical"].as<ISizing*>()
				};
			} else if(node["relative"]) {
				sizing2 = new Sizing2{
					convertBool(node["relative"], "parent", "normal")
				};
			} else if(node["const-size"]) {
				sizing2 = new Sizing2{
					node["const-size"].as<sf::Vector2f>()
				};
			} else if(node["coefficient"]) {
				sizing2 = new Sizing2{
					node["coefficient"].as<sf::Vector2f>(),
					convDef(node["addition"], sf::Vector2f{}),
					convBoolDef(node["relative"], "target", "parent")
				};
			} else if(node["target-coefficient"] && node["parent-coefficient"]) {
				sizing2 = new Sizing2{
					node["target-coefficient"].as<sf::Vector2f>(),
					node["parent-coefficient"].as<sf::Vector2f>(),
					convDef(node["addition"], sf::Vector2f{})
				};
			} else {
				throw YAML::BadConversion{node.Mark()};
			}
		}
		return true;
	}
}