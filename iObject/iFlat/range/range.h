#pragma once

namespace ui {
	template<typename Type>
	struct Range
	{
		Type min;
		Type max;
	};

	typedef Range<int> RangeUIi;
	typedef Range<float> RangeUIf;
	typedef Range<unsigned int> RangeUIu;
}