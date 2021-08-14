#include <iostream>
#include <string>

using namespace std;

class Foo{
protected:
    string name;

public:
    virtual void setName(string aName)
    {
        name = aName;
    }
};


class Bar: public Foo{
public:
    void sayHello()
    {
        cout << "Hi, I am " << name << endl;
    }
};

class Baz : public Foo{
public:
    void sayHello()
    {
        cout << "Hello, I am " << name << endl;
    }
};

void main()
{   
    Bar bar;
    Baz baz;
    Foo * obj;
    
    obj = &bar;
    obj->setName("Bar"); 

    obj = &baz;
    obj->setName("Baz");


    bar.sayHello();
    baz.sayHello();

    system("pause");
}