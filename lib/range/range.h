#pragma once

namespace ui {
	template<typename Type>
	struct Range
	{
		Type min;
		Type max;
	};

	typedef Range<int> RangeI;
	typedef Range<float> RangeF;
	typedef Range<unsigned int> RangeU;
}