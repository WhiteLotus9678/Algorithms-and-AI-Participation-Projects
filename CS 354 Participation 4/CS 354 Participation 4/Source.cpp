#include <iostream>
#include <string>
#include <vector>
using namespace std;
////////////////////////////activities problem
vector<int> Greedy_Activity(vector<int>s, vector<int>f) {
	int n = s.size() - 1;
	vector<int> A;
	A.push_back(1);
	int k = 1;
	for (int m = 2; m <= n; m++) {
		if (s[m] >= f[k]) {
			A.push_back(m);
			k = m;
		}
	}
	return A;
}

/////////////////////////////////////huffman code
///0 set of charactor C
class C {
public:
	C() {
		this->MyC = ' ';
		this->freq = 0;
	}
	C(char MyC, int freq) {
		this->freq = freq;
		this->MyC = MyC;
	}
	char MyC;
	int freq;
};

///1 nodes
class node {
public:
	node() {
		this->left = NULL;
		this->right = NULL;
		this->next = NULL;
		this->MyC.freq = 0;
		this->MyC.MyC = NULL;
	}
	node(C MyC) {
		this->left = NULL;
		this->right = NULL;
		this->next = NULL;
		this->MyC.freq = MyC.freq;
		this->MyC.MyC = MyC.MyC;
	}
	~node() {

	}
	node* left;
	node* right;
	node* next;
	C MyC;
private:
};

////2 MinQ
//template<class node>
class MinQ
{
public:
	MinQ() { first = NULL; last = NULL; size = 0; };
	void push_back(node* MyNode) {

		if (size == 0) {
			this->first = MyNode;
			this->last = MyNode;
		}
		else if (MyNode->MyC.freq <= first->MyC.freq)
		{
			MyNode->next = first;
			this->first = MyNode;
		}
		else if (MyNode->MyC.freq >= last->MyC.freq) {
			this->last->next = MyNode;
			this->last = MyNode;
		}
		else
		{
			node* current = this->first;
			node* previous = this->first;
			while (current != NULL)
			{
				if (MyNode->MyC.freq < current->MyC.freq) {
					previous->next = MyNode;
					MyNode->next = current;
					break;
				}
				previous = current;
				current = current->next;
			}

		}

		size++;
	}
	/////
	node* pop() {
		node* current = NULL;
		if (size != 0) {
			current = first;
			first = first->next;
			size--;
		}
		return current;
	}
	/////
	~MinQ() {
		while (first != NULL)
		{
			node* current = first;
			first = first->next;
			delete current;
		}
		first = NULL;
		last = NULL;
	}
private:
	node * first;
	node * last;
	int size;
};

////3 Huffman

MinQ* Huffman(vector<C> C) {
	MinQ* MyQ = new MinQ;
	//MinQ TheQ;
	int n = C.size();
	for (int i = 0; i < C.size(); i++) {
		node* Temp = new node(C[i]);
		(*MyQ).push_back(Temp);
	}
	for (int i = 0; i < n - 1; i++) {

		node* Z = new node();
		Z->left = (*MyQ).pop();
		Z->right = (*MyQ).pop();
		Z->MyC.freq = Z->left->MyC.freq + Z->right->MyC.freq;
		(*MyQ).push_back(Z);
	}
	return MyQ;
}
vector<int>MyHuFFcode;
bool found = false;
void Print(node* root, C MyC) {
	if (found) {
		return;
	}
	if (root == NULL) {
		return;
	}
	if (root->MyC.MyC == MyC.MyC) {
		found = true;
		return;
	}
	if (!found)
		MyHuFFcode.push_back(0);

	Print(root->left, MyC);
	if (!found)
		MyHuFFcode.pop_back();

	if (!found)
		MyHuFFcode.push_back(1);
	Print(root->right, MyC);
	if (!found)
		MyHuFFcode.pop_back();

}


int main() {
	///////////////////////testing for greedy activity
	vector<int> S = { 0,1,3,0,5,3,5,6,8,8,2,12 };
	vector<int> F = { 0,4,5,6,7,9,9,10,11,12,14,16 };

	vector<int> A = Greedy_Activity(S, F);
	cout << "the optimal activity arrangement:" << endl;
	cout << "{";
	for (int i = 0; i < A.size(); i++) {
		cout << A[i] << ",";
	}
	cout << "}\n\n";
	string banner;
	banner.assign(40, '=');
	cout << banner << endl;

	///////////////////////testing for greedy activity

	vector<C>MyC = { C('a',45),C('b',13), C('c',12), C('d',16), C('e',9), C('f',5) };

	MinQ* TheQ = Huffman(MyC);
	node* Root = TheQ->pop();

	for (int i = 0; i < MyC.size(); i++) {
		MyHuFFcode.clear();
		found = false;
		Print(Root, MyC[i]);
		cout << "Huffman code for letter " << MyC[i].MyC << ": ";
		for (int j = 0; j < MyHuFFcode.size(); j++) {
			cout << MyHuFFcode[j] << " ";
		}
		cout << endl;
	}

	system("pause");

	return 0;
}