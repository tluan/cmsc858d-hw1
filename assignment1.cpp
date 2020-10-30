#include <iostream>
#include<vector>
#include <cstdint>
#include <map>
#include<vector>
#include <cstdint>
#include <map>
#include <iostream>
#include <math.h>
using namespace std;
vector<string> rphelper(int i ){
    vector<string> temp = {};
    vector<string> temp2 = {};
    if(i==0){
        return{};
    }
    else{
        temp = rphelper(i-1);
        if(temp.size()>0) {
            for (string q:temp) {
//                cout << q << endl;
                temp2.push_back(q + "0");
                temp2.push_back(q + "1");
                temp2.push_back(q);
            }
        }else{
            temp2.push_back("0");
            temp2.push_back( "1");
        }
    }
    return temp2;
}


map<uint64_t,uint8_t> rpsupport(vector<string> temp){
    map<uint64_t,uint8_t> result;
    for(string i:temp){
        uint64_t f = std::stoi(i, nullptr, 2);

        result[f]=__builtin_popcount(f);
//       std::cout <<f<<" "<<__builtin_popcount(f)<<std::endl;
    }
    return result;
}

//int main(){
//    vector<string> temp = rphelper(4);
//    map<uint64_t,int> fq =  rpsupport(temp);
//    for (const auto& x : fq) {
//        std::cout << x.first << ": " << x.second << "\n";
//    }

//    for(string i:temp){
//        cout<<i<<endl;
//    }

//class bit_vector
//{
//    std::vector<uint64_t> byteInput;
//    uint64_t byteInputSizeof64;
//
//    // std::map<,int>;
//  public:
//   bit_vector(size_t const count);
//   bit_vector();
//   uint64_t rank1(uint64_t i);
//   void read(std::vector<bool> inBytes);
//   void write(uint16_t i, bool const val);
//   void write64(uint16_t i, uint64_t const val);
//   bool readIndex(size_t const i);
//   uint64_t readIndex64(size_t const i,size_t const w);
//
//};
//
//
//
//bit_vector::bit_vector(){
//  bit_vector(200);
//}
//bit_vector::bit_vector(size_t const lengthVec){
//  //memory of size lengthVec, length of input byte vectgor
//
//  if(lengthVec%64 == 0){
//    byteInput.resize(lengthVec  / 64);
//    this->byteInputSizeof64 = lengthVec/64;
//  }else{
//    byteInput.resize(lengthVec/64 + 1);
//    this->byteInputSizeof64 = lengthVec/64 + 1;
//  }
//  for (uint64_t i = 0; i < this->byteInputSizeof64; ++i)
//    this->byteInput[i] = 0;
//
//}
//void bit_vector::read(std::vector<bool> inBytes){
//  uint64_t sizeInBytes = inBytes.size();
//
//  for (uint64_t i = 0; i < inBytes.size(); ++i){
//    if(inBytes[i]){
//      this->byteInput[i / 64] |= static_cast<uint64_t>(1)  << ( 63- (i % 64));
//    }
//  }
//
//}
//
//void bit_vector::write(uint16_t i, bool const val){
//  if(val){
//    byteInput[i / 64] |= static_cast<uint64_t>(1)<< ( 63- (i % 64));
//    }
//}
//
//void bit_vector::write64(uint16_t i, uint64_t const val){
//  this->byteInput[i / 64] = val;
//}
//
//
//bool bit_vector::readIndex(size_t const i)  {
//    return (this->byteInput[i / 64] >> (63 - (i % 64))) & 1;
//}
//
//
//uint64_t bit_vector::readIndex64(size_t const i,size_t const w)  {
//    uint64_t front = i / 64;
//    uint64_t back = (i+w)/ 64;
//    if(front == back){
//      uint64_t temp = this->byteInput[front];
//      temp<<(i % 64);
//      temp>>(i % 64)+63-(i+w)%64;
//      return temp;
//    }else{
//       uint64_t temp = this->byteInput[front];
//       temp<<(i % 64);
//       uint64_t tempBack = this->byteInput[back];
//       tempBack>>63-(i+w)%64;
//       tempBack<<63-(i+w)%64;
//       return tempBack|temp;
//    }
//}
//
//// void bit_vector::readIndex(uint16_t i,uint16_t w){
//
//// }
//// void bit_vector::generateRb(uint16_t i){
//
//
//// }
//
//
//
//
//// uint64_t  bit_vector::rank1(uint64_t i){
////   return
//// }
//
//
//
//int main() {
//    bit_vector B(5);
//    std::vector<bool> inBytes;
//    inBytes.push_back(1);
//    inBytes.push_back(1);
//    inBytes.push_back(0);
//    inBytes.push_back(1);
//    inBytes.push_back(0);
//    B.read(inBytes);
//    std::cout<<B.readIndex(2)<<std::endl;
//    uint64_t a = 24;
//     std::cout<< __builtin_popcount(0xFFFF)<<std::endl;
//    uint8_t t = 1;//101/01100
//    std::cout<< t<<std::endl;
//    uint8_t t1 = 3;//010110/10
//    t = t>>5;
//    std::cout<< t<<std::endl;
//    t = t<<5;
//    std::cout<< t<<std::endl;
//}