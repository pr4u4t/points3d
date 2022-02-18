// --> YOUR NAME here
// Few comments describing the class Points3D

#ifndef CSCI335_HOMEWORK1_POINTS3D_H_
#define CSCI335_HOMEWORK1_POINTS3D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points3D {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation.

        // Zero-parameter constructor.
        // Set size to 0.
        Points3D(){
            this->_size = 0;
            this->_sequence = 0;
        };

        // Copy-constructor.
        Points3D(const Points3D &rhs){
            this->_size = rhs.size();
            this->_sequence = new std::array<Object, 3>[this->_size];
            
            for(size_t i = 0; i < this->_size; ++i){
                this->_sequence[i] = rhs._sequence[i];  
            }
        };

        // Copy-assignment.
        Points3D& operator=(const Points3D &rhs){
            Points3D copy = rhs;
            std::swap(*this, copy);
            return *this;
        };

        // Move-constructor.
        Points3D(Points3D &&rhs){
            this->_size = rhs._size;
            rhs._size = 0;
            this->_sequence = rhs._sequence;
            rhs._sequence = 0;
        };

        // Move-assignment.
        // Just use std::swap() for all variables.
        Points3D& operator=(Points3D &&rhs){
            this->_size = rhs._size;
            this->_sequence = rhs._sequence;
            return *this;
        };

        ~Points3D() = default;

        // End of big-five.

        // One parameter constructor.
        Points3D(const std::array<Object, 3>& item) {
            this->_sequence = new std::array<Object, 3>(item);
            this->_size = 1;
        }

        size_t size() const {
            return this->_size;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.
        const std::array<Object, 3>& operator[](size_t location) const {
            if(location >= this->_size){
                std::abort();
            }
            
            return this->_sequence[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        friend Points3D operator+(const Points3D &c1, const Points3D &c2) {
            // Code missing.
            Points3D ret(c1.size() > c2.size() ? c1 : c2);
            Points3D add(c1.size() < c2.size() ? c1 : c2);
            
            for(size_t i = 0; i < add.size(); ++i){
                for(size_t j = 0; j < 3; ++j){
                    ret._sequence[i][j] += add._sequence[i][j];
                }
            }
            
            return ret;
        }

        // Overloading the << operator.
        friend std::ostream &operator<<(std::ostream &out, const Points3D &some_points) {
            for(size_t i = 0; i < some_points.size(); ++i){
                out << '(' << some_points[i][0] << ',' << some_points[i][1] << ',' << some_points[i][2] << ')';
            }
            
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        friend std::istream &operator>>(std::istream &in, Points3D &some_points) {
            size_t points;
            in >> points;
            
            if(some_points._sequence){
                delete some_points._sequence;
                some_points._sequence = 0;
            }
            some_points._sequence = new std::array<Object, 3>[points];
            
            for(size_t i = 0; i < points; ++i){
                for(int c = 0; c < 3; ++c){
                    in >> some_points._sequence[i][c];
                }    
            }
            
            some_points._size = points;
            
            return in;
        }

    private:
        // Sequence of points.
        std::array<Object, 3> *_sequence;
        // Size of sequence.
        size_t _size;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS3D_H_
