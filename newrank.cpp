// using namespace std;
#include <iostream>       // std::cout
#include <string>         // std::string
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <map>
#include "newrank.h"
#include <divsufsort.h>
#include "assignment1.cpp"
#include <fstream>

class RankSupport{
    uint64_t rb_size;
    uint64_t rs_size;
    uint64_t input_size;
    std::vector<uint16_t> Rb;
    std::vector<uint64_t> Rs;
    boost::dynamic_bitset<> b;
    std::map<uint64_t, uint8_t> Rp;



public:
    RankSupport(boost::dynamic_bitset<> inBytes);
    RankSupport();
    void initRs();
    void initRb();
    void initRp();
    uint16_t initRp(uint64_t digit);
    uint64_t Rank1(uint64_t x);
    uint64_t Rank0(uint64_t x);
    boost::dynamic_bitset<> reverse(boost::dynamic_bitset<> b);
    uint64_t Select1(uint64_t x);
    uint64_t Select0(uint64_t x);
    uint64_t bsearch(uint64_t p, uint64_t r, uint64_t num);
    uint64_t bsearch0(uint64_t p, uint64_t r, uint64_t num);
    uint64_t overhead();
    void load(string& fname);
    void save(string& fname);
    boost::dynamic_bitset<> getB();

//       uint64_t Rank(uint64_t x);





};


RankSupport::RankSupport(boost::dynamic_bitset<> inBytes){
    this->input_size = inBytes.size();
    this->rs_size = log2(this->input_size)*log2(this->input_size)/2;
    this->rb_size = log2(this->input_size)/2;

    this->b.resize(this->input_size);
    for(int i = 0; i < this->input_size; i ++){
        b[i] = inBytes[i];
    }

//    std::cout << "B1 RAN push(0) operation : "
//         <<b << std::endl;
    initRs();
    initRb();
    initRp();


}
boost::dynamic_bitset<> RankSupport::reverse(boost::dynamic_bitset<> b) {
    boost::dynamic_bitset<> c(b.size(),0) ;
    for(int i = 0; i <  b.size(); i ++){
        c[i] = b[i];
    }
    for(std::size_t i = 0; i < c.size()/2; ++i) {
        bool t = b[i];
        c[i] = b[b.size()-i-1];
        c[b.size()-i-1] = t;
    }
    return c;
}
void RankSupport::initRs(){
    boost::dynamic_bitset<> c = this->reverse(this->b);

    uint64_t rs_sum = 0;
    for (uint64_t i =0; i < this->input_size; ++i) {

        if ((i ) % (this->rs_size) == 0) {
//            std::cout<<"this"<< rs_sum<<std::endl;
        //    std::cout <<"count"<< i<<" "<<rs_sum<<std::endl;
            this->Rs.push_back(rs_sum);


        }

        uint64_t count = c[i];

        rs_sum += count;


    }
//    std::cout <<"t1s"<<std::endl;
//    for(int i=0; i < this->Rs.size(); i++)
//        std::cout << this->Rs.at(i) << ' ';
//    std::cout <<std::endl;

}

void RankSupport::save(string& fname){
    ofstream myfile;
    myfile.open (fname);
    string buffer;
    to_string(b, buffer);
    myfile << buffer<<' ';
    for(uint64_t i:Rs){

        myfile << i<<' ';
    }
    myfile << "EOF"<<' ';
    for(uint16_t j:Rb){
        myfile << j<<' ';
    }
    for(uint16_t j:Rb){
        myfile << j<<' ';
    }
    myfile << "EOF"<<' ';
    for( auto it = this->Rp.begin(); it != this->Rp.end(); ++it )
    {
        uint64_t key = it->first;
        uint8_t & value = it->second;
//        cout<<key<<" "<<value<<'\n';
        myfile << (int)key<<' ';
        myfile <<(int)value<<' ' ;
    }
    myfile.close();
}
void RankSupport::load(string& fname){
    string line;
    ifstream myfile (fname);
    if (myfile.is_open())
    {   string a;
        myfile >> a;

        this->b = boost::dynamic_bitset<>(a);
//        cout<<this->b<<endl;
        string c;
        while (myfile >> c&&c!="EOF")
        {
//            cout<<c<<endl;
           this->Rb.push_back((uint64_t)std::stoi(c));
        }
//        myfile >> c;
        while (myfile >> c&&c!="EOF")
        {
//            cout<<c<<endl;
            this->Rs.push_back((uint64_t)std::stoi(c));
        }
        string d;
        while (myfile >> c>>d)
        {
//            cout<<c<<endl;
            this->Rp[(uint64_t)std::stoi(c)] = (uint16_t)std::stoi(d);
        }
    }

}



void RankSupport::initRb(){
    uint64_t rb_sum = 0;
    boost::dynamic_bitset<> c = this->reverse(this->b);
    for (uint64_t i = 0; i < this->input_size; i++) {
        if(i % (this->rb_size) == 0){


//            std::cout <<rb_sum<<std::endl;
            if(i % (this->rs_size) == 0){
                rb_sum = 0;

            }
//            std::cout <<rb_sum<<std::endl;
            this->Rb.push_back(rb_sum);

        }




        uint64_t count = c[i];
        rb_sum += count;

    }
//    std::cout <<"mark"<<std::endl;
//    for(int i=0; i < this->Rb.size(); i++)
//        std::cout << this->Rb.at(i) << ' ';
//    std::cout <<std::endl;
}



void RankSupport::initRp() {
    std::vector<string> temp = rphelper(rb_size);
    std::map<uint64_t,uint8_t> fq =  rpsupport(temp);
    for( auto it =fq.begin(); it !=fq.end(); ++it )
    {
        uint64_t key = it->first;
        uint8_t & value = it->second;
//        cout<<key<<" "<<value<<'\n';
//        myfile << key<<' '<<value ;
    }
    this->Rp = fq;
}
uint64_t RankSupport::overhead(){
    uint64_t  size = 0;
    size = size+Rs.size()*64+Rb.size()*64;
    int rpsize = 64*8*Rp.size();
    size = size + rpsize;
    return size;
}
uint64_t RankSupport::Rank1(uint64_t x){
    size_t rb_index = x / this->rb_size;
    size_t rs_index = x / this->rs_size;
//    std::cout<< " target-"<<  rb_index<<std::endl;
//    std::cout<< " target--"<<  rs_index<<std::endl;
    std::string temp = "";
    boost::to_string(this->b,temp);

    std::string target;
    if(x!=this->b.size()){
        target = temp.substr(rb_index*this->rb_size,x%this->rb_size);
    } else{
        if(x% rs_size!=0){
            if(x% rb_size==0){
                target = temp.substr((rb_index-1)*this->rb_size,b.size()-(rb_index-1)*this->rb_size);
            }else{
                target = temp.substr((rb_index)*this->rb_size,b.size()-(rb_index)*this->rb_size);}

        }else{
            target = temp.substr((rb_index-1)*this->rb_size,b.size()-(rb_index-1)*this->rb_size);


        }

    }
    if(target == ""){
        target = "0";
    }

    uint64_t i = std::stoi(target, nullptr, 2);

    if(x!=this->b.size()){
//    if(x!=this->b.size()){

        return this->Rb[rb_index] + this->Rs[rs_index] + __builtin_popcount(i);
    }else{

        if(x% rs_size!=0){
            if(x% rb_size==0){
                return this->Rb[rb_index-1] + this->Rs[rs_index] + __builtin_popcount(i);
            }else{

                return this->Rb[rb_index ] + this->Rs[rs_index] + __builtin_popcount(i);}
        }else{
            return this->Rb[rb_index - 1] + this->Rs[rs_index - 1] + __builtin_popcount(i);}


    }

}
boost::dynamic_bitset<> RankSupport::getB(){
    return b;
}
uint64_t RankSupport::Rank0(uint64_t x){
    uint64_t r1 = Rank1(x);
    return x-r1;
}

uint64_t RankSupport::Select1(uint64_t x){

    return this->bsearch(1,b.size(),x);

}
uint64_t RankSupport::Select0(uint64_t x){

    return this->bsearch0(1,b.size(),x);
}
uint64_t RankSupport::bsearch(uint64_t p, uint64_t r, uint64_t num){

    if (p <= r) {

        int mid = (p + r)/2;
//        std::cout<<"mid"<<std::endl;
//        std::cout<<mid<<std::endl;
//        std::cout<<(Rank1(mid) < num)<<std::endl;
        if (this->Rank1(mid) == num){
//            std::cout<<Rank1(mid)<<std::endl;
//            std::cout<<"done"<<std::endl;
            return mid ;}
        if (this->Rank1(mid) > num){
//            std::cout<<"p2"<<std::endl;
            return bsearch( p, mid-1, num);}
        if (this->Rank1(mid) < num){
//            std::cout<<"p3"<<std::endl;
            return bsearch( mid+1, r, num);}
    }
    return 0;

}
uint64_t RankSupport::bsearch0(uint64_t p, uint64_t r, uint64_t num){

    if (p <= r) {

        int mid = (p + r)/2;
//        std::cout<<"mid"<<std::endl;
//        std::cout<<mid<<std::endl;
//        std::cout<<(Rank0(mid) < num)<<std::endl;
        if (this->Rank0(mid) == num){
//            std::cout<<Rank0(mid)<<std::endl;
//            std::cout<<"done"<<std::endl;
            return mid ;}
        if (this->Rank0(mid) > num){
//            std::cout<<"p2"<<std::endl;
            return bsearch0( p, mid-1, num);}
        if (this->Rank0(mid) < num){
//            std::cout<<"p3"<<std::endl;
            return bsearch0( mid+1, r, num);}
    }
    return 0;

}

//class BwtHelper{
//    std::string in_string;
//    std::string pre_bwt;
//    std::string post_bwt;
//    char *Text;
//    int n;
//    int *SA;
//
//public:
//    BwtHelper(std::string);
//    std::string calprebwt();
//    std::string calpostbwt();
//    void free1();
//};
//BwtHelper::BwtHelper(std::string in){
//    this->in_string = in;
//    Text = const_cast<char *>(in_string.data());
//    n = strlen(Text);
//    SA = (int *)malloc(n * sizeof(int));
//    divsufsort((unsigned char *)Text, SA, n);
//}
//std::string BwtHelper::calprebwt() {
//
//
//
//    std::string temp = "$";
//    for(int i = 0; i < n; ++i) {
//        temp = temp + Text[SA[i]];
//
//
//    }
//
//    return temp;
//
//}
//std::string BwtHelper::calpostbwt() {
//
//    char *SA2 = (char  *)malloc(n * sizeof( char ));
//    divbwt((unsigned char *)Text, reinterpret_cast<sauchar_t *>(SA2), NULL, n);
//    int temp = 0;
//    for(int i = 0;i < n; i++){
//        if(SA[i]==0){
//            temp = i;
//        }
//    }
//    std::string tempstr = "";
//    for(int j =0; j < n; j++) {
//
//        tempstr = tempstr+  SA2[j];
//        if(j == temp ){
//            tempstr = tempstr+'$';
//        }
//    }
//
//
//    return  tempstr;
//
//}
//
//void BwtHelper::free1() {
//    free(SA);
//
//}

//class Occ{
//    std::map<char,boost::dynamic_bitset<>> data;
//    std::map<char,std::vector<int>> procceed_;
//    std::set <char> aphabet;
//    std::string bst = "";
////    BwtHelper  helper = BwtHelper();
//
//
//
//public:
//    Occ(std::string & bwt);
//    void accum();
//    std::map<char,uint64_t> pos1(std::string pre_bwt);
//    std::map<char,std::vector<int>> getProcceed();
//
////    std::string bwt_pos(std::string pre_bwt);
////    {
////        // resize the 5 bitvectors to the length of the bwt:
////        for(int i = 0; i < apsize;i ++){
////            data[i].resize(bwt.length());
////        }
////
////        for (size_t i = 0; i < bwt.size(); ++i)
////            data[to_index(bwt[i])].write(i, 1);
////    }
//};
//
//Occ::Occ(std::string & bwt){
//    this->bst = bwt;
////    helper = BwtHelper(bwt);
//    for(int i = 0;i < bwt.length();i++){
//        aphabet.insert(bwt.at(i));
//    }
//    std::set <char > :: iterator itr;
//
//    for (itr = aphabet.begin(); itr != aphabet.end(); ++itr)
//    {
//        data[*itr].resize(bwt.size());
//
//    }
//    for(int i = 0;i < bwt.length();i++){
//        data[bwt[i]][bwt.length()-1-i] = 1;
//    }
//
//    for(auto it = data.cbegin(); it != data.cend(); ++it)
//    {
//
//        std::cout << it->first << " " << it->second<< "\n";
//    }
//    accum();
//}
//
//std::map<char,std::vector<int>> Occ::getProcceed(){
//    return this->procceed_;
//}
//void Occ::accum(){
//
//
//    std::set <char > :: iterator itr;
//    for (int q = 1; q < bst.length()+1;q++) {
//
//        for (itr = aphabet.begin(); itr != aphabet.end(); ++itr) {
//
//            RankSupport temp = RankSupport(data[*itr]);
//            std::cout << *itr<< "\n";
//            this->procceed_[*itr].push_back(temp.Rank1(q));
//            std::cout << "data[*itr]"<<data[*itr]<< "\n";
//            std::cout << "temp.Rank1(q) "<<q<<" "<<temp.Rank1(q)<<"\n";
//
//
//
//        }
//    }
//
//    //std::cout<< procceed_.size()<<" ";
//    for(auto it = procceed_.cbegin(); it != procceed_.cend(); ++it)
//    {
//        std::vector<int> tep = it->second;
//        std::cout<< it->first<<" ";
//        for(int k = 0; k < tep.size();k++){
//            std::cout<<tep[k]<<" ";
//        }
//        std::cout<<std::endl;
////        std::cout << it->first << " " << it->second<< "\n";
//    }
//
//}
//
//
//std::map<char,uint64_t>pos1(std::string pre_bwt){
//    std::map<char,uint64_t> result;
//    int i = 0;
//    for (char ch : pre_bwt)
//    {
//        if( result.find(ch) == result.end()){
//            result[ch] = i;
//        }
//
//        i = i + 1;
//    }
//    return result;
//}
//
//
//
//size_t backward_search(std::string const & pattern,
//                       std::string const & bwt,
//                       std::map<char,uint64_t>& count_table,
//                       Occ & occurance_table)
//{
//    int64_t i = pattern.size() - 1;
//    size_t a = 0;
//    size_t b = bwt.size() - 1;
//    std::cout<<b<<std::endl;
//    std::map<char,std::vector<int>> occ_t = occurance_table.getProcceed();
//    while ((a <= b) && (i >= 0))
//    {
//        char c = pattern[i];
//        if(a!=0){
//
//            a = count_table[c] + occ_t[c][a-1];
//            std::cout<<"a:"<<a<<std::endl;
//
//            std::cout<<"char:"<<c<<std::endl;
//            std::cout<<"count:"<<count_table[c]<<std::endl;
//            std::cout<<"occ_:"<<occ_t[c][a-1]<<std::endl;
//
//        }else{
//
//            a = count_table[c];
//            std::cout<<"a:"<<a<<std::endl;
//            std::cout<<"char:"<<c<<std::endl;
//
//            std::cout<<"count:"<<count_table[c]<<std::endl;
//            std::cout<<"occ_:"<<0<<std::endl;
//        }
//        std::cout<<"b"<<b<<std::endl;
//        std::cout<<"bcount:"<<count_table[c]<<std::endl;
//        std::cout<<"bocc_:"<<occ_t[c][b]<<std::endl;
//        std::cout<<"t1:"<<occ_t[c][b-1]<<std::endl;
//
//
//        i = i - 1;
//    }
//    if (b < a)
//        return 0;
//    else
//        return a;
//}
//
//
//
//int main() {
//    printf("works!\n");
//
//
//
////  s1.accum();
//    BwtHelper s = BwtHelper("atcgatcgatcgatcga");
//    std::string post =s.calpostbwt();
//    std::string pre = s.calprebwt();
//    std::cout <<post<<std::endl;
//    Occ s1 = Occ(post);
//    s.free1();
//    std::map<char,uint64_t> temp = pos1(s.calprebwt());
//
//    for (auto itr = temp.begin(); itr != temp.end(); ++itr)
//    {
//        std::cout << itr->first << " " << itr->second<< "\n";
//
//    }
//    std::cout<<backward_search("ac",post,temp,s1)<<std::endl;
//
//
//    std::cout<<boost::dynamic_bitset<>(17, 15);
//    RankSupport new1 = RankSupport(boost::dynamic_bitset<>(18, 131087));
//    std::cout<<boost::dynamic_bitset<>(18, 131087)<<std::endl;
//    std::cout<<new1.Rank1(18)<<std::endl;
//    return 0;
//
//}
//

//// using namespace std;
//#include <iostream>       // std::cout
//#include <string>         // std::string
//#include <boost/dynamic_bitset.hpp>
//#include <vector>
//#include <map>
//#include "newrank.h"
//#include <divsufsort.h>
//#include "assignment1.cpp"
// class RankSupport{
//     uint64_t rb_size;
//     uint64_t rs_size;
//     uint64_t input_size;
//     std::vector<uint16_t> Rb;
//     std::vector<uint64_t> Rs;
//     boost::dynamic_bitset<> b;
//     std::map<uint64_t, uint8_t> Rp;
//
//
//
//
// public:
//     RankSupport(boost::dynamic_bitset<> inBytes);
//       RankSupport();
//       void initRs();
//       void initRb();
//       void initRp();
////       uint16_t initRp(uint64_t digit);
//       uint64_t Rank1(uint64_t x);
//       uint64_t Rank0(uint64_t x);
//       boost::dynamic_bitset<> reverse(boost::dynamic_bitset<> b);
//       uint64_t Select1(uint64_t x);
//       uint64_t Select0(uint64_t x);
//       uint64_t bsearch(uint64_t p, uint64_t r, uint64_t num);
//       uint64_t bsearch0(uint64_t p, uint64_t r, uint64_t num);
//       boost::dynamic_bitset<> getB();
//       uint64_t overhead();
//
////       uint64_t Rank(uint64_t x);
//
//
//
//
//
// };
//
//
//RankSupport::RankSupport(boost::dynamic_bitset<> inBytes) {
//    this->input_size = inBytes.size();
//    this->rs_size = log2(this->input_size) * log2(this->input_size) / 2;
//    this->rb_size = log2(this->input_size) / 2;
//
//    this->b.resize(this->input_size);
//    for (int i = 0; i < this->input_size; i++) {
//        b[i] = inBytes[i];
//
////    std::cout << "B1 RAN push(0) operation : "
////         <<b << std::endl;
//        initRs();
//        initRb();
//
//
//    }
//}
//
//void RankSupport::initRp() {
//    vector<string> temp = rphelper(rb_size);
//    map<uint64_t,uint8_t> fq =  rpsupport(temp);
//    this->Rp = fq;
//}
//
//
//
//
//
//uint64_t RankSupport::overhead(){
//    uint64_t  size = 0;
//    size = size+rb_size+rs_size;
//    int rpsize = 64*8;
//    size = size + rpsize;
//    return size;
//}
//
//boost::dynamic_bitset<> RankSupport::getB(){
//    return b;
//}
//boost::dynamic_bitset<> RankSupport::reverse(boost::dynamic_bitset<> b) {
//    boost::dynamic_bitset<> c(b.size(),0) ;
//    for(int i = 0; i <  b.size(); i ++){
//        c[i] = b[i];
//    }
//    for(std::size_t i = 0; i < c.size()/2; ++i) {
//        bool t = b[i];
//        c[i] = b[b.size()-i-1];
//        c[b.size()-i-1] = t;
//    }
//    return c;
//}
//void RankSupport::initRs(){
//    boost::dynamic_bitset<> c = this->reverse(this->b);
//
//    uint64_t rs_sum = 0;
//    for (uint64_t i =0; i < this->input_size; ++i) {
//
//        if ((i ) % (this->rs_size) == 0) {
////            std::cout<<"this"<< rs_sum<<std::endl;
//            std::cout <<"count"<< i<<" "<<rs_sum<<std::endl;
//            this->Rs.push_back(rs_sum);
//
//
//        }
//
//        uint64_t count = c[i];
//
//        rs_sum += count;
//
//
//    }
//    std::cout <<"t1s"<<std::endl;
//    for(int i=0; i < this->Rs.size(); i++)
//        std::cout << this->Rs.at(i) << ' ';
//    std::cout <<std::endl;
//
//}
//
//void RankSupport::initRb(){
//    uint64_t rb_sum = 0;
//    boost::dynamic_bitset<> c = this->reverse(this->b);
//    for (uint64_t i = 0; i < this->input_size; i++) {
//        if(i % (this->rb_size) == 0){
//
//
////            std::cout <<rb_sum<<std::endl;
//            if(i % (this->rs_size) == 0){
//                rb_sum = 0;
//
//            }
//            std::cout <<rb_sum<<std::endl;
//            this->Rb.push_back(rb_sum);
//
//        }
//
//
//
//
//        uint64_t count = c[i];
//        rb_sum += count;
//
//    }
//    std::cout <<"mark"<<std::endl;
//    for(int i=0; i < this->Rb.size(); i++)
//        std::cout << this->Rb.at(i) << ' ';
//    std::cout <<std::endl;
//}
//
//
//
////void RankSupport::initRp(){
////    uint64_t blocksize = this->rb_size;
////    std::map<boost::dynamic_bitset<>, uint64_t> m;
////
////
////}
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
//        if(x% rs_size!=0){
//            if(x% rb_size==0){
//                target = temp.substr((rb_index-1)*this->rb_size,b.size()-(rb_index-1)*this->rb_size);
//            }else{
//                target = temp.substr((rb_index)*this->rb_size,b.size()-(rb_index)*this->rb_size);}
//
//        }else{
//        target = temp.substr((rb_index-1)*this->rb_size,b.size()-(rb_index-1)*this->rb_size);
//
//
//    }
//
//       }
//    if(target == ""){
//        target = "0";
//    }
//
//    uint64_t i = std::stoi(target, nullptr, 2);
//
//   if(x!=this->b.size()){
////    if(x!=this->b.size()){
//
//        return this->Rb[rb_index] + this->Rs[rs_index] + __builtin_popcount(i);
//    }else{
//
//       if(x% rs_size!=0){
//           if(x% rb_size==0){
//               return this->Rb[rb_index-1] + this->Rs[rs_index] + __builtin_popcount(i);
//           }else{
//
//           return this->Rb[rb_index ] + this->Rs[rs_index] + __builtin_popcount(i);}
//       }else{
//        return this->Rb[rb_index - 1] + this->Rs[rs_index - 1] + __builtin_popcount(i);}
//
//
//    }
//
//}
//
//uint64_t RankSupport::Rank0(uint64_t x){
//    uint64_t r1 = Rank1(x);
//    return x-r1;
//}
//
//uint64_t RankSupport::Select1(uint64_t x){
//
//    return this->bsearch(1,b.size(),x);
//
//}
//uint64_t RankSupport::Select0(uint64_t x){
//
//    return this->bsearch0(1,b.size(),x);
//}
//uint64_t RankSupport::bsearch(uint64_t p, uint64_t r, uint64_t num){
//
//    if (p <= r) {
//
//        int mid = (p + r)/2;
////        std::cout<<"mid"<<std::endl;
////        std::cout<<mid<<std::endl;
////        std::cout<<(Rank1(mid) < num)<<std::endl;
//        if (this->Rank1(mid) == num){
////            std::cout<<Rank1(mid)<<std::endl;
////            std::cout<<"done"<<std::endl;
//            return mid ;}
//        if (this->Rank1(mid) > num){
////            std::cout<<"p2"<<std::endl;
//            return bsearch( p, mid-1, num);}
//        if (this->Rank1(mid) < num){
////            std::cout<<"p3"<<std::endl;
//            return bsearch( mid+1, r, num);}
//    }
//    return 0;
//
//}
//uint64_t RankSupport::bsearch0(uint64_t p, uint64_t r, uint64_t num){
//
//    if (p <= r) {
//
//        int mid = (p + r)/2;
////        std::cout<<"mid"<<std::endl;
////        std::cout<<mid<<std::endl;
////        std::cout<<(Rank0(mid) < num)<<std::endl;
//        if (this->Rank0(mid) == num){
////            std::cout<<Rank0(mid)<<std::endl;
////            std::cout<<"done"<<std::endl;
//            return mid ;}
//        if (this->Rank0(mid) > num){
////            std::cout<<"p2"<<std::endl;
//            return bsearch0( p, mid-1, num);}
//        if (this->Rank0(mid) < num){
////            std::cout<<"p3"<<std::endl;
//            return bsearch0( mid+1, r, num);}
//    }
//    return 0;
//
//}
//
//class BwtHelper{
//    std::string in_string;
//    std::string pre_bwt;
//    std::string post_bwt;
//    char *Text;
//    int n;
//    int *SA;
//
//public:
//    BwtHelper(std::string);
//    std::string calprebwt();
//    std::string calpostbwt();
//    void free1();
//};
//BwtHelper::BwtHelper(std::string in){
//    this->in_string = in;
//    Text = const_cast<char *>(in_string.data());
//    n = strlen(Text);
//    SA = (int *)malloc(n * sizeof(int));
//    divsufsort((unsigned char *)Text, SA, n);
//}
//std::string BwtHelper::calprebwt() {
//
//
//
//    std::string temp = "$";
//    for(int i = 0; i < n; ++i) {
//        temp = temp + Text[SA[i]];
//
//
//    }
//
//    return temp;
//
//}
//std::string BwtHelper::calpostbwt() {
//
//    char *SA2 = (char  *)malloc(n * sizeof( char ));
//    divbwt((unsigned char *)Text, reinterpret_cast<sauchar_t *>(SA2), NULL, n);
//    int temp = 0;
//    for(int i = 0;i < n; i++){
//        if(SA[i]==0){
//            temp = i;
//        }
//    }
//    std::string tempstr = "";
//    for(int j =0; j < n; j++) {
//
//        tempstr = tempstr+  SA2[j];
//        if(j == temp ){
//            tempstr = tempstr+'$';
//        }
//    }
//
//
//    return  tempstr;
//
//}
//
//void BwtHelper::free1() {
//    free(SA);
//
//}
//
//class Occ{
//    std::map<char,boost::dynamic_bitset<>> data;
//    std::map<char,std::vector<int>> procceed_;
//    std::set <char> aphabet;
//    std::string bst = "";
////    BwtHelper  helper = BwtHelper();
//
//
//
//public:
//    Occ(std::string & bwt);
//    void accum();
//    std::map<char,uint64_t> pos1(std::string pre_bwt);
//    std::map<char,std::vector<int>> getProcceed();
//
////    std::string bwt_pos(std::string pre_bwt);
////    {
////        // resize the 5 bitvectors to the length of the bwt:
////        for(int i = 0; i < apsize;i ++){
////            data[i].resize(bwt.length());
////        }
////
////        for (size_t i = 0; i < bwt.size(); ++i)
////            data[to_index(bwt[i])].write(i, 1);
////    }
//};
//
//Occ::Occ(std::string & bwt){
//    this->bst = bwt;
////    helper = BwtHelper(bwt);
//    for(int i = 0;i < bwt.length();i++){
//        aphabet.insert(bwt.at(i));
//    }
//    std::set <char > :: iterator itr;
//
//    for (itr = aphabet.begin(); itr != aphabet.end(); ++itr)
//    {
//        data[*itr].resize(bwt.size());
//
//    }
//    for(int i = 0;i < bwt.length();i++){
//        data[bwt[i]][bwt.length()-1-i] = 1;
//    }
//
//    for(auto it = data.cbegin(); it != data.cend(); ++it)
//    {
//
//        std::cout << it->first << " " << it->second<< "\n";
//    }
//    accum();
//}
//
//std::map<char,std::vector<int>> Occ::getProcceed(){
//    return this->procceed_;
//}
//void Occ::accum(){
//
//
//    std::set <char > :: iterator itr;
//    for (int q = 1; q < bst.length()+1;q++) {
//
//        for (itr = aphabet.begin(); itr != aphabet.end(); ++itr) {
//
//            RankSupport temp = RankSupport(data[*itr]);
//            std::cout << *itr<< "\n";
//            this->procceed_[*itr].push_back(temp.Rank1(q));
//            std::cout << "data[*itr]"<<data[*itr]<< "\n";
//            std::cout << "temp.Rank1(q) "<<q<<" "<<temp.Rank1(q)<<"\n";
//
//
//
//        }
//    }
//
//    //std::cout<< procceed_.size()<<" ";
//    for(auto it = procceed_.cbegin(); it != procceed_.cend(); ++it)
//    {
//        std::vector<int> tep = it->second;
//        std::cout<< it->first<<" ";
//        for(int k = 0; k < tep.size();k++){
//            std::cout<<tep[k]<<" ";
//        }
//        std::cout<<std::endl;
////        std::cout << it->first << " " << it->second<< "\n";
//    }
//
//}
//
//
//std::map<char,uint64_t>pos1(std::string pre_bwt){
//    std::map<char,uint64_t> result;
//    int i = 0;
//    for (char ch : pre_bwt)
//    {
//            if( result.find(ch) == result.end()){
//                result[ch] = i;
//            }
//
//            i = i + 1;
//    }
//    return result;
//}
//
//
//
//size_t backward_search(std::string const & pattern,
//             std::string const & bwt,
//             std::map<char,uint64_t>& count_table,
//             Occ & occurance_table)
//{
//    int64_t i = pattern.size() - 1;
//    size_t a = 0;
//    size_t b = bwt.size() - 1;
//    std::cout<<b<<std::endl;
//    std::map<char,std::vector<int>> occ_t = occurance_table.getProcceed();
//    while ((a <= b) && (i >= 0))
//    {
//        char c = pattern[i];
//        if(a!=0){
//
//            a = count_table[c] + occ_t[c][a-1];
//            std::cout<<"a:"<<a<<std::endl;
//
//            std::cout<<"char:"<<c<<std::endl;
//            std::cout<<"count:"<<count_table[c]<<std::endl;
//            std::cout<<"occ_:"<<occ_t[c][a-1]<<std::endl;
//
//        }else{
//
//            a = count_table[c];
//            std::cout<<"a:"<<a<<std::endl;
//            std::cout<<"char:"<<c<<std::endl;
//
//            std::cout<<"count:"<<count_table[c]<<std::endl;
//            std::cout<<"occ_:"<<0<<std::endl;
//        }
//        std::cout<<"b"<<b<<std::endl;
//        std::cout<<"bcount:"<<count_table[c]<<std::endl;
//        std::cout<<"bocc_:"<<occ_t[c][b]<<std::endl;
//        std::cout<<"t1:"<<occ_t[c][b-1]<<std::endl;
//
//
//        i = i - 1;
//    }
//    if (b < a)
//        return 0;
//    else
//        return a;
//}
//
//
//
//int main() {
////
////    RankSupport new1 = RankSupport(boost::dynamic_bitset<>(16, 38730));
////    string d = "here.txt";
////    new1.save(d);
////    new1.load(d);
//    Occ o1 = Occ("test");
//    o1.readandwrote();
//
//
//    return 0;}
//  printf("works!\n");
//
//
//
////  s1.accum();
//  BwtHelper s = BwtHelper("atcgatcgatcgatcga");
//  std::string post =s.calpostbwt();
//  std::string pre = s.calprebwt();
//  std::cout <<post<<std::endl;
//  Occ s1 = Occ(post);
//  s.free1();
//  std::map<char,uint64_t> temp = pos1(s.calprebwt());
//
//    for (auto itr = temp.begin(); itr != temp.end(); ++itr)
//    {
//        std::cout << itr->first << " " << itr->second<< "\n";
//
//    }
//    std::cout<<backward_search("ac",post,temp,s1)<<std::endl;
//
//
//    std::cout<<boost::dynamic_bitset<>(17, 15);
//    RankSupport new1 = RankSupport(boost::dynamic_bitset<>(18, 131087));
//    std::cout<<boost::dynamic_bitset<>(18, 131087)<<std::endl;
//    std::cout<<new1.Rank1(18)<<std::endl;
//    return 0;
//
//}
