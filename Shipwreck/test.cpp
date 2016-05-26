#include "shipwreck.hh"
#include "shipwreck.hh"
#include <bits/stdc++.h>
using namespace std;

template<class T, class U>
inline constexpr bool same() {
	return is_same<T,U>::value;
}

template<unsigned C, unsigned M, unsigned S>
struct _ship {
	using cannons = typename multiply_gear<Cannon, C>::type;
	using masts = typename multiply_gear<Mast, M>::type;
	using oars = typename multiply_gear<Oar, S>::type;
	using type = typename add_gear<cannons, typename add_gear<masts, oars>::type>::type;
};

template<unsigned C, unsigned M, unsigned S>
using gear = typename _ship<C, M, S>::type;

template<unsigned C, unsigned M, unsigned S>
using squad = Squad<typename _ship<C, M, S>::type>;

inline void test() {
	{
		Squad<Cannon> sc;
		Squad<Mast> sm;
		Squad<Oar> so;

		assert(sc == sc);
		assert(sm == sm);
		assert(so == so);

		assert(!(sc != sc));
		assert(!(sm != sm));
		assert(!(so != so));

		assert(!(sm != so));

		assert(sc > sm);
		assert(sc > so);
		assert(sm == so); 

		assert(sc >= sm);
		assert(sc >= so);
		assert(sm >= so);

		assert(so == sm);
		assert(so < sc);
		assert(sm < sc);

		assert(so <= sm);
		assert(so <= sc);
		assert(sm <= sc);

		assert(sc < sc * 2);
		assert(sc * 42 < sc * 50);
		assert(sc > so * 50);

		assert(sc + sc > sc);
		assert(so + so < sc);
		assert(0 * sc > 0 * so);
	}

	{
		constexpr Squad<Cannon> sc;
		constexpr Squad<Mast> sm;
		constexpr Squad<Oar> so;

		static_assert(sc == sc, "Cannon == Cannon");
		static_assert(sm == sm, "Mast == Mast");
		static_assert(so == so, "Oar == Oar");

		static_assert(!(sc != sc), "!(Cannon != Cannon)");
		static_assert(!(sm != sm), "!(Mast != Mast)");
		static_assert(!(so != so), "!(Oar != Oar)");

		static_assert(!(sm != so), "!(Mast != Oar)");

		static_assert(sc > sm, "Cannon > Mast");
		static_assert(sc > so, "Cannon > Oar");
		static_assert(sm == so, "Mast == Oar"); 

		static_assert(sc >= sm, "Cannon >= Mast");
		static_assert(sc >= so, "Cannon >= Oar");
		static_assert(sm >= so, "Mast >= Oar");

		static_assert(so == sm, "Oar == Mast");
		static_assert(so < sc, "Oar < Cannon");
		static_assert(sm < sc, "Mast < Cannon");

		static_assert(so <= sm, "Oar <= Mast");
		static_assert(so <= sc, "Oar <= Cannon");
		static_assert(sm <= sc, "Mast <= Cannon");

		static_assert(sc < sc * 2, "Cannon < Cannon * 2");
		static_assert(sc * 42 < sc * 50, "Cannon * 42 < Cannon * 50");
		static_assert(sc > so * 50, "Cannon > Oar * 50");

		static_assert(sc + sc > sc, "Cannon + Cannon > Cannon");
		static_assert(so + so < sc, "Oar + Oar < Cannon");
		static_assert(0 * sc > 0 * so, "0 * Cannon > 0 * Oar");
	}

	{
		squad<0, 0, 0> squad1, squad2{42};
		assert(43 == join_ships(squad1, squad2).get_count());
	}

	{
		constexpr squad<0, 0, 0> squad1, squad2{42};
		static_assert(43 == join_ships(squad1, squad2).get_count(), "1 Raft + 42 Rafts == 43 Rafts");
	}

	{
		constexpr Squad<Cannon> squad1;
		constexpr Squad<Mast> squad2;
		static_assert(1 == join_ships(squad1, squad2).get_count(), "1 Cannon + 1 Mast == 1 Cannon-Mast");
	}

	{
		using big = gear<100, 200, 300>;
		using small = gear<42, 18, 1>;
		using zero = gear<0, 0, 0>;

		static_assert(same<typename remove_gear<small, big>::type, zero>(), "Negative should be rouded to zero");
	}

	{
		static_assert(add_gear<Cannon, Cannon>::type::cannons == 2, "Two cannons should have 2 cannons");
		static_assert(add_gear<Cannon, Cannon>::type::masts == 0, "Two cannons should have 0 masts");
		static_assert(add_gear<Cannon, Cannon>::type::oars == 0, "Two cannns should have 0 oars");
	}

	{
		using Ship = gear<2, 1, 0>;
		static_assert(multiply_gear<Ship, 42>::type::cannons == 42 * 2, "42 * <2, 1, 0> should have 84 cannons");
		static_assert(multiply_gear<Ship, 42>::type::masts   == 42 * 1, "42 * <2, 1, 0> should have 42 masts");
		static_assert(multiply_gear<Ship, 42>::type::oars    == 42 * 0, "42 * <2, 1, 0> should have 0 oars");
	}

	{
		using Ship = gear<1, 3, 18>;
		static_assert(same<split_gear<multiply_gear<Ship, 123>::type, 123>::type, Ship>(), "Ship * 123 / 123 should be Ship");
		static_assert(!same<multiply_gear<split_gear<Ship, 123>::type, 123>::type, Ship>(),	"Ship / 123 * 123 should NOT be Ship");
	}

	{
		using Ship = gear<0, 0, 0>;
		static_assert(Ship::cannons == 0, "The empty ship should have no cannons");
		static_assert(Ship::masts == 0, "The empty ship should have no cannons");
		static_assert(Ship::oars == 0, "The empty ship should have no oars");
		static_assert(same<split_gear<Ship, 100000>::type, Ship>(), "Zero / 100000 should be zero");
		static_assert(same<multiply_gear<Ship, 2>::type, Ship>(), "Zero * 2 should be zero");
		static_assert(same<split_gear<Cannon, 2>::type, Ship>(), "Cannon / 2 should be Zero");
		static_assert(same<split_gear<Mast, 2>::type, Ship>(), "Mast / 2 should be Zero");
		static_assert(same<split_gear<Oar, 2>::type, Ship>(), "Oar / 2 should be Zero");

		static_assert(same<multiply_gear<Cannon, 0>::type, Ship>(), "Cannon * 0 should be Zero");
		static_assert(same<multiply_gear<Mast, 0>::type, Ship>(), "Mast * 0 should be Zero");
		static_assert(same<multiply_gear<Oar, 0>::type, Ship>(), "Oar * 0 should be Zero");

	}

	{
		static_assert(same<split_gear<Cannon, 1>::type, Cannon>(), "Cannon / 1 should be Cannon");
		static_assert(same<split_gear<Mast, 1>::type, Mast>(), "Mast / 1 should be Mast");
		static_assert(same<split_gear<Oar, 1>::type, Oar>(), "Oar / 1 should be Oar");
	}

	{
		constexpr squad<4, 2, 3> s1;
		constexpr squad<1, 2, 3> s2{100000};
		constexpr squad<4, 2, 3> s3{s1};

		static_assert(s1 > s2, "<4, 2, 3> should be greater than <1, 2, 3>");
		static_assert(s1 == s3, "<4, 2, 3> should be equal to its copy");
		static_assert(expected_booty(s1, s2) == s2, "<4, 2, 3> should win against <1, 2, 3>");
	}

	{
		squad<100, 200, 300> s1;
		squad<100, 0, 0> s2;

		assert(s1 == s2);
		assert(!(s1 > s2));
		assert(typeid(s2) == typeid(expected_booty(s1, s2)));
	}

	{
		constexpr squad<0, 0, 0> raft;
		static_assert((raft * 3).get_count() == 3, "1 * 3 should be 3");
		static_assert((raft * (-3)).get_count() == 0, "1 * (-3) should be 0 :D");
		static_assert((raft / (-3)).get_count() == 0, "1 / (-3) should be 0 :D");
		static_assert((raft / 3).get_count() == 0, "1 / 3 should be 0 :D");
		static_assert(((raft * 42) - (raft * 20)).get_count() == 22, "42 - 20 should be 22");
		static_assert(((raft * 42) - (raft * 50)).get_count() == 0, "42 - 50 should be 0");
		static_assert(expected_booty(raft, raft) == raft, "expected_booty(raft, raft) should be raft");
		static_assert(join_ships(raft, raft) == 2 * raft, "join_ships(raft, raft) should be 2 * raft");
		static_assert(join_ships(raft, raft) == raft * 2, "join_ships(raft, raft) should be raft * 2");
	}

	{
		squad<3, 1, 0> s{20};
		ostringstream ss;
		ss << s;
		assert(ss.str() == "Ships: 20; Ship gear: Cannons: 3, Masts: 1, Oars: 0");
	}

	{
		squad<1, 2, 3> s;
		s += s;
		assert(s.get_count() == 2);
	}

	{
		squad<1, 2, 3> s;
		s -= s;
		assert(s.get_count() == 0);
	}

	{
		squad<1, 2, 3> s{100};
		s *= 10;
		assert(s.get_count() == 1000);
	}

	{
		squad<1, 2, 3> s{100};
		s /= 10;
		assert(s.get_count() == 10);
	}

	{
		constexpr squad<13, 3, 18> s1{2392323}, s2{29323};
		constexpr squad<22, 1, 0> s3;

		static_assert(s1 + s2 == s2 + s1, "Addition should be commutative");
		static_assert(17 * s1 == s1 * 17, "Multiplication should be commutative");
		static_assert((2 * 3) * s1 == 2 * (3 * s1), "Multiplication should be associative");
	}

	{
		constexpr Squad<Cannon> s1{42}, s2{81};
		static_assert(s2.get_count() == expected_booty(s1, s2).get_count(), "In case of equal types expected booty should return its second argument");
		static_assert(s1.get_count() != expected_booty(s1, s2).get_count(), "In case of equal types expected booty should return its second argument");

		static_assert(s1.get_count() == expected_booty(s2, s1).get_count(), "In case of equal types expected booty should return its second argument");
		static_assert(s2.get_count() != expected_booty(s2, s1).get_count(), "In case of equal types expected booty should return its second argument");
	}

	{
		constexpr Squad<Oar> s1{42};
		constexpr Squad<Mast> s2{129};
		static_assert(s1 == expected_booty(s1, s2), "Oar should lose against Mast");
	}

	{
		constexpr squad<0, 0, 0> s1{1000000000};
		constexpr Squad<Mast> s2{0};
		static_assert(s1 == expected_booty(s1, s2), "10^9 pirates on rafts should lose against 0 masts (however funny it sounds)");
	}

	{
		assert((reinterpret_cast<const void*>(&squad<1239, 12230, 13>::gear) != reinterpret_cast<const void*>(&squad<12, 7, 12>::gear)));
		std::cout << "address: " << &squad<17, 20, 12>::gear << std::endl;
	}
}