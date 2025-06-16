class student
{

    int age;
    int roll;

public:
    ~student()
    {
        cout << "destructor called" << endl;
    }
    student(int a)
    {
        cout << "constructor 1" << endl;
        age = a;
    }
    student(int a, int r)
    {
        cout << "constructor 2" << endl;
        age = a;
        roll = r;
    }

    void display()
    {
        cout << "age is " << age << endl;
        cout << "roll is " << roll << endl;
    }
};
