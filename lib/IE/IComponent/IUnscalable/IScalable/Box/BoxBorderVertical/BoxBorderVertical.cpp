#include "BoxBorderVertical.hpp"
#include <vector>

namespace ui {
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f minSize) :
		objects(std::move(objects)), bounds(std::move(addBounds(bounds))), minSize(minSize) {
	}
	
	BoxBorderVertical::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f minSize) :
		objects(std::move(objects)), bounds(genBounds(this->objects.size())), minSize(minSize) {
	}
	
	BoxBorderVertical::Make::Make(BoxPtr<IScalable::Make>&& firstObject, BoxPtr<IScalable::Make>&& secondObject, float bound, sf::Vector2f minSize) :
		objects(makeVector(std::move(firstObject), std::move(secondObject))), bounds({0.f, bound, 1.f}), minSize(minSize) {
	}
	
	BoxBorderVertical* BoxBorderVertical::Make::make(InitInfo initInfo) {
		return new BoxBorderVertical{std::move(*this), initInfo};
	}
	
	BoxBorderVertical::BoxBorderVertical(Make&& make, InitInfo initInfo) :
		Box(make.minSize), objects(mapMake(std::move(make.objects), initInfo)), bounds(std::move(make.bounds)) {
	}
	
	BoxBorderVertical::BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f minSize) :
		Box(minSize), objects(std::move(objects)), bounds(std::move(addBounds(bounds))) {
	}
	
	BoxBorderVertical::BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f minSize) :
		Box(minSize), objects(std::move(objects)), bounds(genBounds(this->objects.size())) {
	}
	
	BoxBorderVertical::BoxBorderVertical(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, float bound, sf::Vector2f minSize) :
		Box(minSize), objects({std::move(firstObject), std::move(secondObject)}), bounds({0.f, bound, 1.f}) {
	}
	
	void BoxBorderVertical::init(InitInfo initInfo) {
		for(auto& object: objects) {
			object->init(initInfo);
		}
	}
	
	void BoxBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		sf::Vector2f coordinate{0, 0};
		sf::Vector2f objectSize{size};
		for(std::size_t y = 0; y < objects.size(); ++y) {
			objectSize.y = size.y * (bounds[y + 1] - bounds[y]);
			objects[y]->resize(objectSize, position + coordinate);
			coordinate.y += objectSize.y;
		}
	}
	
	bool BoxBorderVertical::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - layout.position.x, mousePosition.y - layout.position.y};
		if(position.x < 0.0f || position.x > layout.size.x || position.y < 0.0f || position.y > layout.size.y)
			return false;
		position.y = position.y / layout.size.y;
		
		std::size_t i{1};
		while(position.y > bounds[i])
			++i;
		return objects[i - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxBorderVertical::getMinSize() const {
		sf::Vector2f minSize{0, 0};
		std::vector<sf::Vector2f> objectMinSizes(objects.size());
		for(std::size_t i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSizes[i] = objects[i]->getMinSize();
		}
		
		sf::Vector2f objectMinSize;
		for(std::size_t i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSize = {objectMinSizes[i].x, objectMinSizes[i].y / (bounds[i + 1] - bounds[i])};
			minSize = max(objectMinSize, minSize);
		}
		
		return max(minSize, this->minimumSize);
	}
	
	sf::Vector2f BoxBorderVertical::getNormalSize() const {
		sf::Vector2f normalSize{0, 0};
		std::vector<sf::Vector2f> objectNormalSizes(objects.size());
		for(std::size_t i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSizes[i] = objects[i]->getNormalSize();
		}
		
		sf::Vector2f objectNormalSize;
		for(std::size_t i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSize = {objectNormalSizes[i].x, objectNormalSizes[i].y / (bounds[i + 1] - bounds[i])};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	std::size_t BoxBorderVertical::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxBorderVertical::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxBorderVertical::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxBorderVertical* BoxBorderVertical::copy() {
		return new BoxBorderVertical{*this};
	}
	
	bool DecodePointer<BoxBorderVertical>::decodePointer(const YAML::Node& node, BoxBorderVertical*& boxWithBorderVertical) {
		auto minSize{convDef(node["min-size"], sf::Vector2f{})};
		
		if(node["objects"]) {
			auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
			
			if(node["bounds"]) {
				boxWithBorderVertical = new BoxBorderVertical{
					std::move(objects),
					node["bounds"].as<std::vector<float> >(),
					minSize
				};
			} else {
				boxWithBorderVertical = new BoxBorderVertical{
					std::move(objects),
					minSize
				};
			}
		} else {
			boxWithBorderVertical = new BoxBorderVertical{
				node["first-object"].as<BoxPtr<IScalable> >(),
				node["first-object"].as<BoxPtr<IScalable> >(),
				convDef(node["bound"], 0.5f),
				minSize
			};
		}
		return true;
	}
	
	void BoxBorderVertical::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto& object: objects) {
			object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
}
