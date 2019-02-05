//
// Created by anton on 30.12.18.
//

#include "tuple.h"

template<class ...Types>
tuple<Types...>& tuple<Types...>::operator++() {
    ++content;
    return *this;
}
template<class ...Types>
tuple<Types...>::tuple(const tuple &it):content(it.content) {}

template<class ...Types>
tuple<Types...>::tuple(std::tuple<Types...> & data):content(&data) {}

template<class ...Types>
bool tuple<Types...>::operator!=(tuple const &other) const {
    return this->content!=other.content;
}

template<class ...Types>
bool tuple<Types...>::operator==(tuple const &other) const {
    return this->content==other.content;
}

template<class ...Types>
typename tuple<Types...>::reference tuple<Types...>::operator*() const {
    return *content;
}
