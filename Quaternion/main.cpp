#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#include "quaternion_sequence.h"

using namespace std;

int main() {

    assert(QuaternionSequence::count() == 0);

    QuaternionSequence qs0;

    assert(QuaternionSequence::count() == 1);

    map<QuaternionSequence::size_type, Quaternion> m = {{1, 4+J}, {3, -1-K}};
    QuaternionSequence qs1(m);
    assert(qs1[0] == 0);
    assert(qs1[1] == 4+J);
    assert(qs1[2] == 0);
    assert(qs1[3] == -1-K);

    assert(QuaternionSequence::count() == 2);

    vector<Quaternion> v = {0, 3*I-4*K, 2-J};
    QuaternionSequence qs2(v);
    assert(qs2[0] == 0);
    assert(qs2[1] == 3*I-4*K);
    assert(qs2[2] == 2-J);
    assert(qs2[3] == 0);

    assert(QuaternionSequence::count() == 3);

    QuaternionSequence qs3(qs1);
    assert(qs3[0] == 0);
    assert(qs3[1] == 4+J);
    assert(qs3[2] == 0);
    assert(qs3[3] == -1-K);

    assert(QuaternionSequence::count() == 4);

    QuaternionSequence qs4 = qs2;
    assert(qs4[0] == 0);
    assert(qs4[1] == 3*I-4*K);
    assert(qs4[2] == 2-J);
    assert(qs4[3] == 0);

    assert(QuaternionSequence::count() == 5);

    qs1 += qs4;
    assert(qs1[0] == 0);
    assert(qs1[1] == 4+3*I+J-4*K);
    assert(qs1[2] == 2-J);
    assert(qs1[3] == -1-K);
    assert(qs1 == qs3 + qs4);

    assert(QuaternionSequence::count() == 5);

    qs2 -= qs3;
    assert(qs2[0] == 0);
    assert(qs2[1] == -4+3*I-J-4*K);
    assert(qs2[2] == 2-J);
    assert(qs2[3] == 1+K);
    assert(qs2 == qs4 - qs3);

    assert(QuaternionSequence::count() == 5);

    assert(qs1 - qs1 == qs0);
    assert(qs1 + -1 * qs1 == qs0);
    assert(qs1 + qs1 * (-1) == qs0);
    assert(qs1 * 0 == qs0);
    assert(0 * qs1 == qs0);
    assert(qs1 * 1 == qs1);
    assert(1 * qs1 == qs1);

    assert(QuaternionSequence::count() == 5);

    qs0 = qs3 * qs4;
    assert(qs0[0] == 0);
    assert(qs0[1] == 8*I-19*K);
    assert(qs0[2] == 0);
    assert(qs0[3] == 0);

    assert(QuaternionSequence::count() == 5);

    qs0 = qs4;
    assert(qs0[0] == 0);
    assert(qs0[1] == 3*I-4*K);
    assert(qs0[2] == 2-J);
    assert(qs0[3] == 0);

    qs0.insert(1, J);
    qs0.insert(3, K);
    assert(qs0[0] == 0);
    assert(qs0[1] == J);
    assert(qs0[2] == 2-J);
    assert(qs0[3] == K);

    assert(QuaternionSequence::count() == 5);

    QuaternionSequence qs6(move(qs1));
    assert(qs6[0] == 0);
    assert(qs6[1] == 4+3*I+J-4*K);
    assert(qs6[2] == 2-J);
    assert(qs6[3] == -1-K);
    assert(qs1[0] == 0);
    assert(qs1[1] == 0);
    assert(qs1[2] == 0);
    assert(qs1[3] == 0);

    assert(QuaternionSequence::count() == 6);

    while (!qs0) {
      assert(0);
    }

    // Wypisuje (1 -> 3i-4k, 2 -> 2-j)
    cout << qs4 << endl;
  
  assert(QuaternionSequence::count() == 0);

  return 0;
}
