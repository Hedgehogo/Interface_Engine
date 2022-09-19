#pragma once

#include "../../LayerWithChangeableObjects.hpp"
#include "../changeableObjectsEvent.hpp"

namespace ui
{
	class ChangeObjectEvent : public ChangeableObjectsEvent
	{
	protected:
		uint index;
		std::shared_ptr<WithValue<uint>> value;

		void startPressed() override;
		void stopPressed() override;
		void whilePressed() override;
		void whileNotPressed() override;
	public:
		ChangeObjectEvent(std::shared_ptr<WithValue<uint>> value, uint index);

		ChangeObjectEvent* copy() override;

		static ChangeObjectEvent* createFromYaml(const YAML::Node &node);
	};
} // ui
