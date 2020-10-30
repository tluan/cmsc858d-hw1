#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <vector>
#include <iomanip>
#include <divsufsort.h>
#include <set>
using namespace std;
#include <map>
#include <boost/dynamic_bitset.hpp>
#include <set>
#include "newrank.h"
#include "newrank.cpp"

class SelectSupport {
    RankSupport rs;
    public:
    SelectSupport(RankSupport rs);
    uint64_t bsearch(uint64_t p, uint64_t r, uint64_t num);
    uint64_t Select1(uint64_t x);
    uint64_t bsearch0(uint64_t p, uint64_t r, uint64_t num);
    uint64_t Select0(uint64_t x);
    uint64_t overhead();
    void load(string& fname);
    void save(string &fname);
    //void SelectSupport::load(string& fname)

};
SelectSupport:: SelectSupport(RankSupport rs){
    this->rs = rs;
}


uint64_t SelectSupport::overhead(){
    return this->rs.overhead();
}
uint64_t SelectSupport::Select1(uint64_t x){

    return this->bsearch(1,this->rs.getB().size(),x);

}
uint64_t SelectSupport::Select0(uint64_t x){

    return this->bsearch0(1,this->rs.getB().size(),x);

}

void SelectSupport::load(string &fname) {
    this->rs.load(fname);
}
void SelectSupport::save(string &fname){
    this->rs.save(fname);
}
uint64_t SelectSupport::bsearch(uint64_t p, uint64_t r, uint64_t num) {

    if (p <= r) {

        int mid = (p + r) / 2;
//        std::cout<<"mid"<<std::endl;
//        std::cout<<mid<<std::endl;
//        std::cout<<(Rank1(mid) < num)<<std::endl;
        if (this->rs.Rank1(mid) == num) {
//            std::cout<<Rank1(mid)<<std::endl;
//            std::cout<<"done"<<std::endl;
            return mid;
        }
        if (this->rs.Rank1(mid) > num) {
//            std::cout<<"p2"<<std::endl;
            return bsearch(p, mid - 1, num);
        }
        if (this->rs.Rank1(mid) < num) {
//            std::cout<<"p3"<<std::endl;
            return bsearch(mid + 1, r, num);
        }
    }
    return 0;
}

uint64_t SelectSupport::bsearch0(uint64_t p, uint64_t r, uint64_t num){

    if (p <= r) {

        int mid = (p + r)/2;
//        std::cout<<"mid"<<std::endl;
//        std::cout<<mid<<std::endl;
//        std::cout<<(Rank0(mid) < num)<<std::endl;
        if (this->rs.Rank0(mid) == num){
//            std::cout<<Rank0(mid)<<std::endl;
//            std::cout<<"done"<<std::endl;
            return mid ;}
        if (this->rs.Rank0(mid) > num){
//            std::cout<<"p2"<<std::endl;
            return bsearch0( p, mid-1, num);}
        if (this->rs.Rank0(mid) < num){
//            std::cout<<"p3"<<std::endl;
            return bsearch0( mid+1, r, num);}
    }
    return 0;

}


//void SelectSupport::load(string& fname){
//    this->rs.load(fname);
//}