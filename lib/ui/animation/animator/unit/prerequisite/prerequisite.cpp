#include "prerequisite.hpp"

namespace ui {
	Prerequisite::Prerequisite(IValve *valve, std::vector<IAnimatorUnit *> nextTrue, std::vector<IAnimatorUnit *> nextFalse) :
		nextTrue(nextTrue), nextFalse(nextFalse), valve(valve), nextTrueBuf(nextTrue), nextFalseBuf(nextFalse) {
		for (auto &unit: this->nextTrue){
			if(!unit) unit = this;
		}

		for (auto &unit: this->nextFalse){
			if(!unit) unit = this;
		}
	}

	void Prerequisite::restart() {}

	std::vector<IAnimatorUnit *> Prerequisite::update(float time) {
		return (*valve)() ? nextTrue : nextFalse;
	}

	void Prerequisite::addNextTrue(IAnimatorUnit *unit) {
		nextTrue.push_back(unit);
	}

	void Prerequisite::addNextFalse(IAnimatorUnit *unit) {
		nextFalse.push_back(unit);
	}

	IAnimatorUnit *Prerequisite::copy() {

		std::vector<IAnimatorUnit*> copyNextTrue{nextTrueBuf.size()};

		for (size_t i = 0; i < nextTrueBuf.size(); ++i) {
			copyNextTrue[i] = nextTrueBuf[i]->copy();
		}

		std::vector<IAnimatorUnit*> copyNextFalse{nextFalseBuf.size()};

		for (size_t i = 0; i < nextFalseBuf.size(); ++i) {
			copyNextFalse[i] = nextFalseBuf[i]->copy();
		}

		return new Prerequisite{valve->copy(), copyNextTrue, copyNextFalse};
	}

	Prerequisite::~Prerequisite() {
		for (auto item: nextTrueBuf){
			if (item) delete item;
		}

		for (auto item: nextFalseBuf){
			if (item) delete item;
		}

		delete valve;
	}


	bool convertPointer(const YAML::Node &node, Prerequisite *&prerequisite){
		std::vector<IAnimatorUnit*> nextTrue{};

		if(node["next-true"]){
			if(!node["next-true"].IsScalar())
				nextTrue = {node["next-true"].as<IAnimatorUnit *>()};
			else if (node["next-true"].as<std::string>() == "this")
				nextTrue = {nullptr};
		} else if(node["next-trues"]){
			for (auto& unit : node["next-trues"]){
				if(!unit.IsScalar())
					nextTrue.push_back(unit.as<IAnimatorUnit*>());
				else if (unit.as<std::string>() == "this")
					nextTrue.push_back(nullptr);
			}
		}

		std::vector<IAnimatorUnit*> nextFalse{};

		if(node["next-false"]){
			if(!node["next-false"].IsScalar())
				nextFalse = {node["next-false"].as<IAnimatorUnit *>()};
			else if (node["next-false"].as<std::string>() == "this")
				nextFalse = {nullptr};
		} else if(node["next-falses"]){
			for (auto& unit : node["next-falses"]){
				if(!unit.IsScalar())
					nextFalse.push_back(unit.as<IAnimatorUnit*>());
				else if (unit.as<std::string>() == "this")
					nextFalse.push_back(nullptr);
			}
		}

		prerequisite = new Prerequisite{
			node["valve"].as<IValve *>(),
			nextTrue,
			nextFalse
		};

		if (node["next-true"] && node["next-true"].IsScalar() && node["next-true"].as<std::string>() != "this") {
			animatorUnitRequest[node["next-true"].as<std::string>()].push_back([=](IAnimatorUnit *unit){prerequisite->addNextTrue(unit);});
		} else if(node["next-trues"]){
			for (auto& unit : node["next-trues"]){
				if(unit.IsScalar() && unit.as<std::string>() != "this")
					animatorUnitRequest[unit.as<std::string>()].push_back([=](IAnimatorUnit *unit){prerequisite->addNextTrue(unit);});
			}
		}

		if (node["next-false"] && node["next-false"].IsScalar() && node["next-false"].as<std::string>() != "this") {
			animatorUnitRequest[node["next-false"].as<std::string>()].push_back([=](IAnimatorUnit *unit){prerequisite->addNextFalse(unit);});
		} else if(node["next-falses"]){
			for (auto& unit : node["next-falses"]){
				if(unit.IsScalar() && unit.as<std::string>() != "this")
					animatorUnitRequest[unit.as<std::string>()].push_back([=](IAnimatorUnit *unit){prerequisite->addNextFalse(unit);});
			}
		}

		if (node["name"]) animatorUnitBuffer[node["name"].as<std::string>()] = prerequisite;
		return true;
	}
}
