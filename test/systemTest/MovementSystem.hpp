#pragma once

#include <iostream>
#include "GHeaders.hpp"

//std::function<gloop::HookStatus(ecm::Register &, gloop::GLoop &)>	callback;

struct Movement {
	int speed;
	int direction;
};

class MovementSystem
{
public:
	MovementSystem() {
		_hookType = gloop::HookType::EARLY;
		_stageType = gloop::StageType::LOOP;
		_info.sys_name = "MovementSystem";
		_info.weight_p = 3;
		_info.callrate = 1000;
		_info.threadable = true;
		_info.callback = [this](ecm::Register &reg, gloop::GLoop &gloop) {

	//		ecm::SparseSet<Movement> list = reg.getPool<Movement>();
			return gloop::HookStatus::OK;
		};
	};
	~MovementSystem() {};

private:
	gloop::SystemHook	_info;
	gloop::HookType		_hookType;
	gloop::StageType	_stageType;
};