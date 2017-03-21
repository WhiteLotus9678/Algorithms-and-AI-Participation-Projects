#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

///implementing max subarray
vector<double> MaxCrossing(vector<double> pricechange, int low, int mid, int high) {

	double leftsum = -INFINITY;
	double sum = 0;
	int maxleftindex = mid;

	for (int i = mid; i >= low; i--) {

		sum = sum + pricechange[i];

		if (sum > leftsum) {
			leftsum = sum;
			maxleftindex = i;
		}
	}

	double rightsum = -INFINITY;

	sum = 0;

	int maxrightindex = mid + 1;

	for (int i = mid + 1; i <= high; i++) {
		sum = sum + pricechange[i];
		if (sum > rightsum) {
			rightsum = sum;
			maxrightindex = i;
		}
	}

	vector<double> myreturn;

	myreturn.push_back(maxleftindex);
	myreturn.push_back(maxrightindex);
	myreturn.push_back(leftsum + rightsum);

	return myreturn;
}

vector<double> MaxSubArray(vector<double> pricechange, int low, int high) {

	vector<double> myreturn;

	if (high == low) {
		myreturn.push_back(low);
		myreturn.push_back(high);
		myreturn.push_back(pricechange[low]);

		return myreturn;
	}
	else
	{
		int mid = (low + high) / 2;
		vector<double> fromleft = MaxSubArray(pricechange, low, mid);
		vector<double> fromright = MaxSubArray(pricechange, mid + 1, high);
		vector<double> frommiddle = MaxCrossing(pricechange, low, mid, high);

		if (fromleft[2] >= fromright[2] && fromleft[2] >= frommiddle[2]) {
			myreturn = fromleft;
		}
		else if (fromright[2] >= fromleft[2] && fromright[2] >= frommiddle[2]) {
			myreturn = fromright;
		}
		else {
			myreturn = frommiddle;
		}
	}

	return myreturn;
}


int main() {

	vector<double> dailyprice = { 100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97 };

	///calculate daily price change
	vector<double> dailypricechange;

	for (int i = 1; i < dailyprice.size(); i++) {
		dailypricechange.push_back(dailyprice[i] - dailyprice[i - 1]);
	}

	///calculate the max subarray
	vector<double> myresult = MaxSubArray(dailypricechange, 0, dailypricechange.size() - 1);

	///display the results
	string banner;

	banner.assign(36, '=');
	cout << "The results:" << endl;
	cout << banner << endl;
	cout << "You should buy stock on day: " << myresult[0] + 1 << endl;
	cout << "You should sell out stock on day: " << myresult[1] + 1 << endl;
	cout << "The max profit you can receive is: $" << myresult[2] << endl;
	cout << banner << endl;

	system("pause");

	return 0;
}