#pragma once

#include "IE/Animation/convertToUse/iConvertToUse.hpp"

class TestConvertToUse : public ie::IConvertToUse<float>{
public:
	struct Processed{
		struct Convert{
			unsigned long long time;
			float value;
		};
		std::vector<Convert> convert;
	};

protected:
	Processed processed;
	float result;
	float convert(float value) override;

public:
	explicit TestConvertToUse(float result);

	const Processed &getProcessed() const;
};
