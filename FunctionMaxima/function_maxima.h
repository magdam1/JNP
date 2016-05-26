// Banaszek Mateusz + Molenda Magdalena + Lewko Krzysztof
// mb346851 + mm345746 + kl346994
// zadanie 5

#ifndef FUNCTION_MAXIMA_H_
#define FUNCTION_MAXIMA_H_

#include <set>
#include <memory>
#include <vector>

struct InvalidArg: std::exception {
		virtual const char* what() const throw () {
			return "InvalidArg";
		}
} invalid_arg_exc;

template<typename A, typename V> class FunctionMaxima {

	public:
		class point_type {

			public:
				A const& arg() const {
					return *a;
				}

				V const& value() const {
					return *v;
				}

				point_type(point_type const& pt) :
						a(pt.a), v(pt.v) {
				}

				point_type& operator=(point_type const& pt) {
					if (this != &pt) {
						a = pt.a;
						v = pt.v;
					}
					return *this;
				}

				point_type() = delete;

			private:
				point_type(A const& argu, V const& valu) :
						a(std::make_shared<const A>(argu)),
						v(std::make_shared<const V>(valu)) {
				}

				point_type(std::shared_ptr<const A> ptr) :
						a(ptr), v(nullptr) {
				}

				point_type(point_type&& old) = default;
				point_type& operator=(point_type&& old) = default;

				friend class FunctionMaxima<A, V> ;

				std::shared_ptr<const A> a;
				std::shared_ptr<const V> v;

		}; // end of point_type

	private:

		/*
		 * Compare points by values then by args
		 * strong guarantee
		 */
		struct comp_values {
				bool operator()(point_type const& p1,
						point_type const& p2) const {

					if (!(p1.value() < p2.value())
							&& !(p2.value() < p1.value())) {

						return (p1.arg() < p2.arg());
					}
					else {
						return (p2.value() < p1.value());
					}
				}
		};

		/*
		 * Compare points by args
		 * strong guarantee
		 */
		struct comp_args {
				bool operator()(point_type const& p1,
						point_type const& p2) const {

					return (p1.arg() < p2.arg());
				}
		};

		/*
		 * keeps function args and values
		 */
		std::multiset<point_type, comp_args> fun;

		/*
		 * keeps local max
		 */
		std::set<point_type, comp_values> lmax;


		enum class WhatToDo {
			ADD, DELETE, NOTHING
		};

		/*
		 * For every point in the given set checks if it's local max
		 * (in order by arg)
		 * strong guarantee
		 */
		const std::vector<bool> is_local_max(
				std::set<point_type, comp_args> const& funct) {

			std::vector<bool> result;
			auto it = funct.begin();
			while (it != funct.end()) {
				if (((it == funct.begin())
							|| (!(it->value() < std::prev(it, 1)->value())))
						&& ((it == std::prev(funct.end(), 1))
							|| (!(it->value() < std::next(it, 1)->value())))) {

					result.push_back(true);
				}
				else {
					result.push_back(false);

				}
				++it;
			}
			return result;
		}

		/*
		 * deleter for A object which doesn't destroy it
		 */
		struct a_deleter {
				void operator()(A const*) const {
				}
		};

	public:
		using iterator = typename std::set<point_type, comp_args>::const_iterator;
		using mx_iterator = typename std::set<point_type, comp_values>::const_iterator;
		typedef typename std::multiset<point_type, comp_args>::size_type size_type;

		FunctionMaxima() :
				fun(), lmax() {
		}

		FunctionMaxima(FunctionMaxima<A, V> const& old) = default;
		FunctionMaxima(FunctionMaxima<A, V> && old) = default;
		FunctionMaxima<A, V>& operator=(FunctionMaxima<A, V> && old) = default;

		/*
		 * strong guarantee
		 */
		FunctionMaxima<A, V>& operator=(FunctionMaxima<A, V> const& old) {
			if (this != &old) {
				std::multiset<point_type, comp_args> pfun(old.fun);
				std::set<point_type, comp_values> plmax(old.lmax);
				fun.swap(pfun);
				lmax.swap(plmax);
			}

			return *this;
		}

		/*
		 * strong guarantee
		 */
		V const& value_at(A const& a) const {
			const auto it = fun.find(
					point_type(std::shared_ptr<const A>(&a, a_deleter())));
			if (it == fun.end()) {
				throw invalid_arg_exc;
			}

			return it->value();
		}

		/*
		 * strong guarantee
		 */
		void set_value(A const& a, V const& v) {
			/*
			 * strong guarantee section:
			 */
			auto itf_a = fun.find(
					point_type(std::shared_ptr<const A>(&a, a_deleter())));
			if ((itf_a != fun.end()) &&
					!(itf_a->value() < v) && !(v < itf_a->value())) { // there's nothing to do
				return;
			}

			// iterators to the old point; if it didn't exist - to end()
			const auto itf_s = itf_a;
			const auto itl_s =
					(itf_s != fun.end()) ? lmax.find(*itf_s) : lmax.end();

			// containers needed to update local maxs
			std::vector<bool> is_max;
			std::vector<WhatToDo> action(5, WhatToDo::NOTHING);
			std::vector<typename std::set<point_type, comp_values>::iterator> iter(5);
			std::set<point_type, comp_args> to_analyse;
			auto ita = to_analyse.begin();
			int i = 0;

			point_type new_point(a, v);
			bool added = false;
			if (itf_a == fun.end()) { // adding a is needed

				itf_a = fun.insert(new_point);
				added = true;
			}

			try {
				/*
				 * if something fails now
				 * rollback of inserting new_point (if it was done) is needed
				 */

				// choosing proper points to analyze new local max
				to_analyse.insert(new_point);
				if (std::next(itf_a, 1) != fun.end()) {
					to_analyse.insert(*std::next(itf_a, 1));
					if (std::next(itf_a, 2) != fun.end()) {
						to_analyse.insert(*std::next(itf_a, 2));
					}
				}
				if (itf_a != fun.begin()) {
					to_analyse.insert(*std::prev(itf_a, 1));
					if (std::prev(itf_a, 1) != fun.begin()) {
						to_analyse.insert(*std::prev(itf_a, 2));
					}
				}

				// analyzing new local max
				is_max = is_local_max(to_analyse);

				// analyzing required changes of set with local max
				ita = to_analyse.begin();
				i = 0;
				if (fun.find(*ita) != fun.begin()) {
					++ita;
					++i;
				}
				while ((ita != to_analyse.end())
						&& ((std::next(ita, 1) != to_analyse.end())
								|| (fun.find(*ita) == std::prev(fun.end(), 1)))) {
					iter[i] = lmax.find(*ita);

					if (is_max[i] && (iter[i] == lmax.end())) {
						action[i] = WhatToDo::ADD;
					}
					else if ((!is_max[i]) && (iter[i] != lmax.end())) {
						action[i] = WhatToDo::DELETE;
					}
					++ita;
					++i;
				}

				// inserting new_point if it wasn't done before
				if (!added) {
					itf_a = fun.insert(new_point);
					added = true;
				}

				// inserting new local max
				ita = to_analyse.begin();
				auto itaa = to_analyse.begin();
				i = 0;
				try {
					/*
					 * if something fails now it has to be rollbacked:
					 */
					while (ita != to_analyse.end()) {
						if (action[i] == WhatToDo::ADD) {
							iter[i] = lmax.insert(*ita).first;
						}
						++i;
						++ita;
					}

				}
				catch (...) { // rollback of inserting new local max
					i = 0;
					while (itaa != ita) {
						if (action[i] == WhatToDo::ADD)
							lmax.erase(iter[i]); //no-throw
						++itaa;
						++i;
					}
					throw;
				}
			}
			catch (...) { // rollback of inserting new_point
				if (added) {
					fun.erase(itf_a); // no-throw
				}
				throw;
			}

			/*
			 * no-throw section:
			 */

			// deleting points which are no longer local max
			ita = to_analyse.begin();
			i = 0;
			while (ita != to_analyse.end()) {
				if (action[i] == WhatToDo::DELETE) {
					lmax.erase(iter[i]);
				}
				++i;
				++ita;
			}
			if (itl_s != lmax.end()) {
				lmax.erase(itl_s);
			}

			// deleting old point (if it existed)
			if (itf_s != fun.end()) {
				fun.erase(itf_s);
			}

		}

		/*
		 * strong guarantee
		 */
		void erase(A const& a) {
			/*
			 * strong guarantee section:
			 */
			const auto itf_a = fun.find(
					point_type(std::shared_ptr<const A>(&a, a_deleter())));
			if (itf_a == fun.end()) { // there's no arg a
				return;
			}

			// below itf_a != fun.end() is granted:
			const auto itl_a = lmax.find(*itf_a);

			WhatToDo todo_prev = WhatToDo::NOTHING;
			WhatToDo todo_next = WhatToDo::NOTHING;

			// iterators to previous and next point
			const auto itf_prev =
					(itf_a == fun.begin()) ? fun.end() : std::prev(itf_a, 1);
			const auto itf_next = std::next(itf_a, 1);
			const auto itl_prev =
					(itf_prev == fun.end()) ? lmax.end() : lmax.find(*itf_prev);
			const auto itl_next =
					(itf_next == fun.end()) ? lmax.end() : lmax.find(*itf_next);

			// previous may be max :
			if (itf_prev != fun.end()) {
				const auto itf_prev2 =
						(itf_prev == fun.begin()) ?
								fun.end() : std::prev(itf_prev, 1);
				if (((itf_prev == fun.begin())
							|| (!(itf_prev->value() < itf_prev2->value())))
						&& ((itf_prev == std::prev(fun.end(), 2))
							|| (!(itf_prev->value() < itf_next->value())))) {

					todo_prev = WhatToDo::ADD;
				}
				else if (lmax.find(*itf_prev) != lmax.end()) {
					todo_prev = WhatToDo::DELETE;
				}

			}

			// next may be max:
			if (itf_next != fun.end()) {
				const auto itf_next2 =
						(itf_next == std::prev(fun.end(), 1)) ?
								fun.end() : std::next(itf_next, 1);
				if (((itf_next == std::next(fun.begin(), 1))
							|| (!(itf_next->value() < itf_prev->value())))
						&& ((itf_next == std::prev(fun.end(), 1))
							|| (!(itf_next->value() < itf_next2->value())))) {

					todo_next = WhatToDo::ADD;
				}
				else if (lmax.find(*itf_next) != lmax.end()) {
					todo_next = WhatToDo::DELETE;
				}
			}

			std::pair<typename std::set<point_type, comp_values>::iterator, bool> result;

			/*
			 * section that requires rollback if insert fails:
			 */

			// inserting new local max
			if (todo_prev == WhatToDo::ADD) {
				result = lmax.insert(*itf_prev);
			}

			if (todo_next == WhatToDo::ADD) {
				try {
					lmax.insert(*itf_next);
				}
				catch (...) { // rollback of insert
					if (todo_prev == WhatToDo::ADD && result.second) {
						lmax.erase(result.first); // no-throw
						throw;
					}
				}

			}

			/*
			 * no-throw section:
			 */

			// removing point
			fun.erase(itf_a);
			if (itl_a != lmax.end()) {
				lmax.erase(itl_a);
			}
			// removing from local max if required
			if (todo_prev == WhatToDo::DELETE) {
				lmax.erase(itl_prev);
			}
			if (todo_next == WhatToDo::DELETE) {
				lmax.erase(itl_next);
			}

		}

		iterator begin() const noexcept {
			return fun.begin();
		}

		iterator end() const noexcept {
			return fun.end();
		}

		/*
		 * strong guarantee
		 */
		iterator find(A const& a) const {
			return fun.find(
					point_type(std::shared_ptr<const A>(&a, a_deleter())));
		}

		mx_iterator mx_begin() const noexcept{
			return lmax.begin();
		}

		mx_iterator mx_end() const noexcept {
			return lmax.end();
		}

		size_type size() const noexcept {
			return fun.size();
		}

};

#endif