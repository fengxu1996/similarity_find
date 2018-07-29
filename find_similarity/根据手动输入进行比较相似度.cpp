#include<bits/stdc++.h>
#include<ctime>
using namespace std;
const string path = "mh.txt"; /**输入路径*/
vector<string>filename;/**文件名*/
vector<vector<string>>sigv;/**文件对应签名向量*/
vector<string> split(string s)//按空格分割字符串
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
    map<string,int>MM;

    double hashn = sigv[0].size();/**hash函数的个数*/

    vector<node>ans;/**保存结果*/
    for(int i=0;i<filename.size();i++)M[i]=filename[i];
    for(int i=0;i<filename.size();i++)MM[filename[i]]=i;
    string A,B;
    while(cin>>A>>B)
    {
        double cnt=0;
        for(int k=0;k<hashn;k++)
        {
            if(sigv[MM[A]][k]==sigv[MM[B] ][k])cnt++;
        }
        cout<<(cnt/hashn)<<endl;
    }


//    for(int i=0;i<filename.size();i++)
//    {
//        for(int j=i+1;j<filename.size();j++)
//        {
//            double cnt=0;
//            for(int k=0;k<hashn;k++)
//            {
//                if(sigv[i][k]==sigv[j][k])cnt++;
//            }
//            double sim = cnt/hashn;
//            node xx;
//            xx.sim = sim;
//            xx.doc1 = M[i];
//            xx.doc2 = M[j];
//            ans.push_back(xx);
//
//            cout<<sim<<" "<<M[i]<<" "<<M[j]<<endl;
//        }
//    }
    sort(ans.begin(),ans.end(),cmp);

    for(int i=0;i<10;i++)
    {
        cout<<ans[i].doc1<<" "<<ans[i].doc2<<" "<<ans[i].sim<<endl;
    }

    return 0;
}
