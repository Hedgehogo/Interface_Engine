#include <iostream>

namespace ie {
	template<typename T>
	void detail::AnimatorUnitMatch::Option<T>::add_next_unit(IAnimatorUnit* unit) {
		next.emplace_back(unit);
	}
	
	template<typename T>
	detail::AnimatorUnitMatch::Option<T> detail::AnimatorUnitMatch::Option<T>::copy() {
		std::vector<IAnimatorUnit*> copy_next{next.size()};
		for(size_t i = 0; i < next.size(); ++i) {
			copy_next[i] = next[i]->copy();
		}
		return Option{example, comparison, copy_next};
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
	void AnimatorUnitMatch<T>::add_next(size_t i, IAnimatorUnit* unit) {
		options[i].next.emplace_back(unit);
	}
	
	template<typename T>
	void AnimatorUnitMatch<T>::set_speed(PSfloat speed) {
		for(auto& option: options) {
			for(auto& animator_unit: option.next) {
				animator_unit->set_speed(speed);
			}
		}
	}
	
	template<typename T>
	void AnimatorUnitMatch<T>::restart() {
		for(auto& option: options) {
			for(auto& animator_unit: option.next) {
				animator_unit->restart();
			}
		}
	}
	
	template<typename T>
	std::vector<IAnimatorUnit*> AnimatorUnitMatch<T>::update(float) {
		for(auto& option: options) {
			if(option.comparison(value->get_value(), option.example)) {
				return option.next;
			}
		}
		return {this};
	}
	
	template<typename T>
	AnimatorUnitMatch<T>* AnimatorUnitMatch<T>::copy() {
		std::vector<Option> copy_options{options.size()};
		for(size_t i = 0; i < options.size(); ++i) {
			copy_options[i] = options[i].copy();
		}
		
		return new AnimatorUnitMatch<T>{copy_options, value};
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
		auto condition_str{node["condition"].as<std::string>()};
		
		if(condition_str == "equals") {
			condition = [](T a, T b) {
				return a == b;
			};
		} else if(condition_str == "not-equals") {
			condition = [](T a, T b) {
				return a != b;
			};
		} else if(condition_str == "greater") {
			condition = [](T a, T b) {
				return a > b;
			};
		} else if(condition_str == "less") {
			condition = [](T a, T b) {
				return a < b;
			};
		} else if(condition_str == "greater-or-equals") {
			condition = [](T a, T b) {
				return a >= b;
			};
		} else if(condition_str == "less-or-equals") {
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
	void add_next_animator_unit_for_mach(const YAML::Node& node, int i, AnimatorUnitMatch<T>*& animator_unit_match) {
		add_next_animator_unit(node, [=](IAnimatorUnit* unit) {
			animator_unit_match->add_next(i, unit);
		});
		
		add_next_animator_unit(node["options"][i], [=](IAnimatorUnit* unit) {
			animator_unit_match->add_next(i, unit);
		});
	}
	
	template<typename T>
	bool DecodePointer<AnimatorUnitMatch<T>>::decode_pointer(const YAML::Node& node, AnimatorUnitMatch<T>*& animator_unit_match) {
		std::vector<typename AnimatorUnitMatch<T>::Option> options;
		
		if(node["options"]) {
			options = node["options"].as<std::vector<typename AnimatorUnitMatch<T>::Option>>();
		} else {
			options = std::vector{node["option"].as<typename AnimatorUnitMatch<T>::Option>()};
		}
		
		animator_unit_match = new AnimatorUnitMatch<T>{
			options,
			Buffer::get<SValue<T>>(node["value"])
		};
		
		if(node["options"]) {
			for(size_t i = 0; i < node["options"].size(); ++i) {
				add_next_animator_unit_for_mach(node, i, animator_unit_match);
			}
		} else {
			add_next_animator_unit_for_mach(node, 0, animator_unit_match);
		}
		
		add_unit_in_buffer(node, animator_unit_match);
		return true;
	}
}