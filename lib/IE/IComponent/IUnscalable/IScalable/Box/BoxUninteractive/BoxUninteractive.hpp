#pragma once

#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"
#include "../../../../ILayout/ILayoutObject/ILayoutObject.hpp"
#include "../Box.hpp"

namespace ie {
	class BoxUninteractive : public Box, public IUninteractive, public ILayoutObject {
	public:
		struct Make : public Box::Make, public ILayoutObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize = {});
			
			BoxUninteractive* make(InitInfo initInfo) override;
		};
		
		BoxUninteractive(Make&& make, InitInfo initInfo);
		
		BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxUninteractive* copy() override;
		
	protected:
		BoxPtr<IScalable> object;
	};
	
	template<>
	struct DecodePointer<BoxUninteractive> {
		static bool decodePointer(const YAML::Node& node, BoxUninteractive*& boxUninteractive);
	};
}