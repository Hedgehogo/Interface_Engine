#include "valveWithISbool.hpp"

namespace ui {
	ValveWithISbool::ValveWithISbool(PISbool value) : value(value) {}

	bool ValveWithISbool::operator()() {
		return value->getValue();
	}

	ValveWithISbool *ValveWithISbool::copy() {
		return new ValveWithISbool{value};
	}

	bool convertPointer(const YAML::Node &node, ValveWithISbool *&valveWithISbool) {
		valveWithISbool = new ValveWithISbool{
			Buffer::get<ISbool>(node["value"])
		};

		return true;
	}
} // ui