#pragma once

#include "../box.hpp"
#include "../../../../../Interaction/InteractionStack/InteractionStack.hpp"

namespace ui {
	class BoxWithBorder : public Box {
	public:
		struct Make : public Box::Make {
			std::vector<std::vector<BoxPtr<IScalable::Make> > > objects;
			std::vector<float> boundsHorizontal;
			std::vector<float> boundsVertical;
			sf::Vector2f minSize = {};
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {});
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f minSize = {});
			
			BoxWithBorder* make(InitInfo initInfo) override;
		};
		
		BoxWithBorder(Make&& make, InitInfo initInfo);
		
		BoxWithBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {});
		
		BoxWithBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		BoxWithBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<std::vector<BoxPtr<IScalable> > > objects;
		std::vector<float> boundsHorizontal;
		std::vector<float> boundsVertical;
	};
	
	template<>
	struct DecodePointer<BoxWithBorder> {
		static bool decodePointer(const YAML::Node& node, BoxWithBorder*& boxWithBorder);
	};
	
	using BoxWBorder = BoxWithBorder;
	using BWB = BoxWithBorder;
}

