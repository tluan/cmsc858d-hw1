#include <iostream>
#include<vector>
#include <cstdint>
#include <map>
#include <math.h>
using namespace std;
//#include "assignment1.cpp"

vector<string> test(int i ){
    vector<string> temp = {};
    vector<string> temp2 = {};
        if(i==0){
            return{};
        }
        else{
            temp = test(i-1);
            for(string q:temp){
                temp2.push_back(q+"0");
                temp2.push_back(q+"1");
                temp2.push_back(q);
            }
        }
        return temp2;
}


int main(){
    vector<string> temp = test(3);
    for(string i:temp){
        cout<<i<<endl;
    }
}

//class RankSupport{
//    uint64_t rb_size;
//    uint64_t rs_size;
//    uint64_t input_size;
//    std::vector<uint16_t> Rb;
//    std::vector<uint64_t> Rs;
//    bit_vector B;
//
//    public:
//      RankSupport(std::vector<bool> inBytes);
//      RankSupport();
//      void initRs();
//      void initRb();
//      uint16_t initRp(uint64_t digit);
//      uint64_t Rank(uint64_t x);
//
//
//
//
//};
//RankSupport::RankSupport(){
//
//}
//RankSupport::RankSupport(std::vector<bool> inBytes){
//  this->input_size = inBytes.size();
//  this->rb_size = log2(this->input_size)*log(this->input_size)/2;
//  this->rs_size = log2(this->input_size)/2;
//
//  this->B = bit_vector(this->input_size);
//  this->B.read(inBytes);
//
//
//}
//
//
//void RankSupport::initRs(){
//  uint64_t rs_sum = 0;
//  for (uint64_t i = 0; i < this->input_size; ++i) {
//    if (i % (this->rs_size) == 0) {
//      this->Rs.push_back(rs_sum);
//      rs_sum = 0;
//    }
//
//
//    uint64_t count = this->B.readIndex(i);
//    rs_sum += count;
//
//  }
//  this->Rs.erase(this->Rs.begin());
//  this->Rb.resize(rb_size);
//}
//
//
//
//void RankSupport::initRb(){
//  uint64_t rb_sum = 0;
//  for (uint64_t i = 0; i < this->input_size; ++i) {
//    if (i % (this->rb_size) == 0) {
//      this->Rs.push_back(rb_sum);
//      if(i % (this->rs_size) == 0){
//        rb_sum = 0;
//        }
//
//    }
//
//
//    uint64_t count = this->B.readIndex(i);
//    rb_sum += count;
//
//  }
//  this->Rb.erase(this->Rb.begin());
//  this->Rs.resize(rs_size);
//}
//
//
//uint16_t RankSupport::initRp(uint64_t digit){
//  uint16_t count = __builtin_popcount(digit);
//  return count;
//}
//
//
//uint64_t RankSupport::Rank(uint64_t x){
//  size_t rb_index = x / this->rb_size;
//  size_t rs_index = x / this->rs_size;
//  uint64_t bits =this->B.readIndex64(rb_index*this->rb_size,x%this->rb_size);
//
//  // popcnt instruction is used instead of the pattern table for 1/2 w bits.
//  return this->Rb[rb_index] + this->Rs[rs_index] + initRp(bits);
//}
//
//
//
//
//
//
//
//uint64_t RankSupport::Rank1(uint64_t x){
//    size_t rb_index = x / this->rb_size;
//    size_t rs_index = x / this->rs_size;
//    std::cout<< " target-"<<  rb_index<<std::endl;
//    std::cout<< " target--"<<  rs_index<<std::endl;
//    std::string temp = "";
//    boost::to_string(this->b,temp);
//
//    std::string target;
//    if(x!=this->b.size()){
//        target = temp.substr(rb_index*this->rb_size,x%this->rb_size);
//    } else{
//        target = temp.substr((rb_index-1)*this->rb_size,b.size()-(rb_index-1)*this->rb_size);
//
//    }
//
//
//    if(target == ""){
//        target = "0";
//    }
//
//    uint64_t i = std::stoi(target, nullptr, 2);
//    if(x!=this->b.size()){
////    if(x!=this->b.size()){
//        std::cout<< " target "<< rb_index*this->rb_size<<rs_index<<std::endl;
//        return this->Rb[rb_index] + this->Rs[rs_index] + __builtin_popcount(i);
//    }else{
//        std::cout<<(rb_index-1)*this->rb_size <<std::endl;
////        std::cout<< " target "<<   this->Rs[rs_index-1]<<std::endl;
//        return this->Rb[rb_index-1] + this->Rs[rs_index-1] + __builtin_popcount(i);
//
//    }
