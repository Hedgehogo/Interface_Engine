#pragma once

#include "../iValve.hpp"
#include "modules/appendix/yaml-cpp/shared/value/iSValue.hpp"
#include "modules/appendix/yaml-cpp/buffer/buffer.hpp"

namespace ui {
	class ValveWithISbool : public IValve{
	protected:
		PISbool value;

	public:
		explicit ValveWithISbool(PISbool value);

		bool operator()() override;

		ValveWithISbool *copy() override;
	};

	bool convertPointer(const YAML::Node &node, ValveWithISbool *&valveWithISbool);
}