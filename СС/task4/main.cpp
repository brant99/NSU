#include <iostream>
#include <tuple>
#include "CSVParser.h"
#include "tuple.h"
#include "CSVParser.cpp"
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};
template <class Ch,class Tr=std::char_traits<Ch>,class ... Args>
auto operator<<(std::basic_ostream<Ch,Tr> & os, std::tuple<Args...> const & t){
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
}
int main() {
    std::ifstream loghd("input.txt");
    std::string a;
    CSVParser<int,char,int,int> lol(loghd,0);
    for (tuple<int,char,int,int> rs:lol){
        std::cout<<*rs;
    }
    std::tuple<int ,std::string> t(5,"c");
    return 0;
}