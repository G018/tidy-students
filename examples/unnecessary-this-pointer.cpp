const double global_d = 1.5;
const int global_i = 3;

class MyClass {
    int i;
    double d;

public:
    MyClass() : i(global_i), d(global_d) {}

    MyClass(int i_in, double d_in) : i(i_in), d(d_in) {}
 
    MyClass(const MyClass & other) : i(other.i), d(other.d) {}

    MyClass & operator=(const MyClass & other) {
        // Don't warn
        if (&other != this) {
            i = other.i;
            d = other.d;
        }

        // Don't warn
        return *this;
    }

    ~MyClass() {}

    int get_i() {
        // Warn
        return this->i;
    }

    double get_d() {
        // Warn
        return this->d;
    }

    void set_i(int new_i) {
        // Warn
        this->i = new_i;
    }

    void set_d(double new_d) {
        // Warn
        this->d = new_d;
    }

    double add(){
        return d + i;
    }
};