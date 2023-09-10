#pragma once

#include "../Box.hpp"
#include "IE/IComponent/IComponentLayout/IComponentObjectsArray/IComponentObjectsArray.hpp"
#include "../../../../../Interaction/InteractionStack/InteractionStack.hpp"
#include "../../../../../Interaction/InteractionManager/InteractionManager.hpp"

namespace ie {
	class BoxBorderVertical : public Box, public virtual IComponentObjectsArray {
	public:
		struct Make : public virtual Box::Make, public virtual IComponentObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			std::vector<float> bounds;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f minSize = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f minSize = {});
			
			Make(BoxPtr<IScalable::Make>&& firstObject, BoxPtr<IScalable::Make>&& secondObject, float bound = 0.5f, sf::Vector2f minSize = {});
			
			BoxBorderVertical* make(InitInfo initInfo) override;
		};
		
		BoxBorderVertical(Make&& make, InitInfo initInfo);
		
		BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f minSize = {0, 0});
		
		BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f minSize = {0, 0});
		
		BoxBorderVertical(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, float bound = 0.5f, sf::Vector2f minSize = {0, 0});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		BoxBorderVertical* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects;
		std::vector<float> bounds;
	};
	
	template<>
	struct DecodePointer<BoxBorderVertical> {
		static bool decodePointer(const YAML::Node& node, BoxBorderVertical*& boxWithBorderVertical);
	};
}
