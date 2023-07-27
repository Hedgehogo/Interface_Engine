#include <iostream>

namespace ui {
	template<typename T>
	void detail::AnimatorUnitMatch::Option<T>::addNextUnit(IAnimatorUnit* unit) {
		next.emplace_back(unit);
	}
	
	template<typename T>
	detail::AnimatorUnitMatch::Option<T> detail::AnimatorUnitMatch::Option<T>::copy() {
		std::vector<IAnimatorUnit*> copyNext{next.size()};
		for(int i = 0; i < next.size(); ++i) {
			copyNext[i] = next[i]->copy();
		}
		return Option{example, comparison, copyNext};
	}
	
	template<typename T>
	AnimatorUnitMatch<T>::AnimatorUnitMatch(std::vector<Option> options, PSValue<T> value) : options(options), value(value) {
		for(auto& option: options) {
			for(auto& unit: option.next) {
				if(!unit)
					unit = this;
			}
		}
	}
	
	template<typename T>
	void AnimatorUnitMatch<T>::addNext(size_t i, IAnimatorUnit* unit) {
		options[i].next.emplace_back(unit);
	}
	
	template<typename T>
	void AnimatorUnitMatch<T>::setSpeed(PSfloat speed) {
		for(auto& option: options) {
			for(auto& animatorUnit: option.next) {
				animatorUnit->setSpeed(speed);
			}
		}
	}
	
	template<typename T>
	void AnimatorUnitMatch<T>::restart() {
		for(auto& option: options) {
			for(auto& animatorUnit: option.next) {
				animatorUnit->restart();
			}
		}
	}
	
	template<typename T>
	std::vector<IAnimatorUnit*> AnimatorUnitMatch<T>::update(float time) {
		for(auto& option: options) {
			if(option.comparison(value->getValue(), option.example)) {
				return option.next;
			}
		}
		return {this};
	}
	
	template<typename T>
	AnimatorUnitMatch<T>* AnimatorUnitMatch<T>::copy() {
		std::vector<Option> copyOptions{options.size()};
		for(int i = 0; i < options.size(); ++i) {
			copyOptions[i] = options[i].copy();
		}
		
		return new AnimatorUnitMatch<T>{copyOptions, value};
	}
	
	
	template<typename T>
	bool Decode<detail::AnimatorUnitMatch::Option<T>>::decode(const YAML::Node& node, detail::AnimatorUnitMatch::Option<T>& option) {
		std::vector<IAnimatorUnit*> nexts;
		
		if(node["next"]) {
			if(!node["next"].IsScalar())
				nexts = {node["next"].as<IAnimatorUnit*>()};
			else if(node["next"].as<std::string>() == "this")
				nexts = {nullptr};
		} else if(node["nexts"]) {
			for(auto& unit: node["nexts"]) {
				if(!unit.IsScalar())
					nexts.push_back(unit.as<IAnimatorUnit*>());
				else if(unit.as<std::string>() == "this")
					nexts.push_back(nullptr);
			}
		}
		
		std::function<bool(T, T)> condition;
		auto conditionStr{node["condition"].as<std::string>()};
		
		if(conditionStr == "equals") {
			condition = [](T a, T b) {
				return a == b;
			};
		} else if(conditionStr == "not-equals") {
			condition = [](T a, T b) {
				return a != b;
			};
		} else if(conditionStr == "greater") {
			condition = [](T a, T b) {
				return a > b;
			};
		} else if(conditionStr == "less") {
			condition = [](T a, T b) {
				return a < b;
			};
		} else if(conditionStr == "greater-or-equals") {
			condition = [](T a, T b) {
				return a >= b;
			};
		} else if(conditionStr == "less-or-equals") {
			condition = [](T a, T b) {
				return a <= b;
			};
		}
		
		option = typename AnimatorUnitMatch<T>::Option{
			node["example"].as<T>(),
			condition,
			nexts
		};
		return true;
	}
	
	template<typename T>
	void addNextAnimatorUnitForMach(const YAML::Node& node, int i, AnimatorUnitMatch<T>*& animatorUnitMatch) {
		addNextAnimatorUnit(node, [=](IAnimatorUnit* unit) {
			animatorUnitMatch->addNext(i, unit);
		});
		
		addNextAnimatorUnit(node["options"][i], [=](IAnimatorUnit* unit) {
			animatorUnitMatch->addNext(i, unit);
		});
	}
	
	template<typename T>
	bool DecodePointer<AnimatorUnitMatch<T>>::decodePointer(const YAML::Node& node, AnimatorUnitMatch<T>*& animatorUnitMatch) {
		std::vector<typename AnimatorUnitMatch<T>::Option> options;
		
		if(node["options"]) {
			options = node["options"].as<std::vector<typename AnimatorUnitMatch<T>::Option>>();
		} else {
			options = std::vector{node["option"].as<typename AnimatorUnitMatch<T>::Option>()};
		}
		
		animatorUnitMatch = new AnimatorUnitMatch<T>{
			options,
			Buffer::get<SValue<T>>(node["value"])
		};
		
		if(node["options"]) {
			for(int i = 0; i < node["options"].size(); ++i) {
				addNextAnimatorUnitForMach(node, i, animatorUnitMatch);
			}
		} else {
			addNextAnimatorUnitForMach(node, 0, animatorUnitMatch);
		}
		
		addUnitInBuffer(node, animatorUnitMatch);
		return true;
	}
}