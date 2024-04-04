#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;
const int NUM_TESTS = 10;

//binary tree
struct TreeNode {
	int val;
	TreeNode* leftPointer;
	TreeNode* rightPointer;
	TreeNode(int x) : val(x), leftPointer(nullptr), rightPointer(nullptr) {}
};

//create sorted binary tree
TreeNode* createSortedBT(int start, int end) {
	if (start > end)
		return nullptr;

	int mid = start + (end - start) / 2;
	TreeNode* root = new TreeNode(mid);

	root -> leftPointer = createSortedBT(start, mid - 1);
	root -> rightPointer = createSortedBT(mid + 1, end);

	return root;
}

//create reversed binary tree
TreeNode* createReversedBT(int start, int end) {
	if (start > end)
		return nullptr;

	int mid = start + (end - start) / 2;
	TreeNode* root = new TreeNode(mid);

	root->rightPointer = createReversedBT(start, mid - 1);
	root->leftPointer = createReversedBT(mid + 1, end);

	return root;
}

//create array
vector<int> createSortedArray(int n) {
	vector<int> arr(n);

	for (int i = 0; i < n; i++)
		arr[i] = i;

	return arr;
}

vector<int> createReversedArray(int n) {
	vector<int> arr(n);

	for (int i = 0; i < n; i++)
		arr[i] = (n - i) - 1;

	return arr;
}

vector<int> createRandomArray(int n) {
	vector<int> arr(n);

	for (int i = 0; i < n; i++)
		arr[i] = rand() % n;

	return arr;
}

//searching algorytms
void linearSearch(int arrLength) {
	vector<int> arr;
	double totalTime;

	//testing Sorted Array
	totalTime = 0;
	arr = createSortedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] == target)
				break;
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Sorted Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

	//testing Reversed Array
	totalTime = 0;
	arr = createReversedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] == target)
				break;
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Reversed Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

	//testing Random Array
	totalTime = 0;
	arr = createRandomArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] == target)
				break;
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Random Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

}

void binarySearch(int arrLength) {
	vector<int> arr;
	double totalTime;
	int leftPointer = 0;
	int rightPointer = arrLength - 1;

	//testing Sorted Array
	totalTime = 0;
	arr = createSortedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		while (leftPointer <= rightPointer) {
			int mid = leftPointer + (rightPointer - leftPointer) / 2;

			if (arr[mid] == target) {
				break;
			}
			else if (arr[mid] > target) {
				rightPointer = mid - 1;
			}
			else {
				leftPointer = mid + 1;
			}
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Sorted Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

	//testing Reversed Array
	totalTime = 0;
	leftPointer = 0;
	rightPointer = arrLength - 1;
	arr = createReversedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		while (leftPointer <= rightPointer) {
			int mid = leftPointer + (rightPointer - leftPointer) / 2;

			if (arr[mid] == target) {
				break;
			}
			else if (arr[mid] > target) {
				rightPointer = mid - 1;
			}
			else {
				leftPointer = mid + 1;
			}
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Reversed Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

}

void interpolationSearch(int arrLength) {
	vector<int> arr;
	double totalTime;
	int leftPointer = 0;
	int rightPointer = arrLength - 1;

	//testing Sorted Array
	totalTime = 0;
	arr = createSortedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		while (leftPointer <= rightPointer && target >= arr[leftPointer] && target <= arr[rightPointer]) {
			int pos = leftPointer + ((double)(rightPointer - leftPointer) / (arr[rightPointer] - arr[leftPointer])) * (target - arr[leftPointer]);

			if (arr[pos] == target) {
				break;
			}
			else if (arr[pos] > target) {
				rightPointer = pos - 1;
			}
			else {
				leftPointer = pos + 1;
			}
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Sorted Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

	//testing Reversed Array
	totalTime = 0;
	leftPointer = 0;
	rightPointer = arrLength - 1;
	arr = createReversedArray(arrLength);
	for (int test = 0; test < NUM_TESTS; ++test) {
		int target = rand() % arrLength;

		clock_t start_time = clock();
		while (leftPointer <= rightPointer && target >= arr[leftPointer] && target <= arr[rightPointer]) {
			int pos = leftPointer + ((double)(rightPointer - leftPointer) / (arr[rightPointer] - arr[leftPointer])) * (target - arr[leftPointer]);

			if (arr[pos] == target) {
				break;
			}
			else if (arr[pos] > target) {
				rightPointer = pos - 1;
			}
			else {
				leftPointer = pos + 1;
			}
		}
		clock_t end_time = clock();

		totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	}
	cout << left << setw(60) << "Average time for a Reversed Array with length " + to_string(arrLength) + ", is: " << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

}

void binaryTreeSearch(TreeNode* root, int target) {
	if (root == nullptr)
		return;
	if (root -> val == target)
		return;
	if (target < root -> val)
		return binaryTreeSearch(root->leftPointer, target);
	else
		return binaryTreeSearch(root->rightPointer, target);
}

int main() {
	int n[4] = { 100, 1000, 10000, 100000 };
	int alID;
	double totalTime;

	// Create random number in range [0, 31]
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 31);

	srand(time(nullptr));

	//Create binary trees
	TreeNode* sortedBT = createSortedBT(0, 31);
	TreeNode* reversedBT = createReversedBT(0, 31);

	cout << "Choose algorytm to analize" << endl;
	cout << "1) Linear Search \n2) Binary tree search \n3) Binary search \n4) Interpolation Search" << endl;
	try {
		cin >> alID;
		if (alID < 1 || alID > 4)
			throw invalid_argument("Invalid algorithm ID. It must be between 1 and 4.");
	}
	catch (const invalid_argument& e) {
		system("cls");
		cout << e.what();
		return 0;
	}

	system("cls");

	switch (alID) {
	//Linear Search
	case 1:
		cout << "Average time for Linear Search: \n";
		for (int i = 0; i < 4; i++) {
			linearSearch(n[i]);
			cout << endl;
		}
		break;

	//Binary Tree Search
	case 2:
		//test Sorted Binary Tree Search
		totalTime = 0;
		for (int i = 0; i < NUM_TESTS; i++) {
			int target = dis(gen);
			clock_t start_time = clock();
			binaryTreeSearch(sortedBT, target);
			clock_t end_time = clock();
			totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
		}
		cout << "Average time for Sorted Binary Tree Search is   \t" << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";

		//test Reversed Binary Tree Search
		totalTime = 0;
		for (int i = 0; i < NUM_TESTS; i++) {
			int target = dis(gen);
			clock_t start_time = clock();
			binaryTreeSearch(reversedBT, target);
			clock_t end_time = clock();
			totalTime += double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
		}
		cout << "Average time for Reversed Binary Tree Search is \t" << fixed << setprecision(4) << totalTime / NUM_TESTS << " miliseconds \n";
		break;

	//Binary Search
	case 3:
		cout << "Average time for Binary Search: \n";
		for (int i = 0; i < 4; i++) {
			binarySearch(n[i]);
			cout << endl;
		}
		break;

	//Interpolation Search
	case 4:
		cout << "Average time for Interpolation Search: \n";
		for (int i = 0; i < 4; i++) {
			interpolationSearch(n[i]);
			cout << endl;
		}
		break;
	}

	return 0;
}