#include "BoxBorderHorizontal.hpp"
#include <vector>

namespace ui {
	BoxBorderHorizontal::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f minSize) :
		objects(std::move(objects)), bounds(std::move(addBounds(bounds))), minSize(minSize) {
	}
	
	BoxBorderHorizontal::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f minSize) :
		objects(std::move(objects)), bounds(genBounds(this->objects.size())), minSize(minSize) {
	}
	
	BoxBorderHorizontal::Make::Make(BoxPtr<IScalable::Make>&& firstObject, BoxPtr<IScalable::Make>&& secondObject, float bound, sf::Vector2f minSize) :
		objects(makeVector(std::move(firstObject), std::move(secondObject))), bounds({0.f, bound, 1.f}), minSize(minSize) {
	}
	
	BoxBorderHorizontal* BoxBorderHorizontal::Make::make(InitInfo initInfo) {
		return new BoxBorderHorizontal{std::move(*this), initInfo};
	}
	
	BoxBorderHorizontal::BoxBorderHorizontal(Make&& make, InitInfo initInfo) :
		Box(make.minSize), objects(mapMake(std::move(make.objects), initInfo)), bounds(std::move(make.bounds)) {
	}
	
	BoxBorderHorizontal::BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f minSize) :
		Box(minSize), objects(std::move(objects)), bounds(std::move(addBounds(bounds))) {
	}
	
	BoxBorderHorizontal::BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f minSize) :
		Box(minSize), objects(std::move(objects)), bounds(genBounds(this->objects.size())) {
	}
	
	BoxBorderHorizontal::BoxBorderHorizontal(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, float bound, sf::Vector2f minSize) :
		Box(minSize), objects({std::move(firstObject), std::move(secondObject)}), bounds({0.f, bound, 1.f}) {
	}
	
	void BoxBorderHorizontal::init(InitInfo initInfo) {
		for(auto& object: objects) {
			object->init(initInfo);
		}
	}
	
	void BoxBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		sf::Vector2f coordinate{0, 0};
		sf::Vector2f objectSize{size};
		for(std::size_t x = 0; x < objects.size(); ++x) {
			objectSize.x = size.x * (bounds[x + 1] - bounds[x]);
			objects[x]->resize(objectSize, position + coordinate);
			coordinate.x += objectSize.x;
		}
	}
	
	bool BoxBorderHorizontal::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - layout.position.x, mousePosition.y - layout.position.y};
		if(position.x < 0.0f || position.x > layout.size.x || position.y < 0.0f || position.y > layout.size.y)
			return false;
		position.x = position.x / layout.size.x;
		
		std::size_t object{1};
		while(position.x > bounds[object])
			++object;
		return objects[object - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxBorderHorizontal::getMinSize() const {
		sf::Vector2f minSize{0, 0};
		std::vector<sf::Vector2f> objectMinSizes(objects.size());
		for(std::size_t i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSizes[i] = objects[i]->getMinSize();
		}
		
		sf::Vector2f objectMinSize;
		for(std::size_t i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSize = {objectMinSizes[i].x / (bounds[i + 1] - bounds[i]), objectMinSizes[i].y};
			minSize = max(objectMinSize, minSize);
		}
		
		return max(minSize, this->minimumSize);
	}
	
	sf::Vector2f BoxBorderHorizontal::getNormalSize() const {
		sf::Vector2f normalSize{0, 0};
		std::vector<sf::Vector2f> objectNormalSizes(objects.size());
		for(std::size_t i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSizes[i] = objects[i]->getNormalSize();
		}
		
		sf::Vector2f objectNormalSize;
		for(std::size_t i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSize = {objectNormalSizes[i].x / (bounds[i + 1] - bounds[i]), objectNormalSizes[i].y};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	std::size_t BoxBorderHorizontal::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxBorderHorizontal::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxBorderHorizontal::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	BoxBorderHorizontal* BoxBorderHorizontal::copy() {
		return new BoxBorderHorizontal{*this};
	}
	
	void BoxBorderHorizontal::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto& object: objects) {
			object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
	
	bool DecodePointer<BoxBorderHorizontal>::decodePointer(const YAML::Node& node, BoxBorderHorizontal*& boxWithBorderHorizontal) {
		auto minSize{convDef(node["min-size"], sf::Vector2f{})};
		
		if(node["objects"]) {
			auto objects{node["objects"].as<std::vector<BoxPtr<IScalable> > >()};
			
			if(node["bounds"]) {
				boxWithBorderHorizontal = new BoxBorderHorizontal{
					std::move(objects),
					node["bounds"].as<std::vector<float> >(),
					minSize
				};
			} else {
				boxWithBorderHorizontal = new BoxBorderHorizontal{
					std::move(objects),
					minSize
				};
			}
		} else {
			boxWithBorderHorizontal = new BoxBorderHorizontal{
				node["first-object"].as<BoxPtr<IScalable> >(),
				node["first-object"].as<BoxPtr<IScalable> >(),
				convDef(node["bound"], 0.5f),
				minSize
			};
		}
		return true;
	}
}