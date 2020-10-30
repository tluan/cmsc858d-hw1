#include <string.h>
#include "bws.cpp"
#include <sys/time.h>
// Created by Kanzaki Mirai on 10/29/20.
//

long int now_ms() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int main(int argc, char* argv[]){
//    long int start_ms = now_ms();
//    RankSupport F = RankSupport(boost::dynamic_bitset<>(50000, 1317));
//    long int start_ms = now_ms();
//    for (int i =0;i<20;i++){
//        F.Rank1(2029+i);
//    }
//    long int end_ms = now_ms();
//    std::cout<<"ms:"<<end_ms - start_ms<<std::endl;




    if (argc != 4) {
        printf("error: wrong argument.");
        return -1;
    }

    char *arg1 = argv[1];
    char *arg2 = argv[2];
    char *arg3 = argv[3];
//    BwtHelper s = BwtHelper("atcgatcgatcgatcga");;
//    std::string post="";
//    std::string pre="";
//    Occ s1 = Occ(post);
    if (strcmp(arg1, "build") == 0) {


        ifstream infile(arg2);
        if (infile.good()) {
            string sLine;
            getline(infile, sLine);

            int str_size = sLine.size();

            set<char> strSet;
            for (int i = 0; i < str_size; i++){
                strSet.insert(sLine[i]);
            }

            int uniq_alpha_num = strSet.size();
            std::cout<<"here"<<std::endl;
            std::cout<<uniq_alpha_num<<std::endl;
            std::cout<<str_size<<std::endl;


            BwtHelper s = BwtHelper(sLine);
            std::string post =s.calpostbwt();
//            std::cout<<sLine<<std::endl;
//            std::cout<<post<<std::endl;
            std::string pre = s.calprebwt();
            Occ  s1 = Occ(post);
            s.free1();
            std::map<char,uint64_t> temp = pos1(s.calprebwt());
            ofstream myfile;
            myfile.open (arg3);
            string buffer;
            myfile << post <<' ';

            myfile << "EOF"<<' ';

            for( auto it = temp.begin(); it != temp.end(); ++it )
            {
                char key = it->first;
                uint64_t & value = it->second;
                myfile << key<<' ';
                myfile <<(int)value<<' ' ;
            }
            myfile << "EOF"<<' ';
            std::map<char,std::vector<int>> occ_t = s1.getProcceed();

            for( auto it = occ_t.begin(); it != occ_t.end(); ++it )
            {
                char key = it->first;
                std::vector<int> & value = it->second;
                myfile << key<<' ';
                for(int k:value){
                    myfile <<k<<' ' ;
                }
                myfile << "EOF"<<' ';

            }
            myfile << "EOF"<<' ';
            myfile.close();


//            backward_search("sis",post,temp,s1);

        }
        infile.close();

    } else if (strcmp(arg1, "query") == 0) {
        string line;
        ifstream myfile (arg2);
        std::string post ;
        std::map<char,uint64_t> temp;
        std::map<char,std::vector<int>> occ_t;
        if(myfile.is_open()){
            string a;
            myfile >> a;

//            std::cout<< a <<std::endl;

            post = a;
            string c;
            string d;
            myfile >> c;
//            std::cout<<c<<" "<<d<<std::endl;
            while (myfile >> c &&c!="EOF")
            {   myfile >>d;
                char e = c[0];
                uint64_t f = (uint64_t)std::stoi(d);
                temp[e] = f;
//                std::cout<<c<<d<<std::endl;

            }
//            std::cout<<c<<d<<std::endl;
//            myfile >> c;
//            std::cout<<c<<std::endl;
//            c = d;
            while (myfile >> c&&c!="EOF" ){

                char e = c[0];
                occ_t[e] = {};
                string q;
//                std::cout<<e<<std::endl;
                while(myfile >> q &&q!="EOF"){
                    std::vector<int> &ye = occ_t[e];
                    ye.push_back(std::stoi(q));
                }
            }

            ifstream myfile2 (arg3);
            string asd;

            long int run_time = 0;

            while(myfile2>>asd){

                long int start_ms = now_ms();
                pair<int,int> fqd =backward_search(asd,post,temp,occ_t);
                long int end_ms = now_ms();
                run_time += (end_ms - start_ms);
//                cout<<asd<<std::endl;
                std::cout<<fqd.first<<'\t'<<fqd.second<<std::endl;
//                if(fqd.first!=fqd.second){
//                    std::cout<<"!!!!!!!!!!!!!!!!!!"<< std::endl;
//                }
            }

            printf("run time -> %ldms\n", run_time);

        }
    } else {
        printf("error: unknown mode <%s>\n", arg1);
        return -1;
    }

    return 0;
}
