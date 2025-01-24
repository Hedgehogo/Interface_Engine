#include "ITrigger.hpp"

namespace ie {
	auto ITrigger::is_prioritised() const -> bool {
		return false;
	}
	
	auto ITrigger::get_priority() const -> ITrigger::Priority {
		return Priority::Medium;
	}
	
	auto ITrigger::operator<(ITrigger& trigger) const -> bool {
		return get_priority() < trigger.get_priority();
	}
}
