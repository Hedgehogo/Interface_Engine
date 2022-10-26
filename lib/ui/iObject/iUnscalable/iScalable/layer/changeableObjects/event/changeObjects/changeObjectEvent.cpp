#include "changeObjectEvent.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui
{
	void ChangeObjectEvent::startPressed() {}

	void ChangeObjectEvent::stopPressed() {
		value->setValue(index);
	}

	void ChangeObjectEvent::whilePressed() {}

	void ChangeObjectEvent::whileNotPressed() {}

	ChangeObjectEvent::ChangeObjectEvent(std::shared_ptr<SValue<uint>> value, uint index) : value( value), index( index) {}

	ChangeObjectEvent *ChangeObjectEvent::copy()
	{
		return new ChangeObjectEvent { value, index };
	}

	bool convertPointer(const YAML::Node &node, ChangeObjectEvent *&changeObjectEvent)
	{
		uint index {0};
		std::shared_ptr<SValue<uint>> value = Buffer::get<SValue<uint>>(node["value"]);

		if (node["index"]) node["index"] >> index;

		{ changeObjectEvent = new ChangeObjectEvent{ value, index }; return true; }
	}
} // ui