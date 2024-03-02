#include "SInitInfo.hpp"

namespace ie {
	SInitInfo::SInitInfo(DynBuffer& dyn_buffer, UpdateManager& update_manager) : dyn_buffer(dyn_buffer), update_manager(update_manager) {
	}
	
	SInitInfo::SInitInfo(InitInfo init_info) : SInitInfo(init_info.dyn_buffer, init_info.update_manager){
	}
	
	auto SInitInfo::copy(DynBuffer& dyn_buffer_) -> SInitInfo {
		return SInitInfo(dyn_buffer_, update_manager);
	}
	
	auto SInitInfo::copy(UpdateManager& update_manager_) -> SInitInfo {
		return SInitInfo(dyn_buffer, update_manager_);
	}
}