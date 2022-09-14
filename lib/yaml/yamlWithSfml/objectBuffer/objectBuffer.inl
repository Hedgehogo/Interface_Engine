//included into objectBuffer.hpp

namespace ui {
	template<typename T>
	T *ObjectBuffer::get(std::string name)
	{
		return dynamic_cast<T *>(objects[ name ]);
	}
}