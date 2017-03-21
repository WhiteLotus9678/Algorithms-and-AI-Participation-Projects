#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <vector>
using namespace std;

class MySorting {
public:
	vector<double> RandomFloat(int Min, int Max, int size) {
		vector<double> returner;

		srand(time(NULL));

		for (int i = 0; i < size; i++) {
			if (double(rand()) != double(RAND_MAX)) {
				double N = ((double(rand()) / double(RAND_MAX))*(Max - Min)) + Min;
				returner.push_back(N);
			}
		}
		return returner;
	}
	vector<int> RandomInt(int Min, int Max, int size) {
		vector<int> returner;

		srand(time(NULL));

		for (int i = 0; i < size; i++) {
			int N = (rand() % (Max + 1)) + Min;
			returner.push_back(N);
		}
		return returner;
	}

	/////counting sort
	vector<int> Counting_Sort(vector<int> A) {
		int Max = -999;

		for (int i = 0; i < A.size(); i++) {
			if (Max < A[i]) {
				Max = A[i];
			}
		}

		int* C = new int[Max + 1];

		vector<int> B(A.size());

		for (int i = 0; i <= Max; i++) {
			C[i] = 0;
		}

		for (int j = 0; j < A.size(); j++) {
			C[A[j]]++;
		}

		for (int i = 1; i <= Max; i++) {
			C[i] = C[i] + C[i - 1];
		}

		for (int j = A.size() - 1; j >= 0; j--) {
			B[C[A[j]] - 1] = A[j];
			C[A[j]]--;
		}

		delete[] C;

		return B;
	}

	/////bucket sort
	vector<double> Bucket_Sort(vector<double> A) {
		vector<vector<double>> B(A.size());
		int n = A.size();

		for (int i = 0; i < A.size(); i++) {
			B[floor(n*A[i])].push_back(A[i]);
		}

		for (int i = 0; i < n; i++) {
			if (B[i].size() > 0) {
				Insertion_Sort(B[i]);
			}
		}

		////concatenation
		vector<double> returner;

		for (int i = 0; i < n; i++) {
			if (B[i].size() > 0) {
				for (int j = 0; j < B[i].size(); j++) {
					returner.push_back(B[i][j]);
				}
			}
		}

		return returner;
	}

private:
	void Insertion_Sort(vector<double>& A) {
		for (int j = 1; j < A.size(); j++) {

			double key = A[j];
			int i = j - 1;

			while (i >= 0 && A[i] > key) {
				A[i + 1] = A[i];
				i = i - 1;
			}
			A[i + 1] = key;
		}
	}

};

int main() {

	string banner;

	banner.assign(80, '=');
	cout << banner << endl;

	MySorting TheSorting;

	cout << "Randomly generating 15 real numbers in interval of [0,1):" << endl;

	vector<double> floatNum = TheSorting.RandomFloat(0, 1, 15);

	for (int i = 0; i < floatNum.size(); i++) {
		cout << floatNum[i] << " ";
	}
	cout << endl << endl;

	cout << "The result after the bucket sort: " << endl;

	vector<double> result1 = TheSorting.Bucket_Sort(floatNum);

	for (int i = 0; i < result1.size(); i++) {
		cout << result1[i] << " ";
	}
	cout << endl << endl;

	cout << banner << endl;

	cout << "Randomly generating 15 integers in interval of [0,100]: " << endl;

	vector<int> intNum = TheSorting.RandomInt(0, 100, 15);

	for (int i = 0; i < intNum.size(); i++) {
		cout << intNum[i] << " ";
	}
	cout << endl << endl;

	cout << "The result after the counting sort: " << endl;

	vector<int> result2 = TheSorting.Counting_Sort(intNum);

	for (int i = 0; i < result2.size(); i++) {
		cout << result2[i] << " ";
	}
	cout << endl << endl;

	system("pause");

	return 0;
}