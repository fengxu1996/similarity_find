#include<bits/stdc++.h>
#include<ctime>
#include<windows.h>
using namespace std;
double totletime=0;
const long long YUSIZE = 719960;/**设置域大小*/
const string outPath = "mh.txt";/**设置签名输出路径*/
const long long HASHN=1000;/**设置hash函数个数*/
//const long long C=1000003;/**作为(A*x+B)%C中的C 大于等于域的最小素数 */
long long C;/**作为(A*x+B)%C中的C 大于等于域的最小素数 */

/**大素数______________________*/
const int maxn=100000;// N=999999时有78498个素数
const int maxnn=999999;
long long prime[maxn+10]; /**保存素数*/
bool isprime[maxnn+10];
long long pnum;
void GetPrime(long long N )
{
    pnum=0;
    memset(isprime,true,sizeof(isprime));
    isprime[1]=false;
    //i 为最大因数
    for(long long  i=2;i<=N;i++)
    {
        if(isprime[i])
        {
            prime[pnum++]=i;
        }
        for(long long  j=0;j<pnum && prime[j]*i<=N;j++)
        {
            isprime[prime[j]*i]=false;
            if(i%prime[j]==0)break;
        }
    }
}
struct hashParameter
{
    long long A,B;
};
vector<hashParameter> hashi(int k)
{

    vector<hashParameter>v;
    for(int i=0;i<k;i++)
    {
        hashParameter xx;
        long long aindex = (rand()%10000)+(pnum-10001);
        long long bindex = (rand()%10000)+(pnum-10001);

        xx.A=prime[aindex];
        xx.B=prime[bindex];

        v.push_back(xx);
    }
    return v;
}
vector<hashParameter>HASH;/**hash函数集参数*/
vector<long long> minhash(vector<string> attrV)//传入一个属性向量计算出minhash值
{
    long long minHASH[HASHN+10];
    for(int i=0;i<=HASHN+2;i++)minHASH[i]=-1;
    for(int i=0;i<attrV.size();i++)
    {
        for(int k=0;k<HASHN;k++)
        {
            long long ihash=(  HASH[k].A*atoll(attrV[i].c_str()) +HASH[k].B  )% C;
            if(minHASH[k]!=-1)
            {
                minHASH[k]=min(minHASH[k],ihash);
            }
            else
            {
                minHASH[k]=ihash;
            }
        }
    }
    vector<long long>VV;
    for(int i=0;i<HASHN;i++)
    {
        VV.push_back(minHASH[i]);
    }
    return VV;
}

vector<string>filepathlist;/**文件path列表*/
void exec(string pathIn)
{
    //读取文件内容
    ifstream in;
    in.open(pathIn.c_str(), ios::in);
    vector<string>wordhas;
    string s;
    while(in>>s)wordhas.push_back(s);
    in.close();

    double start = clock();

    /**计算该文档签名向量*/
    vector<long long> sigv = minhash(wordhas);
    double stop = clock();
    totletime+=(stop-start);
    /**保存到文件*/
    ofstream out;
    out.open(outPath.c_str(), ios::out|ios::app);
    out<<pathIn;/**把文件名放首位*/
    for(int i=0;i<sigv.size();i++)
    {
        out<<" "<<sigv[i];
    }
    out<<"\n";
    out.close();
}
int main()
{
    /**计算大素数*/
    GetPrime(999999);cout<<"OK1"<<endl;
    /**确定hash函数*/
    HASH = hashi(HASHN);cout<<"OK2"<<endl;
    /**确定C值大小*/
    C = prime[lower_bound(prime, prime+pnum, YUSIZE) - prime];cout<<"OK3"<<" C="<<C<<endl;
    /**删除旧的mh.txt文件*/
    string delPath = "del "+outPath;
    system(delPath.c_str());
    /**确定要操作哪些文件*/
    ifstream fin;
    fin.open("filePath.txt", ios::in);
    string s;
    while(fin>>s)
    {
        filepathlist.push_back(s);
    }
    fin.close();
    /**计算签名矩阵*/
    for(int i=0;i<filepathlist.size();i++)
    {
        //cout<<"done "<<filepathlist[i]<<endl;
        exec(filepathlist[i]);
    }
    /**将运行时间写入日志*/
    ofstream fout;
    fout.open("runtime.log", ios::out|ios::app);
    fout<<"minhash计算用时"<<(totletime/CLOCKS_PER_SEC)<<"\n";
    fout.close();
    return 0;

}
