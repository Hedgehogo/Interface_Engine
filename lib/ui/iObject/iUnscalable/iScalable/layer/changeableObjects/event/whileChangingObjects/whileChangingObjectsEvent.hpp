#pragma once

#include "../../LayerWithChangeableObjects.hpp"
#include "../changeableObjectsEvent.hpp"
#include "../../../../../../../../modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
	class WhileChangingObjectsEvent : public ChangeableObjectsEvent {
	protected:
		int objectsSize;
		std::shared_ptr<SValue<uint>> index;
		int offset;

		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
	public:
		WhileChangingObjectsEvent(LayerWithChangeableObjects *objects = nullptr, int offset = 1 );

		WhileChangingObjectsEvent* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, WhileChangingObjectsEvent *&whileChangingObjectsEvent);
}
