#include <vector>

void vector_max(std::vector<int> v) {
	auto max = v[0];
	for (size_t i = 1; i < v.size(); ++i) {
		if (max < v[i]) {
			max = v[i];
		}
	}
}

void vector_find(std::vector<double> v, double value) {
	bool found = false;
	for (auto it = v.begin(); it != v.end(); ++it)
		if (*it == value)
			found = true;
}

void arr_max(int size, double arr[]) {
	double max = arr[0];
	for (int i = 1; i < size; ++i)
		if (max < arr[i])
			max = arr[i];
}

void arr_find(int size, int arr[], int value) {
	bool found = false;
	for (int* p = arr; p < arr + size; ++p) {
		if (*p == value) {
			found = true;
			break;
		}
	}
}

