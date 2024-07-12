#include <iostream>
#include <vector>
#include <string>

using namespace std;
class CClass {
	public:
	void init();
	void print();
	private:
	struct TStudent {
		string id;
		string name;
		string surname;
	};
		vector<TStudent> studs;
		vector<TStudent *> ptrstuds;
};
void CClass::init (){
	TStudent s1 = { "666","John", "Smith"}; 
	studs.push_back(s1); //push back funguje tak, ze on kopiruje data. s1 je lokalni
	//ptrstuds.push_back(&s1); //problem je, ze vkladas ponter na lokalni pointer.
	ptrstuds.push_back(&(studs.back())); //too by melo fungovat

}
void CClass::print(){
	TStudent * s1;
	s1 = ptrstuds[0];
	cout << s1->id << " " << s1->name << " " << s1->surname << endl;
}
int main (){
	CClass a;
	a.init();
	a.print();
	return 0;
}