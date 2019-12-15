const double global_d = 1.5;
const int global_i = 3;

class MyClass {
    int i;
    double d;

    // Warn
    MyClass() {
        i = global_i;
        d = 1.1;
    }

    // Warn 
    MyClass(int i_in, double d_in) {
        i = i_in;
        d = d_in;
    }

    // Don't warn
    MyClass(double d_in) : d(d_in) {
        i = d_in - 1;
    }

    // Don't warn
    MyClass(int i_in) : i(i_in) {
        if (i == 0) {
            d = global_d;
        }
        else {
            d = 2.0;
        }
    }
 
    // Warn
    MyClass(MyClass & other) {
        i = other.i;
        d = other.d;
    }
};