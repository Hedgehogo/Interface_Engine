#pragma once

#include "modules/appendix/yaml-cpp/shared/value/iSValue.hpp"

class TestSValue : public ui::ISValue<float>{
public:
	struct Processed{
		struct AddSetter{
			unsigned long long time;
			const SetterFunc &setter;
		};
		struct setValue{
			unsigned long long time;
			float value;
		};
		std::vector<AddSetter> addSetter;
		std::vector<setValue> setValue;
	};

protected:
	Processed processed;
	float resultGet;

public:
	explicit TestSValue(float resultGet);

	const Processed &getProcessed() const;

	void addSetter(const SetterFunc &setter) override;

	const float &getValue() const override;

	void setValue(const float &value) override;
};