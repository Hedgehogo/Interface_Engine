#pragma once
#include "../iWithValue.hpp"

namespace ui {
	template <typename T>
	class WithValue : public virtual IWithValue<T> {
	protected:
		T value;
	
	public:
		explicit WithValue(T value = T{});
		
		const T &getValue() const override;
		
		void setValue(const T &value) override;
		
		static WithValue<T> *createFromYaml(const YAML::Node &node);
	};
	
	typedef WithValue<bool> WithB;
	typedef WithValue<float> WithF;
	typedef WithValue<int> WithI;
	typedef WithValue<unsigned> WithU;
}

#include "withValue.inl"