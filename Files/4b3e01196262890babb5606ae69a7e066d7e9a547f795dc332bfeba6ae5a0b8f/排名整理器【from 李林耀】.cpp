#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
map<string,string> user;
map<string,double> scores;
void init(){
    // 用户追加 - code by politetrex
    user["naijil2013"]   ="https://www.luogu.com.cn/user/1794767";
    user["Houyc11"]      ="https://www.luogu.com.cn/user/1789628";
    user["xincheng2024"] ="https://www.luogu.com.cn/user/1366208";
    user["lxxm3502"]     ="https://www.luogu.com.cn/user/1755268";
    user["politetrex"]   ="https://www.luogu.com.cn/user/1431790";
    user["xmgene"]       ="https://www.luogu.com.cn/user/1730134";
    user["z201322"]      ="https://www.luogu.com.cn/user/1789576";
    user["kuailexiaoxiu"]="https://www.luogu.com.cn/user/1789618";
    user["pankuangyu"]   ="https://www.luogu.com.cn/user/1295664";
    user["zhaolt2012"]   ="https://www.luogu.com.cn/user/1408054";
    user["Allen1125"]    ="https://www.luogu.com.cn/user/1789605";
    user["Enoch0601"]    ="https://www.luogu.com.cn/user/1789578";
    user["BKX1405"]      ="https://www.luogu.com.cn/user/1790158";
    user["34567n"]       ="https://www.luogu.com.cn/user/1200461";
}
int main(){
    init();
    for(auto[key,value]:user){
        cout<<"请输入用户 "<<key<<" 的得分：";
        double x; cin>>x; scores[key]=x;
    }
    vector<pair<string,double> > sorted(scores.begin(), scores.end());
    sort(sorted.begin(), sorted.end(),[](auto &a, auto &b) { return a.second > b.second; });
    cout<<"请输入所有者："; string own; cin>>own;
    int n; cout<<"请输入管理员个数："; cin>>n;
    vector<string> managers(n);
    for(int i=0;i<n;i++){
        cout<<"请输入管理员"<<i+1<<"：";
        cin>>managers[i];
    }
    cout<<"\n\n表格已生成\n\n";
    // Output in Markdown - politetrex
    cout<<"|排名|用户|积分|\n|:--:|:--------:|:---:|\n";
    int i=0; double prev=-1;
    for(auto[key,score]:sorted){
        if(prev!=score) i++;
        cout<<"|Top"<<i<<"|["<<key;
        if(key==own) cout<<"$\\colorbox{yellow}{所有者}$";
        else if (find(managers.begin(),managers.end(),key)!=managers.end())
            cout<<"$\\colorbox{blue}{\\color{white}管理员}$";
        cout<<"]("<<user[key]<<")|"<<score<<"|\n"; prev=score;
    }
    return 0;
}

