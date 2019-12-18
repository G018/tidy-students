// bad variable name
int Bad = 2;

// bad class name
class bad {
	// bad variable name
	int I;
	
	// bad variable name
	void set_i(int _under) {
		I = _under;
	}
};

// functionless class
class Functionless {
	int i;
	double b;
	Functionless();
};

double check_equal(double d1, double d2) {
	// double comparison
	if (d1 == d2) {
		return d1;
	}
	return d2;
}

bool not_null(int *ptr) {
	// redundant pointer comparison
	if (ptr == nullptr) {
		return false;
	} else {
		return true;		
	}
}

// thin wrapper
bool wrapper(int *ptr) {
	return not_null(ptr);
}

void by_index(int arr[], int size) {
	// traversal by index
    for (int i = 0; i < size; ++i) {
        arr[i] += i;
    }
}

void by_pointer(int arr[], int size) {
	// traversal by pointer
    for (int* ptr = arr; ptr < arr + size; ++ptr) {
        *ptr += ptr - arr;
    }
}

class MyClass {
    int i;
    double d;

public:
    MyClass() : i(0), d(0) {}

    // unused initializer
    MyClass(int i_in, double d_in) {
    	i = i_in;
    	d = d_in;
    }
 
    MyClass(const MyClass & other) : i(other.i), d(other.d) {}

    MyClass & operator=(const MyClass & other) {
        if (&other != this) {
            i = other.i;
            d = other.d;
        }

        return *this;
    }

    ~MyClass() {}

    int get_i() {
        // unnecessary this
        return this->i;
    }
};
