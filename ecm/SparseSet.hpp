#pragma once

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace GEcm {

	using size_type = uint32_t;
	using entity_type = size_type;

	constexpr size_type NullId = 0;

	#define GetRealId(x)	(x - 1)
	#define CreateId(x)	(x + 1)

	class BaseSparseSet {
		public:
			BaseSparseSet(size_type size) : dense_s(size), direct_s(NullId) {
				dense.resize(size, NullId);
				direct.reserve(size);
			}

			virtual ~BaseSparseSet() = default;

			BaseSparseSet(const BaseSparseSet &) = delete;

			BaseSparseSet(BaseSparseSet &&) = default;

			BaseSparseSet	&operator=(const BaseSparseSet &) = delete;

			BaseSparseSet	&operator=(BaseSparseSet &&) = default;

		private:
			struct iterator final {
				iterator(std::vector<entity_type> *dir, size_type ind) : index(ind), direct(dir) {}

				iterator(const iterator &) = default;

				iterator(iterator &&) = default;

				iterator		&operator=(const iterator &) = default;

				iterator		&operator=(iterator &&) = default;

				inline iterator	&operator+(const size_type &n) {
					index += n;
					return (*this);
				}

				inline iterator	&operator-(const size_type &n) {
					index -= n;
					return (*this);
				}

				inline iterator	&operator++(int) {
					++index;
					return (*this);
				}

				inline iterator	&operator--(int) {
					--index;
					return (*this);
				}

				inline iterator	&operator-=(const size_type &n) {
					return (*this - n);
				}

				inline iterator	&operator+=(const size_type &n) {
					return (*this + n);
				}

				inline bool		operator==(const iterator &n) {
					return index == n.index;
				}

				inline bool		operator<=(const iterator &n) {
					return index <= n.index;
				}

				inline bool		operator>=(const iterator &n) {
					return index >= n.index;
				}

				inline bool		operator<(const iterator &n) {
					return !(*this >= n);
				}

				inline bool		operator>(const iterator &n) {
					return !(*this <= n);
				}

				inline bool		operator!=(const iterator &n) {
					return !(*this == n);
				}

				inline entity_type	*operator->() {
					return &((*direct)[index]);
				}

				inline entity_type	&operator*() {
					return *operator->();
				}

				private:
					size_type				index;
					std::vector<entity_type>	*direct;
			};
		
		public:
			inline size_type	size() const noexcept {
				return direct_s;
			}

			inline size_type	capacity() const noexcept {
				return direct.capacity();
			}

			virtual void		shrink_to_fit() {
				direct.shrink_to_fit();
			}

			virtual void		reserve(const size_type size) noexcept {
				direct.reserve(size);
			}

			virtual void		resize(const size_type size) noexcept {
				direct_s = size;
				direct.resize(size);
			}

			inline bool		empty() const noexcept {
				return direct_s == 0;
			}

			inline bool		has(const size_type n) const noexcept {
				if (n >= dense_s || dense[n] == NullId)
					return false;
				return true;
			}

			inline entity_type		&get(const size_type n) {
				return direct[GetRealId(dense[n])];
			}

			inline entity_type		*try_get(const size_type n) {
				if (!has(n))
					return nullptr;
				return &(direct[GetRealId(dense[n])]);
			}

			inline const entity_type		&operator[](const size_type &n) const {
				return direct[GetRealId(dense[n])];
			}

			inline entity_type			&operator[](const size_type &n) {
				return direct[GetRealId(dense[n])];
			}

			inline entity_type			&back() {
				return direct.back();
			}

			inline iterator	begin() noexcept {
				return iterator{&direct, 0};
			}

			inline iterator	end() noexcept {
				return iterator{&direct, direct_s};
			}

			inline iterator	find(const entity_type n) {
				return has(n) ? (begin() + GetRealId(dense[n])) : end();
			}

			virtual void		destroy(const entity_type &entity) {
				if (!has(entity))
					return;
				size_type	last_id = direct.back();
				if (last_id != entity) {
					direct[GetRealId(dense[entity])] = std::move(direct[GetRealId(dense[last_id])]);
					dense[last_id] = dense[entity];
				}
				dense[entity] = NullId;
				direct.pop_back();
				--direct_s;
			}

		protected:
			inline size_type		pos(const size_type &n) {
				return GetRealId(dense[n]);
			}

			void		push(const entity_type &data) {
				if (data >= dense_s) {
					dense_s = data + 1;
					dense.resize(dense_s, NullId);
				}
				dense[data] = CreateId(direct_s);
				direct.push_back(data);
				++direct_s;
			}

			inline void		push(entity_type &&data) {
				push(static_cast<const entity_type &>(std::forward<entity_type>(data)));
			}

		private:
			size_type				dense_s;
			size_type				direct_s;
			std::vector<entity_type>	direct;
			std::vector<size_type>		dense;
	};


	template<typename Data>
	class	SparseSet : public BaseSparseSet {
		private:
			using parent = BaseSparseSet;
			using direct_type = Data;

		public:
			SparseSet(size_type size) : parent(size), direct_s(NullId) {
				direct.reserve(size);
			}

			SparseSet(const SparseSet<Data> &) = delete;

			SparseSet(SparseSet<Data> &&) = default;

			SparseSet<Data>	&operator=(const SparseSet<Data> &) = delete;

			SparseSet<Data>	&operator=(SparseSet<Data> &&) = default;

		private:
			struct iterator final {
				iterator(std::vector<direct_type> *dir, size_type ind) : index(ind), direct(dir) {}

				iterator(const iterator &) = default;

				iterator(iterator &&) = default;

				iterator	&operator=(const iterator &) = default;

				iterator		&operator=(iterator &&) = default;

				inline iterator	&operator+(const size_type &n) {
					index += n;
					return (*this);
				}

				inline iterator	&operator-(const size_type &n) {
					index -= n;
					return (*this);
				}

				inline iterator	&operator++(int) {
					++index;
					return (*this);
				}

				inline iterator	&operator--(int) {
					--index;
					return (*this);
				}

				inline iterator	&operator-=(const size_type &n) {
					return (*this - n);
				}

				inline iterator	&operator+=(const size_type &n) {
					return (*this + n);
				}

				inline bool		operator==(const iterator &n) {
					return index == n.index;
				}

				inline bool		operator<=(const iterator &n) {
					return index <= n.index;
				}

				inline bool		operator>=(const iterator &n) {
					return index >= n.index;
				}

				inline bool		operator<(const iterator &n) {
					return !(*this >= n);
				}

				inline bool		operator>(const iterator &n) {
					return !(*this <= n);
				}

				inline bool		operator!=(const iterator &n) {
					return !(*this == n);
				}

				inline Data	*operator->() {
					return &((*direct)[index]);
				}

				inline Data	&operator*() {
					return *operator->();
				}

				private:
					size_type				index;
					std::vector<direct_type>	*direct;
			};
		
		public:

			inline void		shrink_to_fit() {
				direct.shrink_to_fit();
				parent::shrink_to_fit();
			}

			inline void		reserve(const size_type size) noexcept {
				direct.reserve(size);
				parent::reserve(size);
			}

			inline void		resize(const size_type size) noexcept {
				direct_s = size;
				direct.resize(size);
				parent::resize(size);
			}

			inline direct_type	&get(const size_type n) {
				return direct[parent::pos(n)];
			}

			inline direct_type	*try_get(const size_type n) {
				if (!parent::has(n))
					return nullptr;
				return &(direct[parent::pos(n)]);
			}

			inline direct_type	&operator[](const size_type &n) {
				return direct[parent::pos(n)];
			}

			void		push(const size_type &entity, const direct_type &data) {
				parent::push(entity);
				direct.push_back(data);
				++direct_s;
			}

			inline void		push(const size_type &entity, direct_type &&data) {
				push(entity, static_cast<const direct_type &>(std::forward<direct_type>(data)));
			}

			template<typename ...Args>
			inline direct_type	&emplace(entity_type entity, Args&& ...args) {
				push(entity, direct_type{std::forward<Args>(args) ...});
				return get(entity);
			}

			void		destroy(const entity_type &entity) {
				if (!parent::has(entity))
					return;
				if (parent::pos(entity) != parent::pos(parent::back()))
					direct[parent::pos(entity)] = std::move(direct[parent::pos(parent::back())]);
				parent::destroy(entity);
				direct.pop_back();
				--direct_s;
			}

			inline Data	&back() {
				return direct.back();
			}

			inline iterator	begin() noexcept {
				return iterator{&direct, 0};
			}

			inline iterator	end() noexcept {
				return iterator{&direct, direct_s};
			}

			inline iterator	find(const entity_type n) {
				return parent::has(n) ? (begin() + parent::pos(n)) : end();
			}

		private:
			size_type				direct_s;
			std::vector<direct_type>	direct;
	};

}