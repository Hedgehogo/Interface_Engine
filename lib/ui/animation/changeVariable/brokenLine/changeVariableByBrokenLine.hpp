#pragma once

#include "../iChangeVariable.hpp"

namespace ui {
	class ChangeVariableByBrokenLine : public IChangeVariable{
	public:
		struct Value{
			float value;
			float size = 0;
		};

	protected:
		std::vector<Value> values;
		float size;

	public:
		ChangeVariableByBrokenLine(std::vector<Value> values);

		float getSize() override;

		float operator()(float frame) override;

		IChangeVariable *copy() override;
	};

	template<>
	bool convert(const YAML::Node &node, ChangeVariableByBrokenLine::Value& value);

	bool convertPointer(const YAML::Node &node, ChangeVariableByBrokenLine*& brokenLine);
}
