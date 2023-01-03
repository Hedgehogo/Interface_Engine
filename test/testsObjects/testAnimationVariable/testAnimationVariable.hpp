#pragma once
#include "ui/animation/variables/iAnimationVariable.hpp"
#include <vector>

class TestAnimationVariable : public ui::IAnimationVariable{
public:
	struct Processed{
		struct ValueFromAnimation{
			unsigned long long time;
			float newValue;
		};
		std::vector<ValueFromAnimation> valueFromAnimation;
	};

protected:
	Processed processed;

public:
	Processed getProcessed() const;

	explicit TestAnimationVariable(Processed processed);

	void valueFromAnimation(float newValue) override;
};
