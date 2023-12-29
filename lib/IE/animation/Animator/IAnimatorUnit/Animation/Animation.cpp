#include "Animation.hpp"

#include <utility>
#include <iostream>

namespace ie {
	Animation::Variable::Variable(PSfloat animation_variable, std::vector<IChangeVariable*> change_variables) : animation_variable(std::move(animation_variable)), change_variables(std::move(change_variables)) {
	}
	
	Animation::Variable Animation::Variable::copy() {
		std::vector<IChangeVariable*> copy_change_variables{change_variables.size()};
		
		for(size_t i = 0; i < copy_change_variables.size(); ++i) {
			copy_change_variables[i] = change_variables[i]->copy();
		}
		
		return {animation_variable, copy_change_variables};
	}
	
	Animation::Animation(std::vector<Variable> animation_variables, PSfloat speed, std::vector<IAnimatorUnit*> next_units) :
		next_units_(next_units), next_units_buff_(next_units), animation_variables_(std::move(animation_variables)), speed_(std::move(speed)) {
		for(auto& unit: this->next_units_) {
			if(!unit)
				unit = this;
		}
		
		restart();
	}
	
	void Animation::set_speed(PSfloat speed) {
		if(!this->speed_)
			this->speed_ = speed;
		
		for(auto& unit: next_units_) {
			if(unit != this)
				unit->set_speed(speed);
		}
	}
	
	void Animation::restart() {
		animation_updatable_variables_.resize(animation_variables_.size());
		
		for(size_t i = 0; i < animation_updatable_variables_.size(); ++i) {
			animation_updatable_variables_[i] = &animation_variables_[i];
		}
		
		for(auto& animation_variable: animation_variables_) {
			animation_variable.active_changer = 0;
			animation_variable.time_start_changer = 0;
		}
	}
	
	std::vector<IAnimatorUnit*> Animation::update(float time) {
		for(size_t i = 0; i < animation_updatable_variables_.size(); ++i) {
			Variable*& animation_variable = animation_updatable_variables_[i];
			
			if(animation_variable->time_start_changer == 0 || time < animation_variable->time_start_changer)
				animation_variable->time_start_changer = time;
			
			float time_from_changer = time - (animation_variable->time_start_changer);
			IChangeVariable* change_variable = animation_variable->change_variables[animation_variable->active_changer];
			
			time_from_changer *= speed_->get_value();
			animation_variable->animation_variable->set_value((*change_variable)(time_from_changer));
			
			if(change_variable->get_size() < time_from_changer) {
				animation_variable->active_changer++;
				if(animation_variable->active_changer == animation_variable->change_variables.size()) {
					animation_updatable_variables_.erase(std::vector<Variable*>::iterator{&animation_variable});
					--i;
					continue;
				}
				animation_variable->time_start_changer = time;
				change_variable = animation_variable->change_variables[animation_variable->active_changer];
			}
		}
		
		if(animation_updatable_variables_.empty()) {
			restart();
			return next_units_;
		}
		
		return {this};
	}
	
	void Animation::set_next_units(std::vector<IAnimatorUnit*> next_units) {
		this->next_units_ = next_units;
	}
	
	void Animation::add_next_units(IAnimatorUnit* next_unit) {
		next_units_.push_back(next_unit);
	}
	
	Animation* Animation::copy() {
		std::vector<IAnimatorUnit*> copy_next_units{next_units_buff_.size()};
		
		for(size_t i = 0; i < next_units_buff_.size(); ++i) {
			copy_next_units[i] = next_units_buff_[i]->copy();
		}
		
		return new Animation{animation_variables_, speed_, copy_next_units};
	}
	
	Animation::~Animation() {
		for(auto& item: next_units_buff_) {
			if(item)
				delete item;
		}
	}
	
	bool Decode<Animation::Variable>::decode(const YAML::Node& node, Animation::Variable& animation_var) {
		animation_var = Animation::Variable{
			Buffer::get<Sfloat>(node["var"]),
			node["change-variable"] ? std::vector<IChangeVariable*>{node["change-variable"].as<IChangeVariable*>()} : node["change-variables"].as<std::vector<IChangeVariable*>>()
		};
		return true;
	}
	
	bool DecodePointer<Animation>::decode_pointer(const YAML::Node& node, Animation*& animation) {
		animation = new Animation{
			node["var"] ? std::vector<Animation::Variable>{node["var"].as<Animation::Variable>()} : node["vars"].as<std::vector<Animation::Variable>>(),
			(node["speed"] ? Buffer::get<Sfloat>(node["speed"]) : PSfloat{nullptr}),
			get_animator_units(node)
		};
		
		add_next_animator_unit(node, [=](IAnimatorUnit* unit) {
			animation->add_next_units(unit);
		});
		
		add_unit_in_buffer(node, animation);
		return true;
	}
}