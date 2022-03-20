//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, create a base Shape class that both Circle and Rectangle inherit from, try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  


#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define pi 3.14

struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

	int x;
	int y;

};

struct Size {

	Size() :
		width(0),
		height(0) {}

	Size(int width_, int height_) :
		width(width_),
		height(height_) {}

	int width;
	int height;
};

ostream& operator<<(std::ostream& os, const Point& p)  //std::cout
{
	os << p.x << "/" << p.y;
	return os;
}

////////////////////class Shape////////////////////
class Shape
{
public:
	Shape(const Point& center):m_center(center) {}
	Shape(){}
	virtual string name() const = 0;  // virtual! const in the end beacuse we get here with const 
	virtual size_t area()const =0;
	const Point& center() const
	{
		return m_center;
	}
protected:
	Point m_center;

};
//////////////////class Rectangle/////////////////////
class Rectangle:public Shape 
{
public:
	Rectangle(const Point& center, const Size& size) :m_size(size)
	{
		m_center = center;
	}
	const Size& size() //the return size is const
	{
		return m_size;
	}
	size_t area() const    //we get here with const rect so the function should be const
	{
		return m_size.width * (size_t)m_size.height;
	}
    string name() const
	{
		return "Rectangle";
	}

protected:
	Size  m_size;
};

//////////////////class Circle////////////////////////
class Circle :public Shape
{
public:
	Circle(const Point& p, double r) : m_radios(r)
	{
		m_center = p;
	}
	double radios() {
		return m_radios;
	}
	string name() const
	{
		return "Circle";
	}
	size_t area() const
	{
		return (pi * m_radios * m_radios);  
	}
	
protected:
	double m_radios;
};


int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{ &circle1, &rect1, &circle2 };
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}