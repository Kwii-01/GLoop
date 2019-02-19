
#include "System.hpp"


class StageSystem
{
public:
	StageSystem() {};
	~StageSystem() {};



private:
	std::map<std::size_t, std::unique_ptr<ISystem>> _start;
	std::map<std::size_t, std::unique_ptr<ISystem>> _middle;
	std::map<std::size_t, std::unique_ptr<ISystem>> _end;
	
};