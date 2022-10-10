#pragma once
#include "../iSValue.hpp"

namespace ui {
	template <typename T>
	class SValue : public virtual ISValue<T> {
	protected:
		T value;
	
	public:
		explicit SValue(T value = T{});
		
		const T &getValue() const override;
		
		void setValue(const T &value) override;
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SValue<T> *&sValue);
	
	typedef SValue<bool> Sbool;
	typedef SValue<float> Sfloat;
	typedef SValue<int> Sint;
	typedef SValue<unsigned> Suint;
	
	typedef std::shared_ptr<Sbool> PSbool;
	typedef std::shared_ptr<Sfloat> PSfloat;
	typedef std::shared_ptr<Sint> PSint;
	typedef std::shared_ptr<Suint> PSuint;
}

#include "withValue.inl"