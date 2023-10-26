#pragma once

#include "IAnimatorUnit/IAnimatorUnit.hpp"
#include "IE/modules/yaml-cpp/buffer/Buffer.hpp"

namespace ie {
	class Animator {
	public:
		explicit Animator(std::vector<IAnimatorUnit*> units, PSfloat speed = std::make_shared<Sfloat>(1));
		
		void update(float time);
		
		virtual Animator* copy();
		
		virtual ~Animator();
	
	protected:
		std::vector<IAnimatorUnit*> units_;
		std::vector<IAnimatorUnit*> units_buff_;
	};
	
	template<>
	struct DecodePointer<Animator> {
		static bool decode_pointer(const YAML::Node& node, Animator*& animator);
	};
}