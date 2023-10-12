#pragma once

#include "IE/Interaction/InteractionStack/InteractionStack.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxBorderHorizontal : public Box, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			std::vector<float> bounds;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f minSize = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f minSize = {});
			
			Make(BoxPtr<IScalable::Make>&& firstObject, BoxPtr<IScalable::Make>&& secondObject, float bound = 0.5f, sf::Vector2f minSize = {});
			
			BoxBorderHorizontal* make(InitInfo initInfo) override;
		};
		
		BoxBorderHorizontal(Make&& make, InitInfo initInfo);
		
		BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f minSize = {});
		
		BoxBorderHorizontal(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f minSize = {});
		
		BoxBorderHorizontal(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, float bound = 0.5f, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		BoxBorderHorizontal* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects;
		std::vector<float> bounds;
	};
	
	template<>
	struct DecodePointer<BoxBorderHorizontal> {
		static bool decodePointer(const YAML::Node& node, BoxBorderHorizontal*& boxWithBorderHorizontal);
	};
}
