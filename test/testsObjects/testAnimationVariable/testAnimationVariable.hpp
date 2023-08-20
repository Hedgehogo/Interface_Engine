#pragma once
#include "IE/Animation/variables/iAnimationVariable.hpp"
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
	explicit TestAnimationVariable();

	Processed getProcessed() const;

	void valueFromAnimation(float newValue) override;
};
