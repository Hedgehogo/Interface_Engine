#pragma once

#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "IE/interaction/BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	struct SInitInfo {
		DynBuffer& dyn_buffer;
		UpdateManager& update_manager;
		
		SInitInfo(DynBuffer& dyn_buffer, UpdateManager& update_manager);
		
		explicit SInitInfo(InitInfo init_info);
		
		template<typename T>
		explicit SInitInfo(BasicActionInitInfo<T> init_info);
		
		SInitInfo copy(DynBuffer& dyn_buffer_);
		
		SInitInfo copy(UpdateManager& update_manager_);
	};
}

#include "SInitInfo.inl"