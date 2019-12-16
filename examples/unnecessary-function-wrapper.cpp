int addition(int i, int j) {
    return i + j;
}

int subtraction(int i, int j) {
    return i - j;
}

int multiplication(int i, int j) {
    return i * j;
}

int complex(int i , int j) {
    return addition(i, j) + subtraction(i, j) + multiplication(i, j);
}

int add_plus_1(int i, int j) {
    return addition(i, j) + 1;
}

// warn
int add_wrapper(int i, int j) {
    return addition(i, j);
}
