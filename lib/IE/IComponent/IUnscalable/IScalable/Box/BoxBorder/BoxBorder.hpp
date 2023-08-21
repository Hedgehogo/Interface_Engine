#pragma once

#include "../Box.hpp"
#include "../../../../../Interaction/InteractionStack/InteractionStack.hpp"

namespace ui {
	class BoxBorder : public Box {
	public:
		struct Make : public Box::Make {
			std::vector<std::vector<BoxPtr<IScalable::Make> > > objects;
			std::vector<float> boundsHorizontal;
			std::vector<float> boundsVertical;
			sf::Vector2f minSize = {};
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {});
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f minSize = {});
			
			BoxBorder* make(InitInfo initInfo) override;
		};
		
		BoxBorder(Make&& make, InitInfo initInfo);
		
		BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {});
		
		BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		BoxBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<std::vector<BoxPtr<IScalable> > > objects;
		std::vector<float> boundsHorizontal;
		std::vector<float> boundsVertical;
	};
	
	template<>
	struct DecodePointer<BoxBorder> {
		static bool decodePointer(const YAML::Node& node, BoxBorder*& boxWithBorder);
	};
}

