#pragma once

#include <string>
#include <functional>
#include <chrono>
#include "GRegister.hpp"
#include "GLoop.hpp"

namespace gloop {

	using gtimer = std::chrono::time_point<std::chrono::system_clock>;

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

	using HookCallback = std::function<gloop::HookStatus(g_reg::Register &, gloop::GLoop &)>

	struct SystemHook {
		std::string		sys_name;
		int				callrate;
		HookCallback	callback;
	};

	struct Hook {
		gloop::SystemHook	hook;
		gloop::gtimer		last_call;
	};


} // gloop