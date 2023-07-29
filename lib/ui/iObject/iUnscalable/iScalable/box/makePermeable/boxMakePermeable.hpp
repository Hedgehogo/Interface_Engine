#pragma once

#include "../box.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"

namespace ui {
	class BoxMakePermeable : public Box, public ILayoutWithObject {
	public:
		BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f minSize);
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxMakePermeable* copy() override;
		
	protected:
		BoxPtr<IScalable> object;
	};
	
	template<>
	struct DecodePointer<BoxMakePermeable> {
		static bool decodePointer(const YAML::Node& node, BoxMakePermeable*& boxMakePermeable);
	};
}