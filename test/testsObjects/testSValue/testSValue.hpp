#pragma once

#include "IE/Modules/yaml-cpp/shared/ISValue/ISValue.hpp"

class TestSValue : public ie::ISValue<float>{
public:
	struct Processed{
		struct AddSetter{
			unsigned long long time;
			const SetterFunc &setter;
		};
		struct set_value{
			unsigned long long time;
			float value;
		};
		std::vector<AddSetter> add_setter;
		std::vector<set_value> set_value;
	};

protected:
	Processed processed;
	float result_get;

public:
	explicit TestSValue(float result_get);

	const Processed &get_processed() const;

	void add_setter(const SetterFunc &setter) override;

	const float &get_value() const override;

	void set_value(const float &value) override;
};
