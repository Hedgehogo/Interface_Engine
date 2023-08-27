#pragma once

#include "IE/Animation/IChangeVariable/IChangeVariable.hpp"

class TestChangeVariable : public ie::IChangeVariable{
public:
	struct Processed{
		struct Operat{
			unsigned long long time;
			float frame;
		};

		std::vector<Operat> operat;
		std::vector<unsigned long long> getSize, copy;
	};

protected:
	Processed processed;
	float size, result;

public:

	TestChangeVariable(float size, float result);

	const Processed &getProcessed() const;

	float getSize() override;

	float operator()(float frame) override;

	IChangeVariable *copy() override;
};
