#pragma once

#include "../Box.hpp"
#include "../../IUninteractive/IUninteractive.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"

namespace ie {
	class BoxConstBezel : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> bezel;
			float thickness;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f minSize = {});
			
			BoxConstBezel* make(InitInfo initInfo) override;
		};
		
		BoxConstBezel(Make&& make, InitInfo initInfo);
		
		BoxConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxConstBezel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IUninteractive> bezel;
		BoxPtr<IScalable> object;
		float thickness;
	};
	
	template<>
	struct DecodePointer<BoxConstBezel> {
		static bool decodePointer(const YAML::Node& node, BoxConstBezel*& boxWithConstBezel);
	};
}