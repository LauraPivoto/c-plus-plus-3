#include <iostream>
#include <iomanip>

using namespace std;

float calc_delta(float a, float b, float c){
	float delta = b*b - 4*a*c;
	
	cout << "delta = ";
	cout << fixed << setprecision(0) << delta << endl;
}

int main(){
	float a;
	float b;
	float c;
	
	cin >> a >> b >> c;
	
	calc_delta(a, b, c);
	
	return 0;
}