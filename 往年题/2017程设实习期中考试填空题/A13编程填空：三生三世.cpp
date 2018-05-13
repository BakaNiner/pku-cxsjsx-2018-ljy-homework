#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama{
	public:
	char name[100];
	int actor;
	int story;
	int acting_skill;
	TV_Drama(char *_name, int _actor, int _story, int _acting_skill) : actor(_actor), story(_story), acting_skill(_acting_skill) {
		int len = strlen(_name);
		for(int i = 0; i < len; i++)
			name[i] = _name[i];
		name[len] = 0;
	}

	bool operator < (const TV_Drama &x) const {
		return actor > x.actor;
	}
};

bool comparator_1(TV_Drama &x, TV_Drama &y) {
	return x.story > y.story;
}

struct comparator_2 {
	bool operator () (TV_Drama &x, TV_Drama &y) {
		return x.acting_skill > y.acting_skill;
	}
};

void Printer(TV_Drama &x) {
	cout << x.name << ";";
}

int main(){
	list<TV_Drama> lst;
	int n;
	
	cin>>n;
	char  _name[100];
	int _actor, _story, _acting_skill;
	for (int i=0; i<n; i++){
        cin.ignore();
        cin.getline(_name,100);
        cin>>_actor>>_story>>_acting_skill;
		lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
	}

	lst.sort();
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_1);
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_2());
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	return 0;
}
