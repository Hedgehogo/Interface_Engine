#pragma once

#include "../IAnimatorUnit.hpp"

namespace ie {
	namespace detail::AnimatorUnitMatch {
		template<typename T>
		struct Option {
			T example;
			std::function<bool(T, T)> comparison;
			std::vector<IAnimatorUnit*> next;
			
			void add_next_unit(IAnimatorUnit* unit);
			
			Option copy();
		};
	}
	
	template<typename T>
	class AnimatorUnitMatch : public virtual IAnimatorUnit {
	public:
		using Option = detail::AnimatorUnitMatch::Option<T>;
	
		AnimatorUnitMatch(std::vector<Option> options, PSValue<T> value);
		
		void add_next(size_t i, IAnimatorUnit* unit);
		
		void set_speed(PSfloat speed) override;
		
		void restart() override;
		
		std::vector<IAnimatorUnit*> update(float) override;
		
		AnimatorUnitMatch<T>* copy() override;
	
	protected:
		std::vector<Option> options_;
		PSValue<T> value_;
	};
	
	/*old_yaml_decode
	template<typename T>
	struct Decode<detail::AnimatorUnitMatch::Option<T> > {
		static bool decode(const YAML::Node& node, detail::AnimatorUnitMatch::Option<T>& option);
	};
	*/
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<AnimatorUnitMatch<T> > {
		static bool decode_pointer(const YAML::Node& node, AnimatorUnitMatch<T>*& animator_unit_match);
	};
	*/
	
	using AnimatorUnitMatchFloat = AnimatorUnitMatch<float>;
}

#include "AnimatorUnitMatch.inl"