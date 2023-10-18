#include "open_url.hpp"

#ifdef WIN32
#include <windows.h>
#endif

namespace ie {
	void open_url(std::string url) {
#ifdef WIN32
		ShellExecute(nullptr, "open", url.c_str(), nullptr, nullptr, SW_HIDE);
#else
		system((std::string{"xdg-open "} + url).c_str());
#endif
	}
}