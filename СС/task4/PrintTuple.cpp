//
// Created by anton on 24.12.18.
//

#include "PrintTuple.h"
template <class Ch,class Tr=std::char_traits<Ch>,class ... Args>
auto operator<<(std::basic_ostream<Ch,Tr> & os, std::tuple<Args...> const& t){

}