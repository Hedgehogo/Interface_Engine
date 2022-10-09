#include "changeObjectEvent.hpp"

namespace ui
{
	void ChangeObjectEvent::startPressed() {}

	void ChangeObjectEvent::stopPressed() {
		value->setValue(index);
	}

	void ChangeObjectEvent::whilePressed() {}

	void ChangeObjectEvent::whileNotPressed() {}

	ChangeObjectEvent::ChangeObjectEvent(std::shared_ptr<WithValue<uint>> value, uint index) : value( value), index( index) {}

	ChangeObjectEvent *ChangeObjectEvent::copy()
	{
		return new ChangeObjectEvent { value, index };
	}

	ChangeObjectEvent *ChangeObjectEvent::createFromYaml(const YAML::Node &node)
	{
		uint index {0};
		std::shared_ptr<WithValue<uint>> value = Buffer::get<WithValue<uint>>(node["value"]);

		if (node["index"]) node["index"] >> index;

		return new ChangeObjectEvent { value, index };
	}
} // ui