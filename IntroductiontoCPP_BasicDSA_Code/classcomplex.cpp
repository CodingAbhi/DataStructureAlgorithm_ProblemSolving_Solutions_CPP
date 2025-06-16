class mycomplex
{
private:
    int real;
    int img;

public:
    mycomplex(int r, int i)
    {
        real = r;
        img = i;
    }

    void print()
    {
        cout << real << " " << img << "i" << endl;
    }
    void multiply(mycomplex const &c2)
    {
        int a = real;
        int b = img;
        int x = c2.real;
        int y = c2.img;
        int areal = a * x - b * y;
        int aimg = a * y + x * b;
        real = areal;
        img = aimg;
    }
    void add(mycomplex const &c2)
    {
        real = real + c2.real;
        img = img + c2.img;
    }
};