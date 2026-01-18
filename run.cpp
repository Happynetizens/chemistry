#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;
struct element{		// 元素
	const short x;		// 原子序数（质子数）
	const string name;		// 元素名称
	const string sign;		// 元素符号
	const short s;		// 金属活跃度（排序）
	int eqn;		// 方程式（链式前向星）
};
struct equation{		// 反应方程式
	vector<short> reactants;		// 反应物
	// vector<string> conditions;		// 反应条件
	vector<short> products;		// 生成物
	int nxt;		// 链式前向星
};
element elements[]={{},
	{1, 	"氢", 	"H", 	10},
	{2, 	"氦", 	"He", 	0},
	{3, 	"锂", 	"Li", 	15},
	{4, 	"铍", 	"Be", 	14},
	{5, 	"硼", 	"B", 	0},
	{6, 	"碳", 	"C", 	0},
	{7, 	"氮", 	"N", 	0},
	{8, 	"氧", 	"O", 	0},
	{9, 	"氟", 	"F", 	0},
	{10, 	"氖", 	"Ne", 	0},
	{11, 	"钠", 	"Na", 	20},
	{12, 	"镁", 	"Mg", 	19},
	{13, 	"铝", 	"Al", 	18},
	{14, 	"硅", 	"Si", 	0},
	{15, 	"磷", 	"P", 	0},
	{16, 	"硫", 	"S", 	0},
	{17, 	"氯", 	"Cl", 	0},
	{18, 	"氩", 	"Ar", 	0},
	{19, 	"钾", 	"K", 	21},
	{20, 	"钙", 	"Ca", 	17},
	{26, 	"铁", 	"Fe", 	16},
	{29, 	"铜", 	"Cu", 	13},
	{30, 	"锌", 	"Zn", 	15},
	{47, 	"银", 	"Ag", 	12},
	{56, 	"钡", 	"Ba", 	11},
	{63, 	"汞", 	"Hg", 	9},
	{78, 	"铂", 	"Pt", 	8},
	{79, 	"金", 	"Au", 	7},
	{80, 	"锡", 	"Sn", 	14},
	{82, 	"铅", 	"Pb", 	8}
};
vector<string> list;		// 原方程式
vector<equation> equations={{/*post 0 is empty*/}};
inline int getPost(short &target) {
    int left=0, right=sizeof(elements)/sizeof(elements[0])-1, mid;
    while (left<=right){
        mid=(left+right)>>1;
        if(elements[mid].x==target) return mid;
        else if(elements[mid].x>target) right=mid-1;
        else left=mid+1;
    }
    return 0;		// Err
}
inline int getX(string &name){
	for(int i=1; i<sizeof(elements)/sizeof(elements[0]); ++i) if(elements[i].name==name) return elements[i].x;
	return 0;		// Err
}
inline short get_element(string &eqn, short start, vector<short> &output){
	short i=start;
	for(string temp; eqn[i] && eqn[i]!='='; ++i){		// 目前是读原子，后续要改为分子......
		if(isupper(eqn[i]) && isupper(eqn[i+1])) temp=eqn[i];
		else temp=eqn[i]+eqn[i+1];		// Err......
		output.push_back(getX(temp));
	}
	output.erase(std::unique(output.begin(), output.end()), output.end());
	return i+1;		// 末尾下标+1
}
inline void add(short &react, int &eqn, vector<short> &prods, vector<short> &reacts){		// 链式前向星_add
	int post=elements[getPost(react)].eqn;
	equations.push_back({reacts, prods, post});
	elements[getPost(react)].eqn=equations.size()-1;
}
inline void init(){		// 存图（library to list && list to data）
    freopen("./library.txt", "r", stdin);
	string temp;
    while(std::cin>>temp) list.push_back(temp);
    list.erase(std::unique(list.begin(), list.end()), list.end());		// deep unique......
	fclose(stdin);
	for(int i=0; i<list.size(); ++i){
		vector<short> reacts;		// 反应物
		vector<short> prods;		// 生成物
		get_element(list[i], get_element(list[i], 0, reacts), prods);
		for(auto p: reacts) add(p, i, prods, reacts);
	}
}
int main(){
	// loading......
	return 0;
}
