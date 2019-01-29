#pragma once

#include "../../src/System.hpp"

class Movement : public gloop::ISystem
{
public:
	Movement():_priority(3), _callRate(800), _speed(2.0), _startTime(std::chrono::system_clock::now()) {};
	~Movement() {};

	void	start() {};
	void	update() {


		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _startTime).count() > _callRate) {
			std::cout << "updating Movement system" <<  std::endl;
			_startTime = std::chrono::system_clock::now();
		}

		// utiliser le register pour modifier valeur de l'EC
	}
	const uint32_t	&getPriority() const noexcept { return _priority; }
	void		setPriority(const uint32_t priority) noexcept { _priority = priority; }
	const int		&getCallrate() const noexcept { return _callRate; }
	void		setCallrate(const int callRate) noexcept { _callRate = callRate; }

private:
	uint32_t	_priority;
	int			_callRate;
	double		_speed;
	std::chrono::time_point<std::chrono::system_clock> _startTime;


};