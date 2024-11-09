#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;

/*Program for recursive and iterative approach in fibonacci*/

void RecFib(int n){
	static unsigned long long int f1=0,f2=1,f3;
	//cout<<f1<<f2;
	if (n>0){
		f3 = f1 + f2;
		f1 = f2;
		f2 = f3;
		cout << f2 << " ";
		RecFib(n-1);
	}
	
}

void iterFib(int n){
	int f1 = 0,f2=1;
	unsigned long long int f3;
	if (n==1){
		cout<<f1;
	}else if (n==2){
		cout<<f1<<f2;
	}
	cout<<"\n"<<f1<<" "<<f2<<" ";
	for(int i=2;i<n;i++){
		f3 = f1 + f2;
		cout<<f3<<" ";
		f1 = f2;
		f2 = f3;
	}
}

int main(){
	int n;
	cout<<"Enter a positive n: ";
	cin >> n;
	int RecN = n -2;
	auto RecStart = high_resolution_clock ::now();
	cout << "Fibonacci Series(Recursion): 0 1 ";
	RecFib(RecN);
	auto RecEnd = high_resolution_clock ::now();
	auto RecDuration = duration_cast<microseconds>(RecEnd - RecStart);
	auto IterStart = high_resolution_clock ::now();
	cout << "\nFibonacci Series(Iteration): ";
	iterFib(n);
	auto IterEnd = high_resolution_clock ::now();
	auto  IterDuration = duration_cast<microseconds>(IterEnd - IterStart);
	cout << "\nRecursive Fibonacci duration : "<<RecDuration.count()<<"microseconds";
	cout << "\nIterative Fibonacci duration : "<<IterDuration.count()<<"microseconds";
	return 0;
}
