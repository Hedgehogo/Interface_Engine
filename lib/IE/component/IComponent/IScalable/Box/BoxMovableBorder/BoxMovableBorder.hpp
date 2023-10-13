#pragma once

#include "IE/modules/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "IE/modules/yaml-cpp/shared/value/coefficient/general/sCoefficientValue.hpp"
#include "IE/interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "MovableBorderAction/MovableBorderAction.hpp"
#include "../Box.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxMovableBorder : public Box, public virtual IScalableTwoObjects, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> firstObject;
			BoxPtr<IScalable::Make> secondObject;
			bool isHorizontalBorder;
			PSCoefficient borderValue;
			int borderInteractionSize = 5;
			Key key = Key::MouseLeft;
			sf::Vector2f minSize = {};
			
			Make(
				BoxPtr<IScalable::Make>&& firstObject,
				BoxPtr<IScalable::Make>&& secondObject,
				bool isHorizontalBorder,
				PSCoefficient borderValue,
				int borderInteractionSize = 5,
				Key key = Key::MouseLeft,
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
		BasicInteractiveData<BoxMovableBorder&> interactive;
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