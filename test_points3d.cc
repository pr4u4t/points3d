// Do not change this file other than adding header files
// if needed.
// You can also comment parts of the functions, and uncomment
// as you add more functionality.
#include <points3d.h>

#include <array>
#include <iostream>
#include <string>
using namespace std;
using namespace teaching_project;

// Place stand-alone function in unnamed namespace.
namespace {
void TestPart1() {
    Points3D<int> a, b;                                     // Two empty Points3D are created.
    cout << a.size() << " " << b.size() << endl;            // yields 0 0.
    
    const array<int, 3> a_point2{{7, 10, 11}};
    Points3D<int> d{a_point2};                              // A Points3D containing (7, 10, 11) should be created.
    cout << d << std::endl;                                              // Should just print (7, 10, 11).
    
    cout << "Enter a sequence of points (integer)" << endl;
    cin >> a;                                               
    cout << "Output1: ";
    cout << a << std::endl;  // Output should be what user entered.
    
    cout << "Enter a sequence of points (integer)" << endl;
    cin >> b; // Enter another sequence.
    cout << "Output2: ";
    cout << b << std::endl;
    
    Points3D<int> c{a};  // Calls copy constructor for c.
    cout << "After copy constructor1 c{a}: " << endl;
    cout << c << std::endl;;
    cout << a << std::endl;
    
    a = b;  // Should call the copy assignment operator for a.
    cout << "After assignment a = b" << endl;
    cout << a << std::endl;;
    Points3D<int> e = move(c);  // Move constructor for e.
    cout << "After e = move(c) " << endl;
    cout << e << std::endl;
    cout << c << std::endl;
    cout << "After a = move(e) " << endl;
    a = move(e);  // Move assignment operator for a.
    cout << a << std::endl;
    cout << e << std::endl;
}

void TestPart2() {
    Points3D<double> a, b;
    cout << "Enter a sequence of points (double)" << endl;
    cin >> a; // User provides input for Points3D a.
    cout << a << std::endl;
    cout << "Enter a sequence of points (double)" << endl;
    cin >> b; // User provides input for Points3D b.
    cout << b << endl;
    cout << "Result of a + b" << endl;
    cout << a + b << endl;
    Points3D<double> d = a + b;
    cout << "Result of d = a + b" << endl;
    cout << d << std::endl;
    cout << "Second element in a: " << endl;
    cout << a[1][0] << ", " << a[1][1] << ", " << a[1][2] << endl;  // Should print the 2nd element.
}

} // namespace

int main(int argc, char **argv) {
    TestPart1();
    TestPart2();
    return 0;
}
