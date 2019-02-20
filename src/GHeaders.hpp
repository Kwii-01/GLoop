#pragma once

#include <string>
#include <functional>
#include <chrono>

namespace gloop {

	using guint = std::size_t;
	using gtimer = std::chrono::time_point<std::chrono::system_clock>;

	enum HookType {
		VERY_EARLY,
		EARLY,
		MIDDLE,
		LAST,
		VERY_LAST,
	};

	enum StageType {
		INIT,
		LOOP,
		FINAL,
	};

	enum HookStatus {
		OK,
		ERROR,
		GAME_ERROR,
	};

	struct SystemHook {
		std::string					sys_name;
		gloop::guint				weight_p;
		int						callrate;
		bool						threadable;
		std::function<gloop::HookStatus(/* ecm::Register &, GLoop &*/)>	callback;

		bool	operator==(const SystemHook &other) const {
			return sys_name == other.sys_name;
		}
	};

	struct HookCallRate {
		gloop::SystemHook	hook;
		gloop::gtimer	last_call;
	};
	

} // gloop