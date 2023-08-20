#include "changeObjectEvent.hpp"
#include "../../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	void ChangeObjectEvent::startPressed() {
	}
	
	void ChangeObjectEvent::stopPressed() {
		value->setValue(index);
	}
	
	void ChangeObjectEvent::whilePressed() {
	}
	
	void ChangeObjectEvent::whileNotPressed() {
	}
	
	ChangeObjectEvent::ChangeObjectEvent(std::shared_ptr<SValue<uint>> value, uint index) : index(index), value(value) {
	}
	
	ChangeObjectEvent* ChangeObjectEvent::copy() {
		return new ChangeObjectEvent{*this};
	}
	
	bool DecodePointer<ChangeObjectEvent>::decodePointer(const YAML::Node& node, ChangeObjectEvent*& changeObjectEvent) {
		changeObjectEvent = new ChangeObjectEvent{
			Buffer::get<SValue<uint>>(node["value"]),
			convDef(node["index"], 0u)
		};
		return true;
	}
}