#pragma once

#include "IE/Animation/convert_to_use/iConvert_to_use.hpp"

class TestConvertToUse : public ie::IConvertToUse<float>{
public:
	struct Processed{
		struct Convert{
			size_t time;
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

	const Processed &get_processed() const;
};
