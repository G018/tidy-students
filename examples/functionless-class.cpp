class FunctionlessClass1 {
	FunctionlessClass1();
};

class FunctionlessClass2 {
	int i;
	double b;
	FunctionlessClass2();
};

class FunctionlessClass3 : private FunctionlessClass1 {
	int i;
	double b;
	int arr[];
	FunctionlessClass3();
};

class BaseClass {
	double b;

	BaseClass();
	virtual void func1();
	void func2();
};

class InheritedClass : public BaseClass {
	int i;

	InheritedClass();
};

struct FunctionlessStruct {
	int i;
	double b;
};
