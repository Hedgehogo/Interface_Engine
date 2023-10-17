#include "ConstRatioSizing2.hpp"
#include "IE/sizing-positioning/ISizing/Functions/make_size_make/make_size_make.hpp"

namespace ie {
	ConstRatioSizing2::Make::Make(BoxPtr<ISizing::Make>&& sizing, float ratio, bool horizontal) :
		sizing(std::move(sizing)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float ratio, bool horizontal, bool relativeParent) :
		sizing(make_size_make(relativeParent)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float constSize, float ratio, bool horizontal) :
		sizing(new ConstSizing::Make{constSize}), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float coefficient, float addition, float ratio, bool horizontal, bool relativeTarget) :
		sizing(make_size_make(coefficient, addition, relativeTarget)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal) :
		sizing(new SmartSizing::Make{targetCoefficient, parentCoefficient, addition}), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2* ConstRatioSizing2::Make::make(Sizing2InitInfo initInfo) {
		return new ConstRatioSizing2{std::move(*this), initInfo};
	}
	
	ConstRatioSizing2::ConstRatioSizing2(Make&& make, Sizing2InitInfo initInfo) :
		renderTarget(&initInfo.renderTarget),
		sizing(make.sizing->make((make.horizontal ? initInfo.normalSize.x : initInfo.normalSize.y))),
		ratio(make.ratio),
		horizontal(make.horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(BoxPtr<ISizing>&& sizing, float ratio, bool horizontal) : sizing(std::move(sizing)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float ratio, bool horizontal, bool relativeParent) :
		sizing(BoxPtr{make_size_make(relativeParent)}->make(0)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float constSize, float ratio, bool horizontal) :
		sizing(new ConstSizing{constSize}), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal, bool relativeTarget) :
		sizing(BoxPtr{make_size_make(coefficient, addition, relativeTarget)}->make(0)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float targetCoefficient, float parentCoefficient, float addition, float ratio, bool horizontal) :
		sizing(new SmartSizing{targetCoefficient, parentCoefficient, addition}), ratio(ratio), horizontal(horizontal) {
	}
	
	void ConstRatioSizing2::init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) {
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
	
	ConstRatioSizing2* ConstRatioSizing2::copy() {
		return new ConstRatioSizing2{*this};
	}
	
	bool DecodePointer<ConstRatioSizing2>::decodePointer(const YAML::Node& node, ConstRatioSizing2*& constRatioSizing2) {
		float ratio{convDef(node["ratio"], 1.f)};
		bool horizontal{convBoolDef(node["direction"], "horizontal", "vertical", true)};
		
		if(node["sizing"]) {
			constRatioSizing2 = new ConstRatioSizing2{
				node["sizing"].as<BoxPtr<ISizing> >(),
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