#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class mydata {
public:
	mydata(int size) {
		cut = vector<int>(size);
		profit = vector<double>(size);
	}

	vector<int> cut;
	vector<double> profit;
};

double Memoized_Cut_Rod_Aux(const vector<double>& p, int n, vector<double> r, mydata& thedata) {
	if (r[n] >= 0) {
		return  r[n];
	}

	double q;

	if (n == 0) {
		q = 0;
	}
	else
	{
		q = -INFINITY;

		for (size_t i = 1; i <= n; i++)
		{
			if (q <= (p[i] + Memoized_Cut_Rod_Aux(p, n - i, r, thedata))) {
				q = p[i] + Memoized_Cut_Rod_Aux(p, n - i, r, thedata);
				thedata.cut[n] = i;
			}
		}
		r[n] = q;

		thedata.profit[n] = q;
	}
	return q;
}


int main() {
	cout << left << setw(15) << "Length i: ";

	vector<double> Prices = { 0,1,5,8,9,10,17,17,20,24,30 };

	for (int i = 1; i < 11; i++) {
		cout << left << setw(4) << i;
	}

	cout << endl;

	string banner;

	banner.assign(56, '-');

	cout << banner << endl;
	cout << left << setw(15) << "Price Pi: ";

	for (int i = 1; i < 11; i++) {
		cout << left << setw(4) << Prices[i];
	}

	cout << endl;
	///////////////////////////////////////////

	///////////////////////////////////////////
	vector<double> r(11, -INFINITY);
	mydata thedata(11);

	Memoized_Cut_Rod_Aux(Prices, 10, r, thedata);

	///////////////////////////////////////////
	cout << endl;

	while (true)
	{
		cout << endl;
		cout << "Enter -1 to stop the program." << endl;
		cout << "Please enter the length (1 - 10) of the rod that you want to cut: ";

		int rodlength;

		cin >> rodlength;

		if (rodlength == -1) {
			break;
		}
		cout << endl;

		cout << "The max profit: $" << thedata.profit[rodlength] << endl;

		cout << "The optimal cuts are: ";

		int temp = rodlength;

		while (temp > 0)
		{
			cout << thedata.cut[temp];
			temp = temp - thedata.cut[temp];
			temp > 0 ? cout << "+" : cout << "";
		}
		cout << endl;

	}

	return 0;
}