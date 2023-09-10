#pragma once

#include "../IComponent/IUnscalable/IScalable/Box/Box.hpp"
#include "IE/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"

namespace ie {
	class BoxDebug : public Box, public virtual IComponentObject, public virtual IDrawable {
	public:
		struct Make : public Box::Make, public virtual IComponentObject::Make {
			BoxPtr<IScalable::Make> object;
			
			Make(BoxPtr<IScalable::Make>&& object);
			
			BoxDebug* make(InitInfo initInfo) override;
		};
		
		BoxDebug(Make&& make, InitInfo initInfo);
		
		BoxDebug(BoxPtr<IScalable>&& object);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxDebug* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> object;
		sf::RenderTarget* renderTarget;
		bool active;
		bool drawn;
	};
	
	template<>
	struct DecodePointer<BoxDebug> {
		static bool decodePointer(const YAML::Node& node, BoxDebug*& boxDebug);
	};
}
