#pragma once

#include <thread>
#include <mutex>
#include <queue>

namespace gloop {

	class ThreadPool {
		public:
			ThreadPool(const std::size_t max_worker);

		private:
			std::mutex			_mutexWorker;
	};
};