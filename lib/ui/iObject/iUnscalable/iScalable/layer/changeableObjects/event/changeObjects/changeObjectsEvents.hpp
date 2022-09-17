#pragma once

#include "../../LayerWithChangeableObjects.hpp"
#include "../changeableObjectsEvent.hpp"

namespace ui
{
	class ChangeObjectsEvent : public ChangeableObjectsEvent
	{
	protected:
		uint index;

		void startPressed() override;
		void stopPressed() override;
		void whilePressed() override;
		void whileNotPressed() override;
	public:
		ChangeObjectsEvent(uint index, LayerWithChangeableObjects *objects = nullptr );

		ChangeObjectsEvent* copy() override;

		static ChangeObjectsEvent* createFromYaml(const YAML::Node &node);
	};
} // ui
