#pragma once

#include "IE/Animation/IChangeVariable/IChangeVariable.hpp"

class TestChangeVariable : public ie::IChangeVariable{
public:
	struct Processed{
		struct Operat{
			size_t time;
			float frame;
		};

		std::vector<Operat> operat;
		std::vector<size_t> get_size, copy;
	};

protected:
	Processed processed;
	float size, result;

public:

	TestChangeVariable(float size, float result);

	const Processed &get_processed() const;

	float get_size() override;

	float operator()(float frame) override;

	IChangeVariable *copy() override;
};
