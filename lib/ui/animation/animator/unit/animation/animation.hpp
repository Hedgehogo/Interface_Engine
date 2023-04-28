#pragma once

#include <vector>
#include "../iAnimatorUnit.hpp"
#include "../../../changeVariable/iChangeVariable.hpp"
#include "modules/appendix/yaml-cpp/buffer/buffer.hpp"

namespace ui {
	class Animation : public IAnimatorUnit{
	public:
		struct Variable{
			PSfloat animationVariable;
			std::vector<IChangeVariable*> changeVariables;
			unsigned int activeChanger = 0;
			float timeStartChanger = 0;

			Variable(PSfloat animationVariable = {}, std::vector<IChangeVariable *> changeVariables = {});

			Variable copy();
		};

	protected:
		std::vector<IAnimatorUnit*> nextUnits;
		std::vector<IAnimatorUnit*> nextUnitsBuff;
		std::vector<Variable> animationVariables;
		std::vector<Variable*> animationUpdatableVariables;
		PSfloat speed;

	public:
		explicit Animation(std::vector<Variable> animationVariables, PSfloat speed = PSfloat{nullptr}, std::vector<IAnimatorUnit *> nextUnits = {});
		
		void setSpeed(PSfloat speed) override;
		
		void restart() override;

		std::vector<IAnimatorUnit*> update(float time) override;

		void setNextUnits(std::vector<IAnimatorUnit*> nextUnit);

		void addNextUnits(IAnimatorUnit* nextUnit);

		Animation* copy() override;

		~Animation();
	};

	
	
	template<>
	struct Decode<Animation::Variable> {
		static bool decode(const YAML::Node &node, Animation::Variable &animationUnit);
	};

	
	template<>
	struct DecodePointer<Animation> {
		static bool decodePointer(const YAML::Node &node, Animation *&animation);
	};
}