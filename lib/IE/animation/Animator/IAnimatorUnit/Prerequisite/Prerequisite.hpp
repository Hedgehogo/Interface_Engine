#pragma once

#include "../IAnimatorUnit.hpp"

namespace ie {
	class Prerequisite : public virtual IAnimatorUnit {
	public:
		Prerequisite(PISbool valve, std::vector<IAnimatorUnit*> nextTrue, std::vector<IAnimatorUnit*> nextFalse);
		
		void setSpeed(PSfloat speed) override;
		
		void restart() override;
		
		std::vector<IAnimatorUnit*> update(float) override;
		
		void addNextTrue(IAnimatorUnit* unit);
		
		void addNextFalse(IAnimatorUnit* unit);
		
		IAnimatorUnit* copy() override;
		
		~Prerequisite();
	
	protected:
		std::vector<IAnimatorUnit*> nextTrueBuf;
		std::vector<IAnimatorUnit*> nextFalseBuf;
		std::vector<IAnimatorUnit*> nextTrue;
		std::vector<IAnimatorUnit*> nextFalse;
		PISbool valve;
	};
	
	template<>
	struct DecodePointer<Prerequisite> {
		static bool decodePointer(const YAML::Node& node, Prerequisite*& prerequisite);
	};
}
