#pragma once

#include <vector>

namespace sparset_collection {

	class BaseSparseSet {
		public:
			// constructor
			BaseSparseSet(const std::size_t &size) : _n(0), _max(size) {
				_dense.reserve(size);
				_sparse.resize(size, 0);
			}

			// copy constructor
			BaseSparseSet(const sparset_collection::BaseSparseSet &) = delete;
			BaseSparseSet(sparset_collection::BaseSparseSet &&) = default;
			sparset_collection::BaseSparseSet	&operator=(const sparset_collection::BaseSparseSet &) = delete;
			sparset_collection::BaseSparseSet	&operator=(sparset_collection::BaseSparseSet &&) = default;

			// destructor
			virtual ~BaseSparseSet() = default;

			// checker
			inline const std::size_t	&size() const { return _n; }
			inline const std::size_t	&capacity() const { return _max; }
			inline bool				is_empty() const { return _n == 0; }
			inline bool				has(const std::size_t &ind) const { return (ind < _max && _sparse[ind] < _n && _dense[_sparse[ind]] == ind); }


			// size manipulators
			virtual void	reserve(const std::size_t &size) { 
				_dense.reserve(size);
				_sparse.reserve(size);
			}

			virtual void	resize(const std::size_t &size) {
				_max = (_max > size ? _max : size);
				_n = (_n > size ? size : _n);
				_dense.resize(size);
				_sparse.resize(size, 0);
			}

			virtual void	remove(const std::size_t &ind) {
				if (!has(ind))
					return;
				std::size_t	elem = _dense[_n - 1];
				_dense[_sparse[ind]] = elem;
				_sparse[elem] = _sparse[ind];
				--_n;
			}

			void			insert(const std::size_t &ind) {
				if (ind > _max)
					resize(ind + 1);
				_dense[_n] = ind;
				_sparse[ind] = _n;
				++_n;
			}


			// getters
			inline std::size_t		&front() { return _dense.front(); }
			inline std::size_t		&back() { return _dense.back(); }
			inline std::size_t		&get(const std::size_t &ind) { return _dense[_sparse[ind]]; }
			inline std::size_t		&operator[](const std::size_t &ind) { return _dense[_sparse[ind]]; }
			inline std::size_t		*try_get(const std::size_t &ind) { return (has(ind) ? &(_dense[_sparse[ind]]) : nullptr); }
			inline const std::size_t	&get(const std::size_t &ind) const { return _dense[_sparse[ind]]; }
			inline const std::size_t	&operator[](const std::size_t &ind) const { return _dense[_sparse[ind]]; }
			inline const std::size_t	*try_get(const std::size_t &ind) const { return (has(ind) ? &(_dense[_sparse[ind]]) : nullptr); }

			//underlying
			inline std::vector<std::size_t>		&underlying() { return _dense; }
			inline const std::vector<std::size_t>	&underlying() const { return _dense; }

		protected:
			inline const std::size_t	&pos(const std::size_t &ind) const { return _sparse[ind]; }

		private:
			std::size_t				_n; // current_size
			std::size_t				_max; // max_size
			std::vector<std::size_t>	_dense; // data
			std::vector<std::size_t>	_sparse; // position
	}; // BaseSparseSet


	/**
	 * TODO:
	 * - iterator (+ begin / end / find / operators)
	*/
	template<typename T>
	class SparseSet : public sparset_collection::BaseSparseSet {
		public:
			using parent = sparset_collection::BaseSparseSet;
			// constructor
			SparseSet(const std::size_t &size) : parent(size) {
				_dense.reserve(size);
			}

			// copy constructor
			SparseSet(const sparset_collection::SparseSet<T> &) = delete;
			SparseSet(sparset_collection::SparseSet<T> &&) = default;
			sparset_collection::SparseSet<T>	&operator=(const sparset_collection::SparseSet<T> &) = delete;
			sparset_collection::SparseSet<T>	&operator=(sparset_collection::SparseSet<T> &&) = default;

			// destructor
			~SparseSet() = default;

			// size manipulators
			void	reserve(const std::size_t &size) {
				parent::reserve(size);
				_dense.reserve(size);
			}

			void	resize(const std::size_t &size) {
				parent::resize(size);
				_dense.resize(size);
			}

			void	remove(const std::size_t &ind) {
				if (!parent::has(ind))
					return;
				if (parent::pos(ind) != parent::size() - 1)
					_dense[parent::pos(ind)] = std::move(_dense[parent::size() - 1]);
				parent::remove(ind);
			}

			void	insert(const std::size_t &ind, const T &elem) {
				if (ind > parent::size())
					resize(ind + 1);
				parent::insert(ind);
				_dense.insert(_dense.begin() + parent::pos(ind), elem);
			}

			void	insert(const std::size_t &ind, T &&elem) {
				insert(ind, static_cast<const T &>(std::forward<T>(elem)));
			}

			template<typename ...Args>
			T	&emplace(const std::size_t &ind, Args &&...args) {
				insert(ind, T{std::forward<Args>(args) ...});
				return get(ind);
			}


			// getters
			inline T		&front() { return _dense.front(); }
			inline T		&back() { return _dense.back(); }
			inline T		&get(const std::size_t &ind) { return _dense[parent::pos(ind)]; }
			inline T		&operator[](const std::size_t &ind) { return _dense[parent::pos(ind)]; }
			inline T		*try_get(const std::size_t &ind) { return (parent::has(ind) ? &(_dense[parent::pos(ind)]) : nullptr); }
			inline const T	&get(const std::size_t &ind) const { return _dense[parent::pos(ind)]; }
			inline const T	&operator[](const std::size_t &ind) const { return _dense[parent::pos(ind)]; }
			inline const T	*try_get(const std::size_t &ind) const { return (parent::has(ind) ? &(_dense[parent::pos(ind)]) : nullptr); }

			//underlying
			inline std::vector<T>					&underlying() { return _dense; }
			inline const std::vector<T>				&underlying() const { return _dense; }

			class Iterator final {
				public:
					// constructor
					Iterator(const std::vector<T> &dense, std::size_t index) : _dense(dense), _n(index) {}

					// copy constructor
					Iterator(const sparset_collection::SparseSet<T>::Iterator &) = default;
					sparset_collection::SparseSet<T>::Iterator &operator=(const sparset_collection::SparseSet<T>::Iterator &) = default;

					// destructor
					~Iterator() = default;

					// deplacement
					sparset_collection::SparseSet<T>::Iterator &operator--() {
						--_n;
						return *this;
					}

					sparset_collection::SparseSet<T>::Iterator &operator--(int) {
						_n--;
						return *this;
					}

					sparset_collection::SparseSet<T>::Iterator &operator-(std::size_t i) {
						_n -= i;
						return *this;
					}

					sparset_collection::SparseSet<T>::Iterator &operator++() {
						++_n;
						return *this;
					}

					sparset_collection::SparseSet<T>::Iterator &operator++(int) {
						_n++;
						return *this;
					}

					sparset_collection::SparseSet<T>::Iterator &operator+(std::size_t i) {
						_n += i;
						return *this;
					}


					// comparaison
					bool	operator==(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n == it._n);
					}

					bool	operator!=(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n != it._n);
					}

					bool	operator<(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n < it._n);
					}

					bool	operator<=(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n <= it._n);
					}

					bool	operator>(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n > it._n);
					}

					bool	operator>=(const sparset_collection::SparseSet<T>::Iterator &it) const {
						return (_n >= it._n);
					}


					// access
					T	&operator*() {
						return _dense[_n];
					}

					T	*operator->() {
						return &(_dense[_n]);
					}

				private:
					std::size_t		_n;
					std::vector<T>	_dense;
			};

			sparset_collection::SparseSet<T>::Iterator begin() { return sparset_collection::SparseSet<T>::Iterator{_dense, 0}; }
			sparset_collection::SparseSet<T>::Iterator end() { return sparset_collection::SparseSet<T>::Iterator{_dense, parent::size()}; }
			sparset_collection::SparseSet<T>::Iterator find(const std::size_t &ind) const {
				std::size_t	pos = (parent::has(ind) ? parent::pos(ind) : parent::size());
				return sparset_collection::SparseSet<T>::Iterator{&_dense, pos};
			}

		private:
			std::vector<T>	_dense; // data
	}; // SparseSet

} // namespace sparset_collection
