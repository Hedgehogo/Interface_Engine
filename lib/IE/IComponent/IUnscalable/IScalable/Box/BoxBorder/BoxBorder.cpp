#include "BoxBorder.hpp"
#include <vector>

namespace ui {
	BoxBorder::Make::Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize) :
		objects(std::move(objects)), boundsHorizontal(std::move(addBounds(boundsHorizontal))), boundsVertical(std::move(addBounds(boundsVertical))), minSize(minSize) {
	}
	
	BoxBorder::Make::Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f minSize) :
		objects(std::move(objects)), boundsHorizontal(genBounds(this->objects.size())), boundsVertical(genBounds(y_size(this->objects))), minSize(minSize) {
	}
	
	BoxBorder* BoxBorder::Make::make(InitInfo initInfo) {
		return new BoxBorder{std::move(*this), initInfo};
	}
	
	BoxBorder::BoxBorder(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		objects(mapMake(std::move(make.objects), initInfo)),
		boundsHorizontal(std::move(make.boundsHorizontal)),
		boundsVertical(std::move(make.boundsVertical)) {
	}
	
	BoxBorder::BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize) :
		Box(minSize), objects(std::move(objects)), boundsHorizontal(std::move(addBounds(boundsHorizontal))), boundsVertical(std::move(addBounds(boundsVertical))) {
	}
	
	BoxBorder::BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, sf::Vector2f minSize) :
		Box(minSize), objects(objects), boundsHorizontal(genBounds(this->objects.size())), boundsVertical(genBounds(y_size(this->objects))) {
	}
	
	void BoxBorder::init(InitInfo initInfo) {
		for(auto& line: objects) {
			for(auto& object: line) {
				object->init(initInfo);
			}
		}
	}
	
	void BoxBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		sf::Vector2f coordinate{};
		sf::Vector2f objectSize{size};
		for(std::size_t x = 0; x < objects.size(); ++x) {
			objectSize.x = size.x * (boundsHorizontal[x + 1] - boundsHorizontal[x]);
			coordinate.y = 0;
			for(std::size_t y = 0; y < objects[0].size(); ++y) {
				objectSize.y = size.y * (boundsVertical[y + 1] - boundsVertical[y]);
				objects[x][y]->resize(objectSize, position + coordinate);
				coordinate.y += objectSize.y;
			}
			coordinate.x += objectSize.x;
		}
	}
	
	bool BoxBorder::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - layout.position.x, mousePosition.y - layout.position.y};
		if(position.x < 0.0f || position.x > layout.size.x || position.y < 0.0f || position.y > layout.size.y) {
			return false;
		}
		position = {position.x / layout.size.x, position.y / layout.size.y};
		
		sf::Vector2u object{1, 1};
		while(position.x > boundsHorizontal[object.x]) {
			++object.x;
		}
		while(position.y > boundsVertical[object.y]) {
			++object.y;
		}
		return objects[object.x - 1][object.y - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxBorder::getMinSize() const {
		sf::Vector2f minSize{0, 0};
		std::vector<std::vector<sf::Vector2f>> objectMinSizes(objects.size());
		for(std::size_t x = 0; x < objectMinSizes.size(); ++x) {
			for(std::size_t y = 0; y < objectMinSizes[x].size(); ++y) {
				objectMinSizes[x][y] = objects[x][y]->getMinSize();
			}
		}
		
		sf::Vector2f lineMinSize{0, 0};
		sf::Vector2f objectMinSize{0, 0};
		for(auto& line: objectMinSizes) {
			lineMinSize.y = 0;
			for(std::size_t y = 0; y < line.size(); ++y) {
				objectMinSize.y = line[y].y / (boundsVertical[y + 1] - boundsVertical[y]);
				lineMinSize.y = std::max(objectMinSize.y, lineMinSize.y);
			}
			minSize.y = std::max(lineMinSize.y, minSize.y);
		}
		
		for(std::size_t y = 0; y < objectMinSizes[0].size(); ++y) {
			lineMinSize.x = 0;
			for(std::size_t x = 0; x < objectMinSizes.size(); ++x) {
				objectMinSize.x = objectMinSizes[x][y].x / (boundsHorizontal[x + 1] - boundsHorizontal[x]);
				lineMinSize.x = std::max(objectMinSize.x, lineMinSize.x);
			}
			minSize.x = std::max(lineMinSize.x, minSize.x);
		}
		
		return {std::max(minSize.x, this->minimumSize.x), std::max(minSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f BoxBorder::getNormalSize() const {
		sf::Vector2f normalSize{0, 0};
		std::vector<std::vector<sf::Vector2f>> objectNormalSizes(objects.size());
		for(std::size_t x = 0; x < objectNormalSizes.size(); ++x) {
			for(std::size_t y = 0; y < objectNormalSizes[x].size(); ++y) {
				objectNormalSizes[x][y] = objects[x][y]->getNormalSize();
			}
		}
		
		sf::Vector2f lineNormalSize{0, 0};
		sf::Vector2f objectNormalSize{0, 0};
		for(auto& line: objectNormalSizes) {
			lineNormalSize.y = 0;
			for(std::size_t y = 0; y < line.size(); ++y) {
				objectNormalSize.y = line[y].y / (boundsVertical[y + 1] - boundsVertical[y]);
				lineNormalSize.y = std::max(objectNormalSize.y, lineNormalSize.y);
			}
			normalSize.y = std::max(lineNormalSize.y, normalSize.y);
		}
		
		for(std::size_t y = 0; y < objectNormalSizes[0].size(); ++y) {
			lineNormalSize.x = 0;
			for(std::size_t x = 0; x < objectNormalSizes.size(); ++x) {
				objectNormalSize.x = objectNormalSizes[x][y].x / (boundsHorizontal[x + 1] - boundsHorizontal[x]);
				lineNormalSize.x = std::max(objectNormalSize.x, lineNormalSize.x);
			}
			normalSize.x = std::max(lineNormalSize.x, normalSize.x);
		}
		
		return normalSize;
	}
	
	BoxBorder* BoxBorder::copy() {
		return new BoxBorder{*this};
	}
	
	void BoxBorder::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto& line: objects) {
			for(auto& object: line) {
				object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
			}
		}
	}
	
	bool DecodePointer<BoxBorder>::decodePointer(const YAML::Node& node, BoxBorder*& boxWithBorder) {
		auto objects(node["objects"].as<std::vector<std::vector<BoxPtr<IScalable> > > >());
		auto minSize{convDef(node["min-size"], sf::Vector2f{})};
		
		if(node["bounds-vertical"] && node["bounds-horizontal"]) {
			boxWithBorder = new BoxBorder{
				std::move(objects),
				node["bounds-vertical"].as<std::vector<float> >(),
				node["bounds-horizontal"].as<std::vector<float> >(),
				minSize
			};
		} else {
			boxWithBorder = new BoxBorder{
				std::move(objects),
				minSize
			};
		}
		return true;
	}
}