void by_index1(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] += i;
    }
}

void by_index2(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += i;
    }
}

void by_index3(int arr[], int size) {
    for (int i = 0; i < size; i += 1) {
        arr[i] += i;
    }
}

void by_index4(int arr[], int size) {
    for (int i = 0; i < size; i = i + 1) {
        arr[i] += i;
    }
}

void by_index5(int arr[], int size) {
    int i = 0;

    for (; i < size; ++i) {
        arr[i] += i;
    }
}

void sneaky_index(int arr[], int size) {
    int i = 0;
    for (int* ptr = arr; ptr + i < arr + size; ++i) {
        *(ptr + i) += i;
    }
}

void by_pointer1(int arr[], int size) {
    for (int* ptr = arr; ptr < arr + size; ++ptr) {
        *ptr += ptr - arr;
    }
}

void by_pointer2(int arr[], int size) {
    for (int* ptr = arr; ptr < arr + size; ptr++) {
        *ptr += ptr - arr;
    }
}

void by_pointer3(int arr[], int size) {
    for (int* ptr = arr; ptr < arr + size; ptr += 1) {
        *ptr += ptr - arr;
    }
}

void by_pointer4(int arr[], int size) {
    for (int* ptr = arr; ptr < arr + size; ptr = ptr + 1) {
        *ptr += ptr - arr;
    }
}

void by_pointer5(int arr[], int size) {
    int* ptr = arr;
    for (; ptr < arr + size; ++ptr) {
        *ptr += ptr - arr;
    }
}

void by_pointer6(int arr[], int size) {
    int* ptr = arr;
    int* end = arr + size;
    for (; ptr < end; ++ptr) {
        *ptr += ptr - arr;
    }
}

