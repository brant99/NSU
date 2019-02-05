//
// Created by anton on 30.12.18.
//

#ifndef TASK4_TUPLE_H
#define TASK4_TUPLE_H


#include <iterator>

template <class ...Types>
class tuple:public std::iterator<std::input_iterator_tag,std::tuple<Types...>> {
    std::tuple<Types...>* content;
public:
    tuple(std::tuple<Types...> &);
    tuple(const tuple &it);
    tuple&operator++();
    typename tuple::reference operator*() const;
    bool operator!=(tuple const &other) const;
    bool operator==(tuple const &other) const;
};


#endif //TASK4_TUPLE_H
