// --> YOUR NAME here
// Few comments describing the class Points3D

#ifndef CSCI335_HOMEWORK1_POINTS3D_H_
#define CSCI335_HOMEWORK1_POINTS3D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <memory>
#include <cstring>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points3D {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation.

        // Zero-parameter constructor
        Points3D() 
            : _sequence(0),_size(0) /* initialize with empty values */{}

        // Copy-constructor.
        Points3D(const Points3D &rhs)
            : _sequence(rhs._sequence),_size(rhs._size) /* initialize with pointer and size from other instance*/ {}

        // Copy-assignment.
        Points3D& operator=(const Points3D &rhs){
            Points3D copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        // Move-constructor.
        Points3D(Points3D &&rhs)
            : _sequence(std::move(rhs._sequence)),_size(std::move(rhs._size)){
        }

        // Move-assignment.
        Points3D& operator=(Points3D &&rhs){
            std::swap(this->_size,rhs._size);
            std::swap(this->_sequence,rhs._sequence);
            return *this;
        }

        //No need to touch the destructor because shared_ptr handles everything
        ~Points3D() = default;

        // End of big-five.

        // One parameter constructor.
        Points3D(const std::array<Object, 3>& item)
            : _sequence(new std::array<Object, 3>),_size(1){
            *(this->_sequence) = item;
        }

        size_t size() const {
            return this->_size;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        const std::array<Object, 3>& operator[](size_t location) const {
            if(location >= this->_size){
                std::abort();
            }
            
            return this->_sequence.get()[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        friend Points3D operator+(const Points3D &c1, const Points3D &c2) {
            //Find if c1 is longer or c2 is longer
            Points3D ret((c1.size() > c2.size()) ? c1 : c2);
            //Find if c2 is shorter or c1 is shorter
            const Points3D& add = (c1.size() < c2.size()) ? c1 : c2;
            
            //Because all the time we are operating on pointers and passing memory address between instances
            //here we must ensure that memory fragment managed by `ret` is owned only by one instance which is `ret`
            //in other case we must make a copy of this fragment not to modify other instances
            ret.make_unique();
            
            //get pointers
            std::array<Object, 3>* longer = ret._sequence.get();
            std::array<Object, 3>* shorter = add._sequence.get();
            
            //Add shorter to longer
            for(size_t i = 0; i < add.size(); ++i){
                for(size_t j = 0; j < 3; ++j){
                    longer[i][j] += shorter[i][j];
                }
            }
            
            return ret;
        }

        // Overloading the << operator.
        friend std::ostream &operator<<(std::ostream &out, const Points3D &some_points) {
            if(!some_points._size || !some_points._sequence.get()){
                out << "() " << std::endl;
                return out;
            }
            
            for(size_t i = 0; i < some_points.size(); ++i){
                out << "(" << (Object) some_points[i][0] << ", " << (Object) some_points[i][1] << ", " << (Object) some_points[i][2] << ") ";
            }
            
            out << std::endl;
            
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        friend std::istream &operator>>(std::istream &in, Points3D &some_points) {
            size_t points;
            in >> points;
    
            some_points._sequence = std::shared_ptr<std::array<Object, 3>>(new std::array<Object, 3>[points]);
            std::array<Object, 3>* ptr = some_points._sequence.get();
             
            for(size_t i = 0; i < points; ++i){
                for(int c = 0; c < 3; ++c){
                    in >> ptr[i][c];
                }    
            }
            
            some_points._size = points;
            std::cout << std::endl;
            
            return in;
        }
    
    protected:
        void make_unique(){
            /* if count > 1 then we are NOT only owner of this memory fragment deep copy must be made*/
            if(this->_sequence.use_count() > 1){
                //store pointer to old memory fragment
                std::array<Object, 3>* old = this->_sequence.get();
                //reserve new momory fragment of the same size
                this->_sequence = std::shared_ptr<std::array<Object, 3>>(new std::array<Object, 3>[this->_size]);
                //copy old memory to new memory
                std::memcpy(this->_sequence.get(),old,this->_size*sizeof(std::array<Object, 3>));
            }
        }
        
    private:
        // Sequence of points.
        std::shared_ptr<std::array<Object, 3>> _sequence;
        // Size of sequence.
        size_t _size;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS3D_H_
