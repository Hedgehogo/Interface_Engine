#pragma once

#include "IE/animation/convertToUse/iConvertToUse.hpp"

class TestConvertToUse : public ui::IConvertToUse<float>{
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
