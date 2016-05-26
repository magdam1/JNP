#include <iostream>
#include <typeinfo>

#ifndef shipwreck
#define shipwreck

template <unsigned int C, unsigned int M, unsigned int O>
class ShipGear {
  public:
    static const unsigned int cannons = C;
    static const unsigned int masts = M;
    static const unsigned int oars = O;

    void print();
};

typedef ShipGear<1, 0, 0> Cannon;
typedef ShipGear<0, 1, 0> Mast;
typedef ShipGear<0, 0, 1> Oar;


template<class G1, class G2>
struct add_gear{
  public:
    /* suma wyposażenia zawartego w G1 i G2 */
    typedef ShipGear<G1::cannons + G2::cannons,
                     G1::masts + G2::masts,
                     G1::oars + G2::oars> type;

};

template<class G1, class G2>
struct remove_gear{
  public:
    /* wyposażenie G1 pomniejszone o G2 */
    typedef ShipGear<(G1::cannons > G2::cannons ? G1::cannons - G2::cannons : 0),
                     (G1::masts > G2::masts     ? G1::masts - G2::masts     : 0),
                     (G1::oars > G2::oars       ? G1::oars - G2::oars       : 0)> type;

};

template<class G1, unsigned int N>
struct multiply_gear{
  public:
    /* wyposażenie zawarte w G1 powiększone N razy */
    typedef ShipGear<N * G1::cannons,
                     N * G1::masts,
                     N * G1::oars> type;
};

template<class G1, unsigned int N>
struct split_gear{
  public:
    /* wyposażenie zawarte w G1 podzielone na N równych części */
    static_assert(N > 0, "Error: division by 0");
    typedef ShipGear<G1::cannons / N,
                     G1::masts   / N,
                     G1::oars    / N> type;

};


template <class Gear>
class Squad{
    unsigned int count;

  public:
    typedef ShipGear<Gear::cannons, Gear::masts, Gear::oars> gear_type;

    static const gear_type gear;    //????????????????const??????????????????

    Squad()                          : count(1)           {}
    Squad(unsigned int const cnt)    : count(cnt)         {}
    Squad(Squad<Gear> const & squad) : count(squad.count) {}
    
    Squad<Gear>& operator+=(Squad<Gear> const & squad) { count += squad.get_count(); return *this; }
    Squad<Gear>& operator-=(Squad<Gear> const & squad) { int diff = count - squad.get_count(); count = (diff > 0 ? diff : 0); return *this; }
    Squad<Gear>& operator*=(const unsigned int N) { count *= N; return *this; } 
    Squad<Gear>& operator/=(const unsigned int N) { count /= N; return *this; }
    template <typename G2> bool operator==(Squad<G2> const & squad) { return (Gear::cannons == G2::cannons); }
    template <typename G2> bool operator!=(Squad<G2> const & squad) { return (Gear::cannons != G2::cannons); }
    template <typename G2> bool operator<=(Squad<G2> const & squad) { return (Gear::cannons <= G2::cannons); }
    template <typename G2> bool operator<(Squad<G2> const & squad) { return (Gear::cannons < G2::cannons); }
    template <typename G2> bool operator>=(Squad<G2> const & squad) { return (Gear::cannons >= G2::cannons); }
    template <typename G2> bool operator>(Squad<G2> const & squad) { return (Gear::cannons > G2::cannons); }
    bool operator==(Squad<Gear> const & squad) { return (count == squad.get_count()); }
    bool operator!=(Squad<Gear> const & squad) { return (count != squad.get_count()); }
    bool operator<=(Squad<Gear> const & squad) { return (count <= squad.get_count()); }
    bool operator<(Squad<Gear> const & squad)  { return (count < squad.get_count()); }
    bool operator>=(Squad<Gear> const & squad) { return (count >= squad.get_count()); }
    bool operator>(Squad<Gear> const & squad)  { return (count > squad.get_count()); }
    
    unsigned int get_count() const {return count;}
};

/* Tworzy bandę nowych, mocniejszych okrętów */
template<class Gear, class OtherGear>
auto const join_ships(Squad<Gear> const& sq1, Squad<OtherGear> const& sq2) ->
           Squad<typename add_gear<typename Squad<Gear>::gear_type,
                                    typename Squad<OtherGear>::gear_type>::type>
{
  unsigned int all_cannons = sq1.gear.cannons * sq1.get_count() +
                             sq2.gear.cannons * sq2.get_count();
  unsigned int all_masts = sq1.gear.masts * sq1.get_count() +
                           sq2.gear.masts * sq2.get_count();
  unsigned int all_oars = sq1.gear.oars * sq1.get_count() +
                          sq2.gear.oars * sq2.get_count();

  unsigned int join_cannons = sq1.gear.cannons + sq2.gear.cannons;
  unsigned int join_masts = sq1.gear.masts + sq2.gear.masts;
  unsigned int join_oars = sq1.gear.oars + sq2.gear.oars;
  unsigned int join_count = sq1.get_count() + sq2.get_count();

  unsigned int max_cannons = (join_cannons > 0 ? all_cannons / join_cannons : join_count);
  unsigned int max_masts = (join_masts > 0 ? all_masts / join_masts : join_count);
  unsigned int max_oars = (join_oars > 0 ? all_oars / join_oars : join_count);

  /* wybieramy najmniejszą z trzech wartości max____, czyli liczność nowej bandy: */
  unsigned int min_gear = (max_cannons < max_masts ? max_cannons : max_masts);
  min_gear = (min_gear < max_oars ? min_gear : max_oars);

  return Squad<typename add_gear<typename Squad<Gear>::gear_type,
                                 typename Squad<OtherGear>::gear_type>::type>(min_gear);
}

/* Dzieli bandę na dwie nowe o tej samej liczności, złożone z mniejszych okrętów */
template<class Gear>
auto const split_ships(Squad<Gear> const& sq) ->
           Squad<typename split_gear<Gear, 2>::type> {
  return Squad<typename split_gear<Gear, 2>::type>(sq.get_count());
}

//Operatory
template <class Gear>
const Squad<Gear> operator+(Squad<Gear> const & squad1, Squad<Gear> const & squad2)
{
  return Squad<Gear>(squad1.get_count() + squad2.get_count());
}

template <class Gear>
const Squad<Gear> operator-(Squad<Gear> const & squad1, Squad<Gear> const & squad2)
{
  int diff = squad1.get_count() - squad2.get_count();
  unsigned int newNumber = (diff > 0 ? diff : 0);
  return Squad<Gear>(newNumber);
}

//czy jak zrobię w argumencie unsigned int, to to wystarczy?
template <class Gear>
const Squad<Gear> operator*(Squad<Gear> const & squad, const unsigned int N)
{
  return Squad<Gear>(squad.get_count() * N);
}

template <class Gear>
const Squad<Gear> operator*(unsigned int N, Squad<Gear> const & squad)
{
  return Squad<Gear>(squad.get_count() * N);
}

//czy to się zrzutuje?
template <class Gear>
const Squad<Gear> operator/(Squad<Gear> const & squad, const unsigned int N)
{
  return Squad<Gear>(squad.get_count() / N);
}

template <class Gear>
std::ostream& operator<<(std::ostream& os, Squad<Gear> const & squad) {
  return os << "Ships: " << squad.get_count()
            << "; Ship gear: Cannons: " << Gear::cannons
            << ", Masts: "<<Gear::masts
            << ", Oars: "<<Gear::oars;
}

//pomocnicze
template <unsigned int C, unsigned int M, unsigned int O>
void ShipGear<C, M, O>::print() {
    std::cout<<Squad<ShipGear<C, M, O> >()<<std::endl;
  }

template<class G1, class G2>
struct loser{
    public: 
      /* porównuje leksykograficznie wg sprzętu */
      constexpr static bool compare()
      {
	return (
		    (
		      (G1::cannons > G2::cannons) 
		      || ( (G1::cannons == G2::cannons) && (G1::masts > G2::masts) )
		    )
		      || ( ((G1::cannons == G2::cannons) && (G1::masts == G2::masts)) && (G1::oars >= G2::oars) )
	       );
      }
      
      /* przegrany w pojedynku dwóch band */
      typedef typename std::conditional<compare(), G2, G1>::type type;
};

template<class G1, class G2, bool C>
struct result{
  public:
    const G2& res;
    result(const G1 squad1, const G2 squad2) : res(squad2) {};
};

template<class G1, class G2>
struct result<G1, G2, false>{
  public:
    const G1& res;
    result(const G1 squad1, const G2 squad2) : res(squad1) {};
};

template<class Gear, class OtherGear>
auto expected_booty(Squad<Gear> const & squad1, Squad<OtherGear> const & squad2) ->
     const Squad<typename loser<Gear, OtherGear>::type>
{
    result<Squad<Gear>, Squad<OtherGear>, loser<Gear, OtherGear>::compare()> tmp(squad1, squad2);
    return tmp.res;
}

#endif