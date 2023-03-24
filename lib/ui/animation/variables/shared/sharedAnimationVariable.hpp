#pragma once

#include "../iAnimationVariable.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../../convertToUse/iConvertToUse.hpp"

namespace ui {
	template<typename T>
	class SharedAnimationVariable : public IAnimationVariable{
	protected:
		std::shared_ptr<ISValue<T>> value;
		IConvertToUse<T>* convertToUse;

	public:
		SharedAnimationVariable(std::shared_ptr<ISValue<T>> value, IConvertToUse <T> *convertToUse);

		void valueFromAnimation(float newValue) override;
	};

	template<typename T>
	bool convertPointer(const YAML::Node &node, SharedAnimationVariable<T>*& sharedAnimationVariable);
}

#include "sharedAnimationVariable.inl"