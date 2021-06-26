#include<iostream>
#include<cstdlib>

class Test {
private:
    int* arr;
    int arrSize;
    void initialization() {
        for (int i = 0; i < arrSize; i++)
        {
            arr[i] = rand() % 100;
        }
    }
public:
    Test() {
        arr = nullptr;
        arrSize = 0;
    }

    Test(int size) {
        arrSize = size;
        arr = new int[arrSize];
        initialization();
    }

    Test(Test& t) {
        arr = new int[t.arrSize];
        this->arrSize = t.arrSize;
        for (int i = 0; i < arrSize; i++) {
            arr[i] = t.arr[i];
        }
    }

    Test(Test&& t) {
        arr = new int[t.arrSize];
        this->arrSize = t.arrSize;
        this->arr = t.arr;
        t.arr = nullptr;

    }

    void printArr() {
        using std::cout;
        for (int i = 0; i < arrSize; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    Test& operator=(Test& t) {
        if (arr != nullptr) delete[]arr;
        arr = new int[t.arrSize];
        this->arrSize = t.arrSize;
        for (int i = 0; i < arrSize; i++) {
            arr[i] = t.arr[i];
        }
        return *this;
    }

    Test& operator=(Test&& t) {
        if (arr != nullptr) {
            delete[]arr;
        }
        this->arr = t.arr;
        this->arrSize = t.arrSize;
        t.arr = nullptr;
        return *this;
    }

    friend Test initializationVal(int val, int quantity);

    ~Test() {
        if (arr != nullptr) {
            delete[]arr;
        }
    }

};

Test initializationVal(int val, int quantity) {
    Test t;
    t.arr = new int[quantity];
    t.arrSize = quantity;
    for (int i = 0; i < quantity; i++) {
        t.arr[i] = val;
    }
    return t;
}

int main()
{
    Test t1(6);
    t1.printArr();

    Test t2(4);
    t2.printArr();

    t2 = t1;
    t2.printArr();

    t1 = Test(3);
    t1.printArr();

    Test t3(t1);
    t3.printArr();

    Test t4 = initializationVal(4, 7);
    t4.printArr();

    return 0;
}