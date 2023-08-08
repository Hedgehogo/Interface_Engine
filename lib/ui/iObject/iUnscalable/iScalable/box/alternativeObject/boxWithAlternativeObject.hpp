#pragma once

#include "../box.hpp"
#include "../../../../iLayout/twoObjects/iLayoutWithTwoObjects.hpp"

namespace ui {
	class BoxWithAlternativeObject : public Box, public ILayoutWithTwoObjects {
	public:
		struct Make : public Box::Make, public ILayoutWithTwoObjects::Make {
			BoxPtr<IScalable::Make> topObject;
			BoxPtr<IScalable::Make> bottomObject;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& topObject, BoxPtr<IScalable::Make>&& bottomObject, sf::Vector2f minSize = {});
			
			BoxWithAlternativeObject* make(InitInfo initInfo) override;
		};
		
		BoxWithAlternativeObject(Make&& make, InitInfo initInfo);
		
		BoxWithAlternativeObject(BoxPtr<IScalable>&& topObject, BoxPtr<IScalable>&& bottomObject, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxWithAlternativeObject* copy() override;
		
	protected:
		BoxPtr<IScalable> topObject;
		BoxPtr<IScalable> bottomObject;
	};
	
	template<>
	struct DecodePointer<BoxWithAlternativeObject> {
		static bool decodePointer(const YAML::Node& node, BoxWithAlternativeObject*& boxWithAlternativeObject);
	};
	
	using BoxWAObject = BoxWithAlternativeObject;
	using BWAO = BoxWithAlternativeObject;
}
