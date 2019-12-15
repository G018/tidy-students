// warn
const int _bad_ = 1;
// warn
int Bad = 2;

// warn
class bad {
    // warn
    int I;
    // warn
    double D;

    // warn
    void set_i(int _under) {
        I = _under;
    }

    // warn
    void set_d(double New_d) {
        D = New_d;
    }

    double add(){
        return D + I;
    }
};

class Good {
    int i;
    double d;

    void set_i(int new_i) {
        i = new_i;
    }

    void set_d(double new_d) {
        d = new_d;
    }

    double add(){
        return d + i;
    }
};