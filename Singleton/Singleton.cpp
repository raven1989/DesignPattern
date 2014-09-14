#include<iostream>
using namespace std;

class Singleton{
public:
	static Singleton * Instance(){
		if(instance == 0)
			instance = new Singleton;
		return instance;
	}
private:
	Singleton(){};
	Singleton(const Singleton&){};
	static Singleton* instance;
};

Singleton* Singleton::instance = 0;

int main(){
	Singleton* s1 = Singleton::Instance();
	Singleton* s2 = Singleton::Instance();
	if(s1==s2)
		cout<<"Singleton!!"<<endl;
	return 0;
}
