#pragma once
#include "../iWithList.hpp"

namespace ui {
	template<typename T>
	class WithList : public IWithList {
	private:
		typedef to_auto<decltype(std::declval<T>().getValue())> V;
	
	protected:
		std::vector<std::shared_ptr<T>> list;
	
	public:
		WithList(const std::vector<V> &list = {});
		
		WithList(std::vector<std::shared_ptr<T>> list);
		
		std::shared_ptr<IWith> getElementPtr(std::size_t index) const override;
		
		void setElementPtr(std::size_t index, std::shared_ptr<IWith> value) override;
		
		V getElement(std::size_t index) const;
		
		void setElement(std::size_t index, const V &value);
		
		std::vector<V> getValue() const;
		
		void setValue(const std::vector<V> &list);
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, WithList<T> *&withList);
}

#include "withList.inl"