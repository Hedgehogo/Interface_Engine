#pragma once

#include "../../boxWithChangeableObjects.hpp"
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
		WhileChangingObjectsEvent(BoxWithChangeableObjects *objects = nullptr, int offset = 1 );

		WhileChangingObjectsEvent* copy() override;
	};
	
	
	template<>
	struct DecodePointer<WhileChangingObjectsEvent> {
		static bool decodePointer(const YAML::Node &node, WhileChangingObjectsEvent *&whileChangingObjectsEvent);
	};
}
