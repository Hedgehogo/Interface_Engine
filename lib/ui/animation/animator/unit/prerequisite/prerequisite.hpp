#pragma once
#include "../iAnimatorUnit.hpp"
#include "velves/iValve.hpp"

namespace ui {
	class Prerequisite : public IAnimatorUnit{
	protected:
		std::vector<IAnimatorUnit*> nextTrueBuf;
		std::vector<IAnimatorUnit*> nextFalseBuf;
		std::vector<IAnimatorUnit*> nextTrue;
		std::vector<IAnimatorUnit*> nextFalse;
		IValve *valve;
	public:
		Prerequisite(IValve *valve, std::vector<IAnimatorUnit *> nextTrue, std::vector<IAnimatorUnit *> nextFalse);

	public:
		void restart() override;

		std::vector<IAnimatorUnit *> update(float time) override;

		void addNextTrue(IAnimatorUnit *unit);

		void addNextFalse(IAnimatorUnit *unit);

		IAnimatorUnit *copy() override;

		~Prerequisite();
	};

	bool convertPointer(const YAML::Node &node, Prerequisite *&prerequisite);
}
