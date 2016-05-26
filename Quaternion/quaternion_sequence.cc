#include "quaternion_sequence.h"

#include <iostream>


size_t QuaternionSequence::iloscQS = 0;

QuaternionSequence::QuaternionSequence()
{
	iloscQS++;
}

QuaternionSequence::QuaternionSequence
	(const std::map<size_type, Quaternion>& m)
{
	ciag = m;
	iloscQS++;
}

QuaternionSequence::QuaternionSequence(const std::vector<Quaternion>& v)
{
	for (int i = 0; i < v.size(); ++i)
		if(v[i])
			ciag[i] = v[i];
	iloscQS++;
}

QuaternionSequence::QuaternionSequence(const QuaternionSequence& qs1)
{
	ciag = qs1.ciag;

	iloscQS++;
}

QuaternionSequence::QuaternionSequence(QuaternionSequence&& qs1)
{
	ciag = std::move(qs1.ciag);

	iloscQS++;
}

QuaternionSequence::~QuaternionSequence()
{
	iloscQS--;
}

QuaternionSequence& QuaternionSequence::operator=
	(const QuaternionSequence& qs1)
{
	this->ciag = qs1.ciag;
	return *this;
}

QuaternionSequence& QuaternionSequence::operator+=
	(const QuaternionSequence& qs1)
{
	for(auto iter = qs1.ciag.begin(); iter != qs1.ciag.end(); ++iter)
		{
			this->ciag[iter->first] += iter->second;
			if(this->ciag[iter->first] == 0)
				this->ciag.erase(iter->first);
		}

	return *this; //chyba?
}

const QuaternionSequence QuaternionSequence::operator+
	(const QuaternionSequence& qs1) const
{
	QuaternionSequence qPom(*this); //konstr kopiujacy
	qPom += qs1;
	return qPom;
}

QuaternionSequence& QuaternionSequence::operator-=
	(const QuaternionSequence& qs1)
{
	for(auto iter = qs1.ciag.begin(); iter != qs1.ciag.end(); ++iter)
	{
		this->ciag[iter->first] -= iter->second;
		if(this->ciag[iter->first] == 0)
			this->ciag.erase(iter->first);

		/*if( this->ciag[iter->first] == iter->second )
			this->ciag.erase(iter->first);
		else
			this->ciag[iter->first] -= iter->second;*/
	}
	return *this; //chyba?
}

const QuaternionSequence QuaternionSequence::operator-
	(const QuaternionSequence& qs1) const
{
	QuaternionSequence qPom(*this); //konstr kopiujacy
	qPom -= qs1;
	return qPom;
}

QuaternionSequence& QuaternionSequence::operator*=
	(const QuaternionSequence& qs1)
{
	QuaternionSequence qPom;
	for(auto iter1 = this->ciag.begin(); iter1 != this->ciag.end(); ++iter1)
	{
		for(auto iter2 = qs1.ciag.begin(); iter2 != qs1.ciag.end(); ++iter2)
			if(iter1->first == iter2->first)
				qPom.insert(iter1->first, iter1->second * iter2->second);

		if(qPom.ciag[iter1->first] == 0)
			qPom.ciag.erase(iter1->first);
	}
	*this = qPom;
	return *this;

} // dla mnozenia wektor * wektor nie bedzie bardzo podobnie

const QuaternionSequence QuaternionSequence::operator*
	(const QuaternionSequence& qs1) const
{
	QuaternionSequence qPom(*this); //konstr kopiujacy
	qPom *= qs1;
	return qPom;
}

QuaternionSequence& QuaternionSequence::operator*=(const Quaternion& q)
{
	for(auto iter = this->ciag.begin(); iter != this->ciag.end(); ++iter)
	{
		this->ciag[iter->first] *= q;
			if(this->ciag[iter->first] == 0)
				this->ciag.erase(iter->first);
	}
	return *this;
}

const QuaternionSequence QuaternionSequence::operator*
	(const Quaternion& q) const
{
	QuaternionSequence qPom(*this);//konstr kopiujacy
	return qPom *= q;

}

const Quaternion QuaternionSequence::operator[]
	(const QuaternionSequence::size_type i) const
//ostatni const - mozna wywolac dla stalej instancji klasy QuatSeq
{
	auto iter = ciag.find(i);
	if(iter != ciag.end())
		return iter->second;
	return Quaternion(0., 0., 0., 0.);
}

void QuaternionSequence::insert(const size_type n, const Quaternion& q)
{
	if(q)
		this->ciag[n] = q;
	else
		this->ciag.erase(n);
}

//nie dziala
bool QuaternionSequence::operator==(const QuaternionSequence& qs1) const
{
	return (this->ciag == qs1.ciag);
/*
	if(this->ciag.size() != qs1.ciag.size())
		return false;
	else
	{
		auto iter2 = qs1.ciag.begin();
		for(auto iter1 = this->ciag.begin();
				iter1 != this->ciag.end(); ++iter1)
		{	
			if(iter1->first != iter2->first || iter1->second != iter2->second)
					return false;
			++iter2;
		}
	}
	return true;*/
}

bool QuaternionSequence::operator!=(const QuaternionSequence& qs1) const
{
	return !((*this) == qs1);
}

QuaternionSequence::operator bool() const //ten explicit
{
	return (ciag.size() > 0);
}


size_t QuaternionSequence::count()
{
	return iloscQS;
}

const QuaternionSequence operator*
	(const Quaternion& q, const QuaternionSequence& qs1)
{
	QuaternionSequence qPom = qs1;
	return qPom *= q;
}


std::ostream& operator<<(std::ostream& os, const QuaternionSequence& qs1)
{
	os << "(";
	bool first = true;
	for (const auto& node : qs1.ciag)
	{
		if (!first)
			os << ", ";
		os << node.first << " -> " << node.second;
		first = false;
	}
	return os << ")";


	/*bool was = false;
	QuaternionSequence qPom = qs1;
	os << "(";
	for(auto iter = qPom.ciag.begin(); iter != qPom.ciag.end(); ++iter)
	{
		if(was)
			os << ", ";
		os << iter.first << "->" << iter.second;
		was = true;
	}
	os << ")";

	return os;*/

}

