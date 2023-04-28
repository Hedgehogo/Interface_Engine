#pragma once

#include "../iAnimatorUnit.hpp"

namespace ui {
	
	namespace detail::AnimatorUnitMatch {
		template<typename T>
		struct Option {
			T example;
			std::function<bool(T, T)> comparison;
			std::vector<IAnimatorUnit*> next;
			
			void addNextUnit(IAnimatorUnit* unit);
			
			Option copy();
		};
	}
	
	template<typename T>
	class AnimatorUnitMatch : public IAnimatorUnit {
	public:
		using Option = detail::AnimatorUnitMatch::Option<T>;
		
	protected:
		std::vector<Option> options;
		PSValue<T> value;
	
	public:
		AnimatorUnitMatch(std::vector<Option> options, PSValue<T> value);
		
		void addNext(size_t i, IAnimatorUnit* unit);
		
		
		void setSpeed(PSfloat speed) override;
		
		void restart() override;
		
		std::vector<IAnimatorUnit*> update(float time) override;
		
		AnimatorUnitMatch<T>* copy() override;
	};
	
	template<typename T>
	bool convert(const YAML::Node& node, detail::AnimatorUnitMatch::Option<T>& option);
	
	template<typename T>
	struct Decode<detail::AnimatorUnitMatch::Option<T>> {
		static bool decode(const YAML::Node& node, detail::AnimatorUnitMatch::Option<T>& option);
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node& node, AnimatorUnitMatch<T>*& animatorUnitMatch);
	
	template<typename T>
	struct DecodePointer<AnimatorUnitMatch<T>> {
		static bool decodePointer(const YAML::Node& node, AnimatorUnitMatch<T>*& animatorUnitMatch);
	};
	
	using AnimatorUnitMatchFloat = AnimatorUnitMatch<float>;
}

#include "animatorUnitMatch.inl"