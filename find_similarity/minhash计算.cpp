#include<bits/stdc++.h>
#include<ctime>
#include<windows.h>
using namespace std;
double totletime=0;
const long long YUSIZE = 719960;/**�������С*/
const string outPath = "mh.txt";/**����ǩ�����·��*/
const long long HASHN=1000;/**����hash��������*/
//const long long C=1000003;/**��Ϊ(A*x+B)%C�е�C ���ڵ��������С���� */
long long C;/**��Ϊ(A*x+B)%C�е�C ���ڵ��������С���� */

/**������______________________*/
const int maxn=100000;// N=999999ʱ��78498������
const int maxnn=999999;
long long prime[maxn+10]; /**��������*/
bool isprime[maxnn+10];
long long pnum;
void GetPrime(long long N )
{
    pnum=0;
    memset(isprime,true,sizeof(isprime));
    isprime[1]=false;
    //i Ϊ�������
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
vector<hashParameter>HASH;/**hash����������*/
vector<long long> minhash(vector<string> attrV)//����һ���������������minhashֵ
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

vector<string>filepathlist;/**�ļ�path�б�*/
void exec(string pathIn)
{
    //��ȡ�ļ�����
    ifstream in;
    in.open(pathIn.c_str(), ios::in);
    vector<string>wordhas;
    string s;
    while(in>>s)wordhas.push_back(s);
    in.close();

    double start = clock();

    /**������ĵ�ǩ������*/
    vector<long long> sigv = minhash(wordhas);
    double stop = clock();
    totletime+=(stop-start);
    /**���浽�ļ�*/
    ofstream out;
    out.open(outPath.c_str(), ios::out|ios::app);
    out<<pathIn;/**���ļ�������λ*/
    for(int i=0;i<sigv.size();i++)
    {
        out<<" "<<sigv[i];
    }
    out<<"\n";
    out.close();
}
int main()
{
    /**���������*/
    GetPrime(999999);cout<<"OK1"<<endl;
    /**ȷ��hash����*/
    HASH = hashi(HASHN);cout<<"OK2"<<endl;
    /**ȷ��Cֵ��С*/
    C = prime[lower_bound(prime, prime+pnum, YUSIZE) - prime];cout<<"OK3"<<" C="<<C<<endl;
    /**ɾ���ɵ�mh.txt�ļ�*/
    string delPath = "del "+outPath;
    system(delPath.c_str());
    /**ȷ��Ҫ������Щ�ļ�*/
    ifstream fin;
    fin.open("filePath.txt", ios::in);
    string s;
    while(fin>>s)
    {
        filepathlist.push_back(s);
    }
    fin.close();
    /**����ǩ������*/
    for(int i=0;i<filepathlist.size();i++)
    {
        //cout<<"done "<<filepathlist[i]<<endl;
        exec(filepathlist[i]);
    }
    /**������ʱ��д����־*/
    ofstream fout;
    fout.open("runtime.log", ios::out|ios::app);
    fout<<"minhash������ʱ"<<(totletime/CLOCKS_PER_SEC)<<"\n";
    fout.close();
    return 0;

}
