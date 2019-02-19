
#pragma once

#include <thread>
#include <functional>
#include <algorithm>
#include <deque>
#include <future>
#include <mutex>
#include <vector>

class ThreadPool {
	public:
		ThreadPool(unsigned int	max_worker = 0) : _state(true) {
			if (max_worker < 1)
				max_worker = std::thread::hardware_concurrency();
			for (unsigned int id = 0; id < max_worker; id++)
				_worker.emplace_back(&ThreadPool::doWork, this, id);
		}

		~ThreadPool() {
			while (!workIsFinished());
			_state = false;
			_cv.notify_all();
			joinAll();
		}

		void	submit(std::function<void()> &&function) {
			std::lock_guard<std::mutex>	l(_mutex);

			_work.emplace_back([function](){ function(); });
			_cv.notify_one();
		}

		template<typename Return>
		std::future<Return>	submit(std::function<Return()> &&function) {
			std::shared_ptr<std::promise<Return>>	result(new std::promise<Return>());
			std::lock_guard<std::mutex>	l(_mutex);

			_work.emplace_back([function, result](){ result->set_value(function()); });
			_cv.notify_one();
			return result->get_future();
		}


		inline bool	workIsFinished() const noexcept { return _work.empty(); }

		inline void	stopWork() {
			while (!_work.empty());
			_state = false;
			_cv.notify_all();
			joinAll();
		}

	private:
		void	doWork(unsigned int id) {
			std::unique_lock<std::mutex>	l(_mutex);
			while (_state) {
				if (!_work.empty()) {
					auto work = std::move(_work.front());
					_work.pop_front();
					l.unlock();
					work();
					l.lock();
				} else if (_state)
					_cv.wait(l);
			}
		}

		inline void	joinAll() {
			for(auto&& thread : _worker)
				thread.join();
			_worker.clear();
		}

	private:
		std::atomic<bool>					_state;
		std::mutex						_mutex;
		std::condition_variable				_cv;
		std::deque<std::function<void()>>		_work;
		std::vector<std::thread>			_worker;
};
