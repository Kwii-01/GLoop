#pragma once

#include "System.hpp"

class Movement : public ISystem
{
public:
	Movement():_priority(3), _speed(2.0) {};
	~Movement() {};


	void	start();
	void	update() {
		// utiliser le register pour modifier valeur de l'EC
	}
	const uint32_t	&getPriority() { return _priority; }
	void		setPriority(const uint32_t priority) { _priority = priority; }
	const int		&getCallrate() { return _callRate; }
	void		setCallrate(const int callRate) { callRate = _callRate; }

private:
	uint32_t	_priority;
	int			_callRate;
	double		_speed;

};