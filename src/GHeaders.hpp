#pragma once

#include <string>
#include <functional>
#include <chrono>
#include "GRegister.hpp"
#include "GLoop.hpp"

namespace gloop {

	using gtimer = std::chrono::time_point<std::chrono::system_clock>;


	/**
	 * StageType
	 * stage are the differents moment of a game
	 * INIT: before the game loop
	 * LOOP: during the game loop
	 * FINAL: after the game loop
	*/
	enum StageType {
		INIT,
		LOOP,
		FINAL,
	};

	/**
	 * HookStatus
	 * status of the functionning of each hooks
	 * OK: the hook work properly
	 * ERROR: there is an error, the gloop will stop
	 * STOP_LOOP: stop the loop stage and go into the final stage
	*/

	enum HookStatus {
		OK,
		ERROR,
		STOP_LOOP,
	};

	class GLoop;

	/**
	 * SystemHook
	 * is a structure that allow the user to create easly a hook
	 *
	 * sys_name: name of the system
	 * weight_p: determine the priority of a hook, bigger is the number, bigger priority it will have
	 * callrate: determine the callrate of a function in the LOOP stage in ms.
	 * threadable: allow the user to make a function threadable
	 * callback: function that will be called in the GLoop
	*/
	struct SystemHook {
		std::string					sys_name;
		std::size_t					weight_p;
		int							callrate;
		std::function<gloop::HookStatus(g_reg::Register &, gloop::GLoop &)>	callback;
	};

	/**
	 * HookCallRate
	 * hook: systemhook
	 * last_call: timer that allow to determine when the function need to be call
	*/
	struct HookCallRate {
		gloop::SystemHook	hook;
		gloop::gtimer	last_call;
	};


} // gloop