#ifndef POLY_H
#define POLY_H

#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>
#include <thread>
#include <map>

using power = size_t;
using coeff = int;

class polynomial
{

private:
    // std::vector<std::pair<power,coeff>> polynomialVec;
    std::map<power, coeff> polynomialMap;

    ///////MAP code
    

public:
    /**
     * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
     *
     */
    // polynomial(): polynomialVec({{0,0}}) {};
    polynomial(): polynomialMap({{0,0}}) {};

    /**
     * @brief Construct a new polynomial object from an iterator to pairs of <power,coeff>
     *
     * @tparam Iter
     *  An iterator that points to a std::pair<power, coeff>
     * @param begin
     *  The start of the container to copy elements from
     * @param end
     *  The end of the container to copy elements from
     */
    template <typename Iter>
    polynomial(Iter begin, Iter end) {
        while (begin != end)
        {
            if((*begin).second != 0){
                // polynomialVec.push_back(*begin);
                polynomialMap[(*begin).first] = (*begin).second;
            }
            begin++;
        }
    }

    /**
     * @brief Construct a new polynomial object from an existing polynomial object
     *
     * @param other
     *  The polynomial to copy
     */
    // polynomial(const polynomial &other) : polynomialVec(other.polynomialVec) {};
    polynomial(const polynomial& other) : polynomialMap(other.polynomialMap) {}

    /**
     * @brief Prints the polynomial.
     *
     * Only used for debugging, isn't graded.
     *
     */
    void print() const;

    // std::vector<std::pair<power,coeff>> getPolyVec() const {
    //     return polynomialVec;
    // }
    std::map<power, coeff> getPolyMap() const {
        return polynomialMap;
    }


    /**
     * @brief Turn the current polynomial instance into a deep copy of another
     * polynomial
     *
     * @param other
     * The polynomial to copy
     * @return
     * A reference to the copied polynomial
     */
    // polynomial &operator=(const polynomial &other);
    polynomial& operator=(const polynomial& other) {
        if (this != &other) {
            polynomialMap = other.polynomialMap;
        }
        return *this;
    }

    /**
     * Overload the +, * and % operators. The function prototypes are not
     * provided.
     * 
     * Addition (+) should support
     * 1. polynomial + polynomial
     * 2. polynomial + int
     * 3. int + polynomial
     * 
     * Multiplication (*) should support
     * 1. polynomial * polynomial
     * 2. polynomial * int
     * 3. int * polynomial
     * 
     * Modulo (%) should support
     * 1. polynomial % polynomial
     */

    // poly + poly
    polynomial operator+(const polynomial& p) const;
    
    // poly + int
    polynomial operator+(int val) const;

    // poly * int
    polynomial operator*(int val) const;

    // poly * poly
    polynomial operator*(const polynomial& p) const;

    // poly % poly
    polynomial operator%(const polynomial& p) const;

    /**
     * @brief Returns the degree of the polynomial
     *
     * @return size_t
     *  The degree of the polynomial
     */
    size_t find_degree_of() const;

    /**
     * @brief Returns a vector that contains the polynomial is canonical form. This
     *        means that the power at index 0 is the largest power in the polynomial,
     *        the power at index 1 is the second largest power, etc.
     *
     *        ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
     *
     *        Note: any terms that have a coefficient of zero aren't returned in
     *        in the canonical form, with one exception.
     *        See the above example (there's no x^3 term, so
     *        there's no entry in the vector for x^3)
     *
     *        The only exception to this is the polynomial 0. If your polynomial is
     *        just the constant 0 then you would return a single entry of [(0,0)]
     *
     *        ie. y = 0 would be returned as [(0,0)]
     *
     * @return std::vector<std::pair<power, coeff>>
     *  A vector of pairs representing the canonical form of the polynomial
     */
    std::vector<std::pair<power, coeff>> canonical_form() const;

    bool isZero() const;


};

// int + poly
polynomial operator+(int val, const polynomial& p);

// int * poly
polynomial operator*(int val, const polynomial& p);

// multiplication helper function
void multiply_helper_f(std::pair<power, coeff> p1, std::map<power, coeff> p2, std::map<power, coeff> &res);

polynomial multiply_helper(polynomial& p1, polynomial& p2);

std::map<power, coeff> ParBF(const std::map<power, coeff>& A, const std::map<power, coeff>& B, int d, std::map<power, coeff>& sol);

void BF(std::map<power, coeff> A, std::map<power, coeff> B, std::map<power, coeff>& sol);

std::map<power, coeff> polynomialModulo(const std::map<power, coeff>& dividend, const std::map<power, coeff>& divisor);


#endif
