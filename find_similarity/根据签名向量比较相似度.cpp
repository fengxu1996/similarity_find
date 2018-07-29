#include<bits/stdc++.h>
#include<ctime>
using namespace std;
double totletime;
const string path = "mh.txt"; /**����·��*/
vector<string>filename;/**�ļ���*/
vector<vector<string>>sigv;/**�ļ���Ӧǩ������*/
vector<string> split(string s)//���ո�ָ��ַ���
{
    vector<string>v;
    string w="";

    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' ')
        {
            v.push_back(w);
            w="";
        }
        else
        {
            w+=s[i];
        }
    }
    v.push_back(w);
    return v;
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
    fin.open(path.c_str(), ios::in);
    string ss;
    int cnt=0;
    while(getline(fin, ss))
    {
        vector<string>x=split(ss);
        vector<string>xx;
        filename.push_back(x[0]);
        for(int i=1;i<x.size();i++)
        {
            xx.push_back(x[i]);
        }
        sigv.push_back(xx);
    }
    map<int,string>M;
    double hashn = sigv[0].size();/**hash�����ĸ���*/

    vector<node>ans;/**������*/
    double start = clock();
    for(int i=0;i<filename.size();i++)M[i]=filename[i];
    for(int i=0;i<filename.size();i++)
    {
        for(int j=i+1;j<filename.size();j++)
        {
            double cnt=0;
            for(int k=0;k<hashn;k++)
            {
                if(sigv[i][k]==sigv[j][k])cnt++;
            }
            double sim = cnt/hashn;
            node xx;
            xx.sim = sim;
            xx.doc1 = M[i];
            xx.doc2 = M[j];
            ans.push_back(xx);

            //cout<<sim<<" "<<M[i]<<" "<<M[j]<<endl;
        }
    }
    double stop = clock();
    totletime = (stop - start);
    cout<<"I am OK!"<<(totletime/CLOCKS_PER_SEC)<<endl;
    start = clock();
    sort(ans.begin(),ans.end(),cmp);
    stop = clock();
    ofstream fout;
    fout.open("result.txt", ios::out);
    for(int i=0;i<1000;i++)
    {
        fout<<ans[i].doc1<<" "<<ans[i].doc2<<" "<<ans[i].sim<<"\n";
    }
    fout.close();

    fout.open("runtime.log", ios::out|ios::app);
    fout<<"�Ƚ������ĵ����ƶ���ʱ"<<(totletime/CLOCKS_PER_SEC)<<"\n";
    fout<<"�������ƶ���ʱ"<<((stop-start)/CLOCKS_PER_SEC)<<"\n";
    fout.close();
    return 0;
}
