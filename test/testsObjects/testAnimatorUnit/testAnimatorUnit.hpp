#pragma once

#include "IE/Animation/Animator/IAnimatorUnit/IAnimatorUnit.hpp"

class TestAnimatorUnit : public ie::IAnimatorUnit{
	struct Processed{
		struct Update{
			unsigned long long time{0};
			float timeParameter;
		};
		struct SetNextUnits{
			unsigned long long time{0};
			std::vector<IAnimatorUnit *> nextUnits;
		};
		struct AddNextUnits{
			unsigned long long time{0};
			IAnimatorUnit *nextUnit;
		};

		std::vector<unsigned long long> restart;
		std::vector<Update> update;
		std::vector<SetNextUnits> setNextUnits;
		std::vector<AddNextUnits> addNextUnits;
		std::vector<unsigned long long> copy;
	};

protected:
	Processed processed;
	std::vector<IAnimatorUnit *> updateResult;

public:
	explicit TestAnimatorUnit(std::vector<IAnimatorUnit *> updateResult = {});

	Processed getProcessed();

	void restart() override;

	std::vector<IAnimatorUnit *> update(float time) override;

	void setNextUnits(std::vector<IAnimatorUnit *> nextUnits);

	void addNextUnits(IAnimatorUnit *nextUnit);

	TestAnimatorUnit * copy() override;
};