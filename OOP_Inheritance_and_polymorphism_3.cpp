#include <iostream>
#include <cmath>
#include <vector>

class Figure {
public:
    Figure(int sides_count = 0) : sides_count(sides_count) {}

    virtual void print_info() const {
        std::cout << "Фигура:\n";
        std::cout << (check() ? "Правильная" : "Неправильная") << "\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
    }

    virtual bool check() const {
        return sides_count == 0;
    }

protected:
    int sides_count;
};

class Triangle : public Figure {
public:
    Triangle(double a, double b, double c, double A, double B, double C)
        : Figure(3), a(a), b(b), c(c), A(A), B(B), C(C) {}

    void print_info() const override {
        std::cout << "Треугольник:\n";
        std::cout << (check() ? "Правильная" : "Неправильная") << "\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }

    bool check() const override {
        return (A + B + C == 180);
    }

protected:
    double a, b, c;
    double A, B, C;
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b, double c, double A, double B, double C)
        : Triangle(a, b, c, A, B, C) {}

    bool check() const override {
        return Triangle::check() && (C == 90);
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b, double c, double A, double B, double C)
        : Triangle(a, b, c, A, B, C) {}

    bool check() const override {
        return Triangle::check() && (a == c && A == C);
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double side)
        : Triangle(side, side, side, 60, 60, 60) {}

    bool check() const override {
        return Triangle::check() && (a == b && b == c && A == 60 && B == 60 && C == 60);
    }
};

class Quadrilateral : public Figure {
public:
    Quadrilateral(double a, double b, double c, double d, double A, double B, double C, double D)
        : Figure(4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void print_info() const override {
        std::cout << "Четырёхугольник:\n";
        std::cout << (check() ? "Правильная" : "Неправильная") << "\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }

    bool check() const override {
        return (A + B + C + D == 360);
    }

protected:
    double a, b, c, d;
    double A, B, C, D;
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(double a, double b)
        : Quadrilateral(a, b, a, b, 90, 90, 90, 90) {}

    bool check() const override {
        return Quadrilateral::check() && (a == c && b == d && A == 90 && B == 90 && C == 90 && D == 90);
    }
};

class Square : public Rectangle {
public:
    Square(double side)
        : Rectangle(side, side) {}
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(double a, double b, double A, double B)
        : Quadrilateral(a, b, a, b, A, B, A, B) {}

    bool check() const override {
        return Quadrilateral::check() && (a == c && b == d && A == C && B == D);
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double side, double A, double B)
        : Parallelogram(side, side, A, B) {}

    bool check() const override {
        return Parallelogram::check() && (a == b && b == c && c == d);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Figure*> figures = {
        new Figure(),
        new Triangle(10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 40, 90),
        new IsoscelesTriangle(10, 20, 10, 50, 60, 50),
        new EquilateralTriangle(30),
        new Quadrilateral(10, 20, 30, 40, 50, 60, 70, 80),
        new Rectangle(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (Figure* figure : figures) {
        figure->print_info();
        std::cout << std::endl;
    }

    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}
