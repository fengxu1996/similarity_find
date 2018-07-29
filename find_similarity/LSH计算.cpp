#include<hash_map>
#include<bits/stdc++.h>
#include<ctime>
#include<hashtable.h>
using namespace std;
double totletime=0;
int DOCNUM=0;/**文档数*/
//const int R = 20;/**每个行条的行数*/
//const int B = 50;/**行条数*/

//const int R = 10;/**每个行条的行数*/
//const int B = 100;/**行条数*/

const int R = 5;/**每个行条的行数*/
const int B = 200;/**行条数*/

const int HASHN=1000;/**hash函数个数*/
unordered_map<string,int>HASH;
vector<string>docsName;/**存储文件名*/
vector<vector<string>>Sig;/**存储原始签名矩阵,用作计算最终相似度*/
vector<vector<string>>newSig;/**存储新的签名矩阵*/
unordered_map<string,vector<string>>M;
//set<string>FLAG;/**标记已被确认相似的文件对*/
unordered_map<string,bool>flag;/**key为docname1+docname2, value为true代表已被标记*/
vector<vector<string>>SIMDOC;/**保存结果,保存有可能相似的文件名*/
unordered_map<string,int>docName_To_index;/**文件名映射到下标号*/
vector<string> split(string s)//按空格分割字符串
{
    vector<string>v;
    string x="";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' '){
            v.push_back(x);
            x="";
        }
        else
            x+=s[i];
    }
    v.push_back(x);
    return v;
}
vector<string> combinesig(vector<string>v, int k)/**构造新的sig矩阵*/
{

    vector<string>ans;
    string s="";
    for(int i=1;i<v.size();i++)
    {
        s+=v[i];
        if(i%k==0){
            ans.push_back(s);
            s="";
        }
    }
    return ans;
}
void exec()
{
    unordered_map<string,vector<string>>Mi;/**key为每个行条中的一列, value为散列到一起的文件名*/

    for(int i=0;i<B;i++)/**每个行条*/
    {

        for(int j=0;j<DOCNUM;j++)/**每个行条中的每个小列*/
        {
            Mi[ newSig[j][i] ].push_back(docsName[j]);/**散列*/
        }
        unordered_map<string,vector<string>>::iterator it;
        for(it=Mi.begin();it!=Mi.end();it++)
        {

            if((it->second).size()>1){
                //cout<<"exec"<<(it->second).size()<<endl;
                SIMDOC.push_back((it->second));
//                for(int ww=0;ww<(it->second).size();ww++)cout<<(it->second)[ww]<<" ";cout<<endl;
            }
        }
        Mi.clear();/**清空*/
    }
}
struct node
{
    double sim;
    string doc1;
    string doc2;
};
bool cmp(node x,node y)
{
    return x.sim>y.sim;
}
int main()
{
    ifstream fin;
    fin.open("mh.txt", ios::in);
    string s;
    while(getline(fin,s))
    {
        vector<string>v = split(s);
        docsName.push_back(v[0]);/**存储文件名*/

        vector<string>vv = combinesig(v, R);
        newSig.push_back(vv);/**存储合并后的新签名向量*/
        Sig.push_back(v);

    }
//    cout<<"OK1"<<endl;
    DOCNUM = docsName.size();
    for(int i=0;i<docsName.size();i++)docName_To_index[docsName[i]]=i;/**建立文件名到下表的映射*/
//    cout<<"OK2"<<endl;
    double start = clock();
    exec();
    double stop = clock();
    totletime+=(stop-start);
//    cout<<"OK3"<<endl;
//    cout<<SIMDOC.size()<<endl;

    /**去除重复对*/
    vector<node>ans;/**保存最终相似度结果*/
//    set<string>repetion;
    unordered_map<string,bool>flag1;

    start = clock();
    for(int i=0;i<SIMDOC.size();i++)
    {
        for(int j=0;j<SIMDOC[i].size();j++)
        {
            for(int k=j+1;k<SIMDOC[i].size();k++)
            {
                string xx=SIMDOC[i][j]+SIMDOC[i][k];
                if(flag1[xx]!=true){/**去重*/
                    flag1[xx]=true;
                    /**计算相似度*/
                    int doc1index = docName_To_index[SIMDOC[i][j]];
                    int doc2index = docName_To_index[SIMDOC[i][k]];
                    double cnt=0;
                    for(int ww=1;ww<=HASHN;ww++){
                        if(Sig[doc1index][ww]==Sig[doc2index][ww])
                            cnt++;
                    }
                    node oo;
                    oo.doc1=SIMDOC[i][j];
                    oo.doc2=SIMDOC[i][k];
                    oo.sim=(cnt/HASHN);
                    ans.push_back(oo);
                }
            }
        }
    }
    stop = clock();
    totletime+=(stop-start);
    sort(ans.begin(),ans.end(),cmp);

    ofstream fout;
    fout.open("lshResult.txt", ios::out);
    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i].doc1<<" "<<ans[i].doc2<<" "<<ans[i].sim<<endl;
        fout<<ans[i].doc1<<" "<<ans[i].doc2<<" "<<ans[i].sim<<"\n";
    }
    fout.close();
    cout<<"用时"<<(totletime/CLOCKS_PER_SEC)<<endl;


    fout.open("runtime.log", ios::out|ios::app);
    fout<<"lsh用时"<<(totletime/CLOCKS_PER_SEC)<<"\n";
    fout.close();

//    ofstream fout;
//    fout.open("lsh.txt", ios::out);
//    for(int i=0;i<SIMDOC.size();i++)
//    {
//        for(int j=0;j<SIMDOC[i].size();j++)
//        {
//            if(j==0){
//                fout<<SIMDOC[i][j];
//            }
//            else{
//                fout<<" "<<SIMDOC[i][j];
//            }
//        }
//        fout<<"\n";
//    }
//    fout.close();



    return 0;
}
