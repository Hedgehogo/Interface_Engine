#pragma once

#include "../box.hpp"
#include "../../interactive/simple/baseInteractive.hpp"
#include "../../../../iLayout/twoObjects/iLayoutWithTwoObjects.hpp"
#include "../../../../../interaction/iInteraction/block/pressed/pressedInteraction.hpp"
#include "interaction/event/movableBorderEvent.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"

namespace ui {
	class BoxWithMovableBorder : public Box, public IInteractive, public IUpdatable, public ILayoutWithTwoObjects {
	public:
		BoxWithMovableBorder(
			BoxPtr<IScalable>&& firstObject,
			BoxPtr<IScalable>&& secondObject,
			bool isHorizontalBorder,
			PSCoefficient borderValue,
			int borderInteractionSize = 5,
			sf::Vector2f minSize = {}
		);
		
		void init(InitInfo initInfo) override;
		
		float getBorderValue();
		
		void setBorderValue(float borderValue);
		
		float getBorderValueNow();
		
		int getBorderInteractionSize();
		
		void setBorderInteractionSize(int size);
		
		bool getIsHorizontalBorder();
		
		bool isInBorder(sf::Vector2f pointPosition);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxWithMovableBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BaseInteractiveData interactive;
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
		PressedInteraction pressedInteraction;
		float borderValueNow;
		PSCoefficient borderValue;
		int borderInteractionSize;
		bool isHorizontalBorder;
	};
	
	template<>
	struct DecodePointer<BoxWithMovableBorder> {
		static bool decodePointer(const YAML::Node& node, BoxWithMovableBorder*& boxWithMovableBorder);
	};
	
	using BoxWMovableB = BoxWithMovableBorder;
	using BWMB = BoxWithMovableBorder;
}