#include <cmath>
#include <iostream>

#ifndef quaternion_h
#define quaternion_h

class Quaternion
{
public:
	Quaternion();
	Quaternion(double r);
	Quaternion(double r, double i);
	Quaternion(double a, double b, double c, double d);
	Quaternion(const Quaternion &q);
	double R() const {return re;}
	double I() const {return i;}
	double J() const {return j;}
	double K() const {return k;}

	Quaternion& operator=(const Quaternion &q);
	Quaternion& operator+=(const Quaternion &q);
	Quaternion& operator-=(const Quaternion &q);
	const Quaternion operator*=(const Quaternion &q);
	const Quaternion operator+(const Quaternion &q) const;
	const Quaternion operator-(const Quaternion &q) const;
	const Quaternion operator*(const Quaternion &q) const;
	bool operator==(const Quaternion &q) const;
	bool operator!=(const Quaternion &q) const;
	explicit operator bool() const;
	
	const Quaternion conj() const;
	double norm() const;

private:
	 double re, i, j, k;
};

//Konstruktory
inline Quaternion::Quaternion()
{
	re = 0;
	i = 0;
	j = 0;
	k = 0;
}

inline Quaternion::Quaternion(double r)
{
	re = r;
	i = 0;
	j = 0;
	k = 0;
}

inline Quaternion::Quaternion(double r, double im)
{
	re = r;
	i = im;
}

inline Quaternion::Quaternion(double a, double b, double c, double d)
{
	re = a;
	i = b;
	j = c;
	k = d;
}

inline Quaternion::Quaternion(const Quaternion &q)
{
	re = q.re;
	i = q.i;
	j = q.j;
	k = q.k;
}

//Metody
inline const Quaternion Quaternion::conj() const
{
	return Quaternion(re, -i, -j, -k);
}

inline double Quaternion::norm() const
{
	return sqrt(re*re + i*i + j*j + k*k);
}

//Operatory modyfikujące obiekt
inline Quaternion& Quaternion::operator=(const Quaternion &q)
{
	if (this == &q)
	  return *this;

	re = q.re;
	i = q.i;
	j = q.j;
	k = q.k;
	return *this;
}

inline Quaternion& Quaternion::operator+=(const Quaternion &q) 
{
	re += q.R();
	i += q.I();
	j += q.J();
	k += q.K();
	return *this;
}

inline Quaternion& Quaternion::operator-=(const Quaternion &q) 
{
	re -= q.R();
	i -= q.I();
	j -= q.J();
	k -= q.K();
	return *this;
}

inline const Quaternion Quaternion::operator*=(const Quaternion &q) 
{
	double qr = q.R(), qi = q.I(), qj = q.J(), qk = q.K();
	
	double re2, i2, j2, k2;
	
	re2 = re*qr - i*qi - j*qj - k*qk;
	i2 = re*qi + i*qr + j*qk - k*qj;
	j2 = re*qj + j*qr - i*qk + k*qi;
	k2 = re*qk + k*qr + i*qj -j*qi;
	
	re = re2;
	i = i2;
	j = j2;
	k = k2;
	
	return *this;
}

//Operatory zwracające nowy obiekt
inline const Quaternion Quaternion::operator+(const Quaternion &q) const
{	
	return Quaternion(re + q.R(), i + q.I(), j + q.J(), k + q.K());
}

inline const Quaternion Quaternion::operator-(const Quaternion &q) const
{	
	return Quaternion(re - q.R(), i - q.I(), j - q.J(), k - q.K());
}

inline const Quaternion Quaternion::operator*(const Quaternion &q) const
{	
	double qr = q.R(), qi = q.I(), qj = q.J(), qk = q.K();
	  
	return Quaternion(
			  re*qr - i*qi - j*qj - k*qk,
			  re*qi + i*qr + j*qk - k*qj,
			  re*qj + j*qr - i*qk + k*qi,
			  re*qk + k*qr + i*qj -j*qi
			 );
}

//Operatory logiczne
inline bool Quaternion::operator==(const Quaternion &q) const
{
	return ( (re == q.R()) && (i == q.I()) && (j == q.J()) && (k == q.K()) );
}

inline bool Quaternion::operator!=(const Quaternion &q) const
{
	return !(*this == q);
}

inline Quaternion::operator bool() const
{
	return ((re != 0) || (i != 0) || (j != 0) || (k != 0));
}

//Funkcje pozaklasowe
inline const Quaternion conj(Quaternion q)
{
	return Quaternion(q.R(), -q.I(), -q.J(), -q.K());
}

inline double norm(Quaternion q)
{
	double r = q.R(), i = q.I(), j = q.J(), k = q.K();
	return sqrt(r*r + i*i + j*j + k*k);
}

//Operatory pozaklasowe - do operacji z doublem
inline const Quaternion operator-(double d, const Quaternion &q)
{	
	return Quaternion((d - q.R()), -q.I(), -q.J(), -q.K());
}

inline const Quaternion operator-(const Quaternion &q, double d)
{	
	return Quaternion((q.R() - d), q.I(), q.J(), q.K());
}

inline const Quaternion operator+(double d, const Quaternion &q)
{
	return Quaternion((q.R() + d), q.I(), q.J(), q.K());
}

inline const Quaternion operator+(const Quaternion &q, double d)
{
	return Quaternion((q.R() + d), q.I(), q.J(), q.K());
}

inline const Quaternion operator*(double d, const Quaternion &q)
{
	return Quaternion((q.R() * d), (q.I() * d), (q.J() * d), (q.K() * d));
}

inline const Quaternion operator*(const Quaternion &q, double d)
{
	return Quaternion((q.R() * d), (q.I() * d), (q.J() * d), (q.K() * d));
}

inline bool operator==(const Quaternion &q, double d)
{
	return ((q.R() == d) && (q.I() == 0) && (q.J() == 0) && (q.K() == 0));
}

inline bool operator==(double d, const Quaternion &q)
{
	return ((q.R() == d) && (q.I() == 0) && (q.J() == 0) && (q.K() == 0));
}

inline bool operator!=(const Quaternion &q, double d)
{
	return ((q.R() != d) || ((q.I() != 0) || (q.J() != 0) || (q.K() != 0)));
}

inline bool operator!=(double d, const Quaternion &q)
{
	return ((q.R() != d) || ((q.I() != 0) || (q.J() != 0) || (q.K() != 0)));
}

//Operatory jednoargumentowe
inline const Quaternion operator-(const Quaternion &q)
{
	return Quaternion(-q.R(), -q.I(), -q.J(), -q.K());
}

inline const Quaternion operator+(const Quaternion &q)
{
	return Quaternion(q.R(), q.I(), q.J(), q.K());
}

//Wypisywanie
inline std::ostream& operator<<(std::ostream &os, Quaternion const &q)
{
  	double qr = q.R(), qi = q.I(), qj = q.J(), qk = q.K(), tmp;
	bool was = 0;
	
	if ( (qr != 0) || ((qi == 0) && (qj == 0) && (qk == 0)) )
	{
	  os << q.R();
	  was = 1;
	}
	
	for (int l=0; l<3; l++)
	{
	  if (l == 0)
	    tmp = qi;
	  else if (l == 1)
	    tmp = qj;
	  else
	    tmp = qk;
	  
	  if (tmp != 0)
	  {
	    if ((tmp > 0) && (was == 1)) 
	      os << "+";

	    if (tmp == -1)
	      os << "-";
	    
	    if ((tmp > 1) || (tmp < -1))
	    {
		os << tmp;
		was = 1;
	    }
	    
	    if (l == 0)
	      os << "i";
	    else if (l == 1)
	      os << "j";
	    else
	      os << "k";
	  }
	}
	  
	return os;
}

const Quaternion I = Quaternion(0, 1, 0, 0);
const Quaternion J = Quaternion(0, 0, 1, 0); 
const Quaternion K = Quaternion(0, 0, 0, 1);

#endif