#include "Prerequisite.hpp"

namespace ie {
	Prerequisite::Prerequisite(PISbool valve, std::vector<IAnimatorUnit*> next_true, std::vector<IAnimatorUnit*> next_false) :
		next_true_buf(next_true), next_false_buf(next_false), next_true(next_true), next_false(next_false), valve(valve) {
		for(auto& unit: this->next_true) {
			if(!unit)
				unit = this;
		}
		
		for(auto& unit: this->next_false) {
			if(!unit)
				unit = this;
		}
	}
	
	void Prerequisite::set_speed(PSfloat speed) {
		for(auto& unit: this->next_true) {
			if(unit != this)
				unit->set_speed(speed);
		}
		
		for(auto& unit: this->next_false) {
			if(unit != this)
				unit->set_speed(speed);
		}
	}
	
	void Prerequisite::restart() {
		for(auto& unit: this->next_true) {
			unit->restart();
		}
		
		for(auto& unit: this->next_false) {
			unit->restart();
		}
	}
	
	std::vector<IAnimatorUnit*> Prerequisite::update(float) {
		return valve->get_value() ? next_true : next_false;
	}
	
	void Prerequisite::add_next_true(IAnimatorUnit* unit) {
		next_true.push_back(unit);
	}
	
	void Prerequisite::add_next_false(IAnimatorUnit* unit) {
		next_false.push_back(unit);
	}
	
	IAnimatorUnit* Prerequisite::copy() {
		std::vector<IAnimatorUnit*> copy_next_true{next_true_buf.size()};
		
		for(size_t i = 0; i < next_true_buf.size(); ++i) {
			copy_next_true[i] = next_true_buf[i]->copy();
		}
		
		std::vector<IAnimatorUnit*> copy_next_false{next_false_buf.size()};
		
		for(size_t i = 0; i < next_false_buf.size(); ++i) {
			copy_next_false[i] = next_false_buf[i]->copy();
		}
		
		return new Prerequisite{valve, copy_next_true, copy_next_false};
	}
	
	Prerequisite::~Prerequisite() {
		for(auto item: next_true_buf) {
			delete item;
		}
		
		for(auto item: next_false_buf) {
			delete item;
		}
	}
	
	
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
}
