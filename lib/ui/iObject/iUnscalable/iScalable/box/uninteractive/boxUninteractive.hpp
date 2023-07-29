#pragma once

#include "../../uninteractive/uninteractive.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../box.hpp"

namespace ui {
	class BoxUninteractive : public IUninteractive, public ILayoutWithObject, public Box {
	public:
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