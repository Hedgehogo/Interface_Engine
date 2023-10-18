#pragma once

#include "IE/Animation/Animator/IAnimatorUnit/IAnimatorUnit.hpp"

class TestAnimatorUnit : public ie::IAnimatorUnit{
	struct Processed{
		struct Update{
			unsigned long long time{0};
			float time_parameter;
		};
		struct SetNextUnits{
			unsigned long long time{0};
			std::vector<IAnimatorUnit *> next_units;
		};
		struct AddNextUnits{
			unsigned long long time{0};
			IAnimatorUnit *next_unit;
		};

		std::vector<unsigned long long> restart;
		std::vector<Update> update;
		std::vector<SetNextUnits> set_next_units;
		std::vector<AddNextUnits> add_next_units;
		std::vector<unsigned long long> copy;
	};

protected:
	Processed processed;
	std::vector<IAnimatorUnit *> update_result;

public:
	explicit TestAnimatorUnit(std::vector<IAnimatorUnit *> update_result = {});

	Processed get_processed();

	void restart() override;

	std::vector<IAnimatorUnit *> update(float time) override;

	void set_next_units(std::vector<IAnimatorUnit *> next_units);

	void add_next_units(IAnimatorUnit *next_unit);

	TestAnimatorUnit * copy() override;
};