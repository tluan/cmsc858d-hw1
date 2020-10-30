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
class BwtHelper{
    std::string in_string;
    std::string pre_bwt;
    std::string post_bwt;
    char *Text;
    int n;
    int *SA;

public:
    BwtHelper(std::string);
    std::string calprebwt();
    std::string calpostbwt();
    void free1();
};
BwtHelper::BwtHelper(std::string in){
    this->in_string = in;
    Text = const_cast<char *>(in_string.data());
    n = strlen(Text);
    SA = (int *)malloc(n * sizeof(int));
    divsufsort((unsigned char *)Text, SA, n);
}
std::string BwtHelper::calprebwt() {



    std::string temp = "$";
    for(int i = 0; i < n; ++i) {
        temp = temp + Text[SA[i]];


    }

    return temp;

}
std::string BwtHelper::calpostbwt() {

    char *SA2 = (char  *)malloc(n * sizeof( char ));
    divbwt((unsigned char *)Text, reinterpret_cast<sauchar_t *>(SA2), NULL, n);
    int temp = 0;
    for(int i = 0;i < n; i++){
        if(SA[i]==0){
            temp = i;
        }
    }
    std::string tempstr = "";
    for(int j =0; j < n; j++) {

        tempstr = tempstr+  SA2[j];
        if(j == temp ){
            tempstr = tempstr+'$';
        }
    }


    return  tempstr;

}

void BwtHelper::free1() {
    free(SA);

}
class Occ{
    std::map<char,boost::dynamic_bitset<>> data;
    std::map<char,std::vector<int>> procceed_;
    std::set <char> aphabet;
    std::string bst = "";
//    BwtHelper  helper = BwtHelper();




public:
    Occ(std::string & bwt);
    void accum();
    std::map<char,uint64_t> pos1(std::string pre_bwt);
    std::map<char,std::vector<int>> getProcceed();
    void readandwrote();

//    std::string bwt_pos(std::string pre_bwt);
//    {
//        // resize the 5 bitvectors to the length of the bwt:
//        for(int i = 0; i < apsize;i ++){
//            data[i].resize(bwt.length());
//        }
//
//        for (size_t i = 0; i < bwt.size(); ++i)
//            data[to_index(bwt[i])].write(i, 1);
//    }
};

Occ::Occ(std::string & bwt){
    this->bst = bwt;
//    helper = BwtHelper(bwt);
    for(int i = 0;i < bwt.length();i++){
        aphabet.insert(bwt.at(i));
    }
    std::set <char > :: iterator itr;

    for (itr = aphabet.begin(); itr != aphabet.end(); ++itr)
    {
        data[*itr].resize(bwt.size());

    }
    for(int i = 0;i < bwt.length();i++){
        data[bwt[i]][bwt.length()-1-i] = 1;
    }

//    for(auto it = data.cbegin(); it != data.cend(); ++it)
//    {
//
//        std::cout << it->first << " " << it->second<< "\n";
//    }
    accum();
}

std::map<char,std::vector<int>> Occ::getProcceed(){
    return this->procceed_;
}
void Occ::accum(){


    std::set <char > :: iterator itr;
    for (int q = 1; q < bst.length()+1;q++) {

        for (itr = aphabet.begin(); itr != aphabet.end(); ++itr) {

            RankSupport temp = RankSupport(data[*itr]);
//            std::cout << *itr<< "\n";
            this->procceed_[*itr].push_back(temp.Rank1(q));
//            std::cout << "data[*itr]"<<data[*itr]<< "\n";
//            std::cout << "temp.Rank1(q) "<<q<<" "<<temp.Rank1(q)<<"\n";



        }
    }

    //std::cout<< procceed_.size()<<" ";
    for(auto it = procceed_.cbegin(); it != procceed_.cend(); ++it)
    {
        std::vector<int> tep = it->second;
//        std::cout<< it->first<<" ";
//        std::cout<<std::endl;
//        std::cout << it->first << " " << it->second<< "\n";
    }

}

void Occ::readandwrote() {
    string filenamein;
    string filenameout;
    cout << "Please enter bwocc build <input string> <output file> ";
    cin >> filenamein;
    cin >> filenamein;
    cin >> filenamein;
    cin >> filenameout;
//    cout << "The value you entered is " << i;
//    cout << " and its double is " << i*2 << ".\n"

}
std::map<char,uint64_t>pos1(std::string pre_bwt){
    std::map<char,uint64_t> result;
    int i = 0;
    for (char ch : pre_bwt)
    {
        if( result.find(ch) == result.end()){
            result[ch] = i;
        }

        i = i + 1;
    }
    return result;
}



pair<int, int> backward_search(std::string const & pattern,
                       std::string const & bwt,
                       std::map<char,uint64_t>& count_table,
                       std::map<char,std::vector<int>> occ)
{
//  int64_t i = pattern.size() - 1;
    size_t a = 0;
    size_t b = bwt.size() - 1;

//    std::cout<<b<<std::endl;
    std::map<char,std::vector<int>> occ_t = occ;

    for (int64_t i = pattern.size(); !((a > b) || (i < 1)); i -= 1) {
        char pattern_char = pattern[i - 1];
        a = (a == 0) ? count_table[pattern_char] : (count_table[pattern_char] + occ_t[pattern_char][a - 1]);

        b = occ_t[pattern_char][b] + count_table[pattern_char];
        b -= 1;
    }



    if (b < a){
//        std::cout<<a<<std::endl;
//        std::cout<<b+1<<std::endl;
        return std::make_pair(a, a);}
    else{
//        std::cout<<a<<std::endl;
//        std::cout<<b+1<<std::endl;
        return std::make_pair(a, b+1);}
}



