#pragma once

#include "../box.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	class BoxWithBorder : public Box {
	protected:
		std::vector<std::vector<IScalable*>> objects;
		std::vector<float> boundsVertical;
		std::vector<float> boundsHorizontal;
		
		void init(InitInfo initInfo) override;
	
	public:
		BoxWithBorder(std::vector<std::vector<IScalable*>> objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		BoxWithBorder(std::vector<std::vector<IScalable*>> objects, sf::Vector2f minSize = {0, 0});
		
		~BoxWithBorder() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		BoxWithBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithBorder> {
		static bool decodePointer(const YAML::Node& node, BoxWithBorder*& boxWithBorder);
	};
	
	using BoxWBorder = BoxWithBorder;
	using BWB = BoxWithBorder;
}

