#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int calc_raizes(float a, float b, float c, float &x1, float &x2){
    float delta = b*b - 4*a*c;
	
	x1 = (-b + sqrt(delta))/2*a;
    x2 = x1 = (-b - sqrt(delta))/2*a;
    
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}

int main(){
	float a;
	float b;
	float c;
    float x1;
    float x2;
	
	cin >> a >> b >> c;
	
	calc_raizes(a,b,c, x1, x2);

	return 0;
}