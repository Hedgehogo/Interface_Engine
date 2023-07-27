#pragma once

#include "../iSList.hpp"

namespace ui {
	template<typename T>
	class SList : public ISList {
	private:
		using V = to_auto<decltype(std::declval<T>().getValue())>;
		using SetterFunc = std::function<void(const std::vector<V>&)>;
	
	protected:
		std::vector<std::shared_ptr<T>> list;
		std::vector<SetterFunc> setters;
		
		void set();
	
	public:
		SList(const std::vector<V>& list = {});
		
		SList(std::vector<std::shared_ptr<T>> list);
		
		PIShared getElementPtr(std::size_t index) const override;
		
		void setElementPtr(std::size_t index, PIShared value) override;
		
		V getElement(std::size_t index) const;
		
		void setElement(std::size_t index, const V& value);
		
		std::vector<V> getValue() const;
		
		void setValue(const std::vector<V>& list);
	};
	
	template<typename T>
	struct DecodePointer<SList<T>> {
		static bool decodePointer(const YAML::Node& node, SList<T>*& withList);
	};
	
	template<typename T>
	using PSList = std::shared_ptr<SList<T>>;
}

#include "sList.inl"