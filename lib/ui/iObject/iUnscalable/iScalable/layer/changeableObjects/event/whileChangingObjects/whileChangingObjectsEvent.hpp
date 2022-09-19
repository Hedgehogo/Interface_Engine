#pragma once

#include "../../LayerWithChangeableObjects.hpp"
#include "../changeableObjectsEvent.hpp"

namespace ui
{
	class WhileChangingObjectsEvent : public ChangeableObjectsEvent
	{
	protected:
		int objectsSize;
		std::shared_ptr<WithValue<uint>> index;
		int offset;

		void startPressed() override;
		void stopPressed() override;
		void whilePressed() override;
		void whileNotPressed() override;
	public:
		WhileChangingObjectsEvent(LayerWithChangeableObjects *objects = nullptr, int offset = 1 );

		WhileChangingObjectsEvent* copy() override;

		static WhileChangingObjectsEvent* createFromYaml(const YAML::Node &node);
	};
} // ui
