#pragma once
#include "IE/Animation/variables/iAnimation_variable.hpp"
#include <vector>

class TestAnimationVariable : public ie::IAnimationVariable{
public:
	struct Processed{
		struct ValueFromAnimation{
			unsigned long long time;
			float new_value;
		};
		std::vector<ValueFromAnimation> value_from_animation;
	};

protected:
	Processed processed;

public:
	explicit TestAnimationVariable();

	Processed get_processed() const;

	void value_from_animation(float new_value) override;
};
