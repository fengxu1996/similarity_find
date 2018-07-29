#include<hash_map>
#include<bits/stdc++.h>
#include<ctime>
#include<hashtable.h>
using namespace std;
double totletime=0;
int DOCNUM=0;/**�ĵ���*/
//const int R = 20;/**ÿ������������*/
//const int B = 50;/**������*/

//const int R = 10;/**ÿ������������*/
//const int B = 100;/**������*/

const int R = 5;/**ÿ������������*/
const int B = 200;/**������*/

const int HASHN=1000;/**hash��������*/
unordered_map<string,int>HASH;
vector<string>docsName;/**�洢�ļ���*/
vector<vector<string>>Sig;/**�洢ԭʼǩ������,���������������ƶ�*/
vector<vector<string>>newSig;/**�洢�µ�ǩ������*/
unordered_map<string,vector<string>>M;
//set<string>FLAG;/**����ѱ�ȷ�����Ƶ��ļ���*/
unordered_map<string,bool>flag;/**keyΪdocname1+docname2, valueΪtrue�����ѱ����*/
vector<vector<string>>SIMDOC;/**������,�����п������Ƶ��ļ���*/
unordered_map<string,int>docName_To_index;/**�ļ���ӳ�䵽�±��*/
vector<string> split(string s)//���ո�ָ��ַ���
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
vector<string> combinesig(vector<string>v, int k)/**�����µ�sig����*/
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
    unordered_map<string,vector<string>>Mi;/**keyΪÿ�������е�һ��, valueΪɢ�е�һ����ļ���*/

    for(int i=0;i<B;i++)/**ÿ������*/
    {

        for(int j=0;j<DOCNUM;j++)/**ÿ�������е�ÿ��С��*/
        {
            Mi[ newSig[j][i] ].push_back(docsName[j]);/**ɢ��*/
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
        Mi.clear();/**���*/
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
        docsName.push_back(v[0]);/**�洢�ļ���*/

        vector<string>vv = combinesig(v, R);
        newSig.push_back(vv);/**�洢�ϲ������ǩ������*/
        Sig.push_back(v);

    }
//    cout<<"OK1"<<endl;
    DOCNUM = docsName.size();
    for(int i=0;i<docsName.size();i++)docName_To_index[docsName[i]]=i;/**�����ļ������±��ӳ��*/
//    cout<<"OK2"<<endl;
    double start = clock();
    exec();
    double stop = clock();
    totletime+=(stop-start);
//    cout<<"OK3"<<endl;
//    cout<<SIMDOC.size()<<endl;

    /**ȥ���ظ���*/
    vector<node>ans;/**�����������ƶȽ��*/
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
                if(flag1[xx]!=true){/**ȥ��*/
                    flag1[xx]=true;
                    /**�������ƶ�*/
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
    cout<<"��ʱ"<<(totletime/CLOCKS_PER_SEC)<<endl;


    fout.open("runtime.log", ios::out|ios::app);
    fout<<"lsh��ʱ"<<(totletime/CLOCKS_PER_SEC)<<"\n";
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
