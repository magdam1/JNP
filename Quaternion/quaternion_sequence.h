#include "quaternion.h"
#include <map>
#include <vector>

#ifndef quaternion_sequence_h
#define quaternion_sequence_h
class QuaternionSequence
{

public:
	typedef size_t size_type;
	QuaternionSequence();
	QuaternionSequence(const std::map<size_type, Quaternion>& m);
	QuaternionSequence(const std::vector<Quaternion>& v);
	QuaternionSequence(const QuaternionSequence& qs1);
	QuaternionSequence(QuaternionSequence&& qs1);
	~QuaternionSequence();


	QuaternionSequence& operator=(const QuaternionSequence& qs1);

	QuaternionSequence& operator+=(const QuaternionSequence& qs1);
	const QuaternionSequence operator+(const QuaternionSequence& qs1) const;

	QuaternionSequence& operator-=(const QuaternionSequence& qs1);
	const QuaternionSequence operator-(const QuaternionSequence& qs1) const;

	QuaternionSequence& operator*=(const QuaternionSequence& qs1);
	const QuaternionSequence operator*(const QuaternionSequence& qs1) const;

	QuaternionSequence& operator*=(const Quaternion& q);
	const QuaternionSequence operator*(const Quaternion& q) const;

	friend const QuaternionSequence operator*
		(const Quaternion& q, const QuaternionSequence& qs1);

	const Quaternion operator[](const QuaternionSequence::size_type i) const;

	void insert(const size_type n, const Quaternion& q);

	bool operator==(const QuaternionSequence& qs1) const;
	bool operator!=(const QuaternionSequence& qs1) const;
	explicit operator bool() const;

	static size_t count();

private:
	friend std::ostream& operator<<
		(std::ostream& os, const QuaternionSequence& qs1);

	static size_t iloscQS; //trzeba robic ++ w konstruktoreach
	std::map<size_type, Quaternion> ciag;
	//dla kazdego Quaternionu, jest pamietane na ktorym jest miejscu
	//gdy w mapie dla danego klucza nie ma Quaternionu, to jst tam 0
};

const QuaternionSequence operator*
	(const Quaternion& q, const QuaternionSequence& qs1);

std::ostream& operator<<(std::ostream& os, const QuaternionSequence& qs1);

#endif