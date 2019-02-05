#include "TritSet.h"

Trit getTrit(const uint &num, int pos) {
    uint trit=(num>>(8* sizeof(uint)-(pos+1)*2));
    trit&=3;
    return static_cast<Trit>(trit);
}

void changeTrit(int pos, uint &num,Trit val){
    num&=(~(3<<(8* sizeof(uint)-(pos+1)*2)));
    num|=(val<<(8* sizeof(uint)-(pos+1)*2));
}

TritSet::TritSet(int size) {
    size--;
    cpct=size/(4* sizeof(uint)) + 1;
    val = 0;
    for (int i = 0; 2 * i + 1 < sizeof(uint) * 8; i++)
        val |= 1 << (2 * i + 1);
    saveTrit =(uint*)malloc(cpct* sizeof(uint));
    fillUnknown(0,cpct);
    lastTrit=0;
}

TritSet::~TritSet() {
    free(saveTrit);
}

TritSet::TritSet(const TritSet & other) {
    saveTrit=(uint*)malloc(sizeof(other.saveTrit));
    for(int i=0;i<other.cpct;i++)
        saveTrit[i]=other.saveTrit[i];
    lastTrit=other.lastTrit;
    val=other.val;
    cpct=other.cpct;
}


int TritSet::capacity() const {
    return cpct ;
}

Trit TritSet::get(int pos) const {
    if(pos>lastTrit)
        return Unknown;
    else
        return getTrit(saveTrit[pos/((sizeof(uint))*4)],pos%((sizeof(uint))*4));
}

void TritSet::set(int pos, Trit value) {
    if(value==Unknown && lastTrit==pos){
        while(lastTrit && get(lastTrit)==Unknown)
            lastTrit--;
    }
    else if(lastTrit < pos && value != Unknown)
        lastTrit=pos;
    changeTrit(pos%((sizeof(uint))*4),saveTrit[pos/((sizeof(uint))*4)],value);
}


Trit TritSet::operator[](const int & pos) const {
    return get(pos);
}

TritSet& TritSet::operator=(const TritSet & secondPlace) {
    if(this->saveTrit)
        free(this->saveTrit);
    this->saveTrit=(uint*)malloc(sizeof(uint)*secondPlace.cpct);
    for(int i=0;i<secondPlace.cpct;i++)
        this->saveTrit[i]=secondPlace.saveTrit[i];
    this->cpct=secondPlace.cpct;
    this->lastTrit=secondPlace.lastTrit;
    this->val=secondPlace.val;
    return *this;
}

TritSet TritSet::operator&(const TritSet & cont2) {
    TritSet cont3(this->cpct > cont2.cpct ? *this : cont2);
    int i=0;
    if(cont2.saveTrit!=this->saveTrit) {
        while (cont2.cpct > i && this->cpct > i) {
            cont3.saveTrit[i] = cont2.saveTrit[i] & this->saveTrit[i];
            i++;
        }
        for(i; i<cont3.cpct ; i++) {
            cont3.saveTrit[i] &=Unknown;
        }
        cont3.lastTrit=(cont2.lastTrit > this->lastTrit) ? cont2.lastTrit : this->lastTrit ;
    }
    return cont3;
}

TritSet TritSet::operator|(const TritSet &cont2) {
    TritSet cont3(this->cpct > cont2.cpct ? *this : cont2);
    int i=0;
    if(cont2.saveTrit!=(this->saveTrit)) {
        while (cont2.cpct > i && this->cpct > i) {
            cont3.saveTrit[i] = cont2.saveTrit[i] | this->saveTrit[i];
            i++;
        }
        for(; i<cont3.cpct ; i++) {
            cont3.saveTrit[i] |=Unknown;
        }
        cont3.lastTrit=(cont2.lastTrit > this->lastTrit) ? cont2.lastTrit : this->lastTrit ;
    }
    return cont3;
}

TritSet TritSet::operator~() {
    TritSet cont2(*this);
    for(int i = 0 ; i<this->cpct ; i++) {
        cont2.saveTrit[i] = ~(this->saveTrit[i]);
        for(int j=0;j< sizeof(uint)*4;j++)
            if (cont2.get(j+( i * 4 * sizeof(uint))) == 1)
                cont2[i * 4 * sizeof(uint) + j] = Unknown;
    }
    return cont2;
}

void TritSet::shrink() {
    cpct=lastTrit/4* sizeof(uint) +1;
    saveTrit=(uint*)realloc(saveTrit, cpct * sizeof(uint) );
}

int TritSet::length() const {
    return lastTrit+1;
}

void TritSet::fillUnknown(const int &start,const int &end) {
    for (int i = start; i < end; i++)
        saveTrit[i] = val;
}

TritSet::reference::reference(TritSet & ReferenceTrit, const int pos) {
    this->pos=pos;
    trit=(&ReferenceTrit);
}

TritSet::reference::~reference() {
}

TritSet::reference& TritSet::reference::operator=(const Trit & var)  {
    Trit currentNum = trit->get(pos);
    if(pos>=trit->cpct * 4 * sizeof(uint)){
        if(var!=Unknown){
            trit->cpct=pos/((sizeof(uint))*4)+1;
            trit->saveTrit=(uint*)realloc(trit->saveTrit , sizeof(uint)*trit->cpct);
            trit->fillUnknown(trit->cpct,trit->cpct);
            trit->set(pos,var);
        }
    }
    else if (currentNum != var){
        trit->set(pos,var);
    }
    return *this;
}

TritSet::reference & TritSet::reference::operator=(const TritSet::reference & secondPlace){
    //Trit anotherNum = secondPlace.trit->get(secondPlace.pos);
    *this=(Trit)secondPlace;
    return *this;
}


TritSet::reference TritSet::operator[](const int & pos) {
    return reference(*this,pos);
}

TritSet::reference::operator Trit() const {
    return const_cast<const TritSet&>(*(this->trit))[this->pos];
}

