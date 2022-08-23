#include "buffer.hpp"

namespace ui {
	std::map<std::string, std::shared_ptr<IWith>> Buffer::objects = {};
	
	bool Buffer::existObject(const std::string &name) {
		return objects.find(name) != objects.end();
	}
}
