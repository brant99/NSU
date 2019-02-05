#include <iostream>
#include <vector>
using uint=unsigned int;
enum Trit{
    True=3,False=0,Unknown=2
};

class TritSet{
    uint *saveTrit;
    uint val;
    int lastTrit;
    int cpct;
    void fillUnknown(const int &,const int&);
    Trit get(int pos) const;
    void set(int pos,Trit value);
public:
    TritSet(int);
    ~TritSet();
    TritSet(const TritSet &);
    class reference{
        friend class TritSet;
        TritSet * trit;
        int pos;
    public:
        reference(TritSet &,const int);
        ~reference();
        reference & operator=(const Trit&);
        reference & operator=(const reference&);
        operator Trit ()const;
    };
    reference operator [](const int &);
    Trit operator [](const int &) const;
    TritSet & operator=(const TritSet&);
    TritSet  operator &(const TritSet &);
    TritSet operator |(const TritSet &);
    TritSet operator ~();
    void shrink();
    int capacity() const;
    int length() const;
};

