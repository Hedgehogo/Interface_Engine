#include "Sizing2.hpp"
#include "../../ISizing/Functions/makeSize/makeSize.hpp"

namespace ui {
	Sizing2::Make::Make(BoxPtr<ISizing::Make>&& horizontal, BoxPtr<ISizing::Make>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)) {
	}
	
	Sizing2::Make::Make(bool relativeParent) :
		horizontal(makeSizeMake(relativeParent)), vertical(makeSizeMake(relativeParent)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f constSize) :
		horizontal(makeSizeMake(constSize.x)), vertical(makeSizeMake(constSize.y)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget) :
		horizontal(makeSizeMake(coefficient.x, addition.x, relativeTarget)),
		vertical(makeSizeMake(coefficient.y, addition.y, relativeTarget)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition) :
		horizontal(makeSizeMake(targetCoefficient.x, parentCoefficient.x, addition.x)),
		vertical(makeSizeMake(targetCoefficient.y, parentCoefficient.y, addition.y)) {
	}
	
	Sizing2* Sizing2::Make::make(Sizing2InitInfo initInfo) {
		return new Sizing2{std::move(*this), initInfo};
	}
	
	Sizing2::Sizing2(Make&& make, Sizing2InitInfo initInfo) :
		horizontal(make.horizontal->make(initInfo.normalSize.x)),
		vertical(make.vertical->make(initInfo.normalSize.y)),
		renderTarget(&initInfo.renderTarget) {
	}
	
	Sizing2::Sizing2(BoxPtr<ISizing>&& horizontal, BoxPtr<ISizing>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)), renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(bool relativeParent) :
		horizontal(BoxPtr{makeSizeMake(relativeParent)}->make(0)),
		vertical(BoxPtr{makeSizeMake(relativeParent)}->make(0)),
		renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f constSize) :
		horizontal(BoxPtr{makeSizeMake(constSize.x)}->make(0)),
		vertical(BoxPtr{makeSizeMake(constSize.y)}->make(0)),
		renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget) :
		horizontal(BoxPtr{makeSizeMake(coefficient.x, addition.x, relativeTarget)}->make(0)),
		vertical(BoxPtr{makeSizeMake(coefficient.y, addition.y, relativeTarget)}->make(0)),
		renderTarget(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition) :
		horizontal(BoxPtr{makeSizeMake(targetCoefficient.x, parentCoefficient.x, addition.x)}->make(0)),
		vertical(BoxPtr{makeSizeMake(targetCoefficient.y, parentCoefficient.y, addition.y)}->make(0)),
		renderTarget(nullptr) {
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
	
	Sizing2* Sizing2::copy() {
		return new Sizing2{*this};
	}
	
	bool DecodePointer<Sizing2>::decodePointer(const YAML::Node& node, Sizing2*& sizing2) {
		if(node.IsScalar()) {
			sizing2 = new Sizing2{node.as<sf::Vector2f>()};
		} else {
			if(node["horizontal"] && node["vertical"]) {
				sizing2 = new Sizing2{
					node["horizontal"].as<BoxPtr<ISizing> >(),
					node["vertical"].as<BoxPtr<ISizing> >()
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