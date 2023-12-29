#pragma once

#include "../IAnimatorUnit.hpp"

namespace ie {
	class Prerequisite : public virtual IAnimatorUnit {
	public:
		Prerequisite(PISbool valve, std::vector<IAnimatorUnit*> next_true, std::vector<IAnimatorUnit*> next_false);
		
		void set_speed(PSfloat speed) override;
		
		void restart() override;
		
		std::vector<IAnimatorUnit*> update(float) override;
		
		void add_next_true(IAnimatorUnit* unit);
		
		void add_next_false(IAnimatorUnit* unit);
		
		IAnimatorUnit* copy() override;
		
		~Prerequisite();
	
	protected:
		std::vector<IAnimatorUnit*> next_true_buf_;
		std::vector<IAnimatorUnit*> next_false_buf_;
		std::vector<IAnimatorUnit*> next_true_;
		std::vector<IAnimatorUnit*> next_false_;
		PISbool valve_;
	};
	
	template<>
	struct DecodePointer<Prerequisite> {
		static bool decode_pointer(const YAML::Node& node, Prerequisite*& prerequisite);
	};
}
