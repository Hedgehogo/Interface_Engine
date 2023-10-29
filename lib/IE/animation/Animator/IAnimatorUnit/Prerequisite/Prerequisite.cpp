#include "Prerequisite.hpp"

namespace ie {
	Prerequisite::Prerequisite(PISbool valve, std::vector<IAnimatorUnit*> next_true, std::vector<IAnimatorUnit*> next_false) :
		next_true_buf_(next_true), next_false_buf_(next_false), next_true_(next_true), next_false_(next_false), valve_(valve) {
		for(auto& unit: this->next_true_) {
			if(!unit)
				unit = this;
		}
		
		for(auto& unit: this->next_false_) {
			if(!unit)
				unit = this;
		}
	}
	
	void Prerequisite::set_speed(PSfloat speed) {
		for(auto& unit: this->next_true_) {
			if(unit != this)
				unit->set_speed(speed);
		}
		
		for(auto& unit: this->next_false_) {
			if(unit != this)
				unit->set_speed(speed);
		}
	}
	
	void Prerequisite::restart() {
		for(auto& unit: this->next_true_) {
			unit->restart();
		}
		
		for(auto& unit: this->next_false_) {
			unit->restart();
		}
	}
	
	std::vector<IAnimatorUnit*> Prerequisite::update(float) {
		return valve_->get_value() ? next_true_ : next_false_;
	}
	
	void Prerequisite::add_next_true(IAnimatorUnit* unit) {
		next_true_.push_back(unit);
	}
	
	void Prerequisite::add_next_false(IAnimatorUnit* unit) {
		next_false_.push_back(unit);
	}
	
	IAnimatorUnit* Prerequisite::copy() {
		std::vector<IAnimatorUnit*> copy_next_true{next_true_buf_.size()};
		
		for(size_t i = 0; i < next_true_buf_.size(); ++i) {
			copy_next_true[i] = next_true_buf_[i]->copy();
		}
		
		std::vector<IAnimatorUnit*> copy_next_false{next_false_buf_.size()};
		
		for(size_t i = 0; i < next_false_buf_.size(); ++i) {
			copy_next_false[i] = next_false_buf_[i]->copy();
		}
		
		return new Prerequisite{valve_, copy_next_true, copy_next_false};
	}
	
	Prerequisite::~Prerequisite() {
		for(auto item: next_true_buf_) {
			delete item;
		}
		
		for(auto item: next_false_buf_) {
			delete item;
		}
	}
	
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<Prerequisite>::decode_pointer(const YAML::Node& node, Prerequisite*& prerequisite) {
		prerequisite = new Prerequisite{
			Buffer::get<ISbool>(node["valve"]),
			get_animator_units(node, "next-true"),
			get_animator_units(node, "next-false")
		};
		
		add_next_animator_unit(node, [=](IAnimatorUnit* unit) {
			prerequisite->add_next_true(unit);
		}, "next-true");
		
		add_next_animator_unit(node, [=](IAnimatorUnit* unit) {
			prerequisite->add_next_false(unit);
		}, "next-false");
		
		add_unit_in_buffer(node, prerequisite);
		return true;

	}
	*/
}
