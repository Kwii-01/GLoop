#pragma once

#include <string>
#include <functional>
#include <chrono>
#include "Register.hpp"
#include "GLoop.hpp"

namespace gloop {

	using guint = std::size_t;
	using gtimer = std::chrono::time_point<std::chrono::system_clock>;

	enum HookType {
		EARLY,
		MIDDLE,
		LAST,
	};

	enum StageType {
		INIT,
		LOOP,
		FINAL,
	};

	enum HookStatus {
		OK,
		ERROR,
		STOP_LOOP,
	};

	class GLoop;

	struct SystemHook {
		std::string					sys_name;
		gloop::guint				weight_p;
		int						callrate;
		bool						threadable;
		std::function<gloop::HookStatus(ecm::Register &, gloop::GLoop &)>	callback;

		bool	operator==(const SystemHook &other) const {
			return sys_name == other.sys_name;
		}
	};

	struct HookCallRate {
		gloop::SystemHook	hook;
		gloop::gtimer	last_call;
	};
	

} // gloop