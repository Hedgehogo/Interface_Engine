#pragma once

#include "../Box.hpp"
#include "../../IInteractive/BaseInteractive/BaseInteractive.hpp"
#include "../../../../ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"
#include "../../../../../Interaction/IInteraction/IBlockInteraction/PressedInteraction/PressedInteraction.hpp"
#include "MovableBorderEvent/MovableBorderEvent.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "modules/appendix/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"

namespace ui {
	class BoxMovableBorder : public Box, public IInteractive, public IUpdatable, public ILayoutTwoObjects {
	public:
		struct Make : public Box::Make, public ILayoutTwoObjects::Make {
			BoxPtr<IScalable::Make> firstObject;
			BoxPtr<IScalable::Make> secondObject;
			bool isHorizontalBorder;
			PSCoefficient borderValue;
			int borderInteractionSize = 5;
			Key key = Key::mouseLeft;
			sf::Vector2f minSize = {};
			
			Make(
				BoxPtr<IScalable::Make>&& firstObject,
				BoxPtr<IScalable::Make>&& secondObject,
				bool isHorizontalBorder,
				PSCoefficient borderValue,
				int borderInteractionSize = 5,
				Key key = Key::mouseLeft,
				sf::Vector2f minSize = {}
			);
			
			BoxMovableBorder* make(InitInfo initInfo) override;
		};
		
		BoxMovableBorder(Make&& make, InitInfo initInfo);
		
		BoxMovableBorder(
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
		
		BoxMovableBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		PressedInteraction pressedInteraction;
		BaseInteractiveData interactive;
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
		PSCoefficient borderValue;
		float borderValueNow;
		int borderInteractionSize;
		bool isHorizontalBorder;
	};
	
	template<>
	struct DecodePointer<BoxMovableBorder> {
		static bool decodePointer(const YAML::Node& node, BoxMovableBorder*& boxWithMovableBorder);
	};
}