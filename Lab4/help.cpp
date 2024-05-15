#include "help.h"
#include <algorithm>
#include <unordered_set>
#include <thread>
#include <mutex>

std::mutex mtx;

// void polynomial::print() const {
//     bool firstTerm = true; // Used to handle the '+' sign correctly

//     for (const auto& term : polynomialVec) {
//         int power = term.first;
//         double coeff = term.second;

//         // Handling the first term without a leading '+'
//         if (!firstTerm) {
//             std::cout << " + ";
//         } else {
//             firstTerm = false;
//         }

//         // Print the term
//         std::cout << coeff << "x^" << power;
//     }

//     std::cout << std::endl; // End the line after printing the polynomial
// }
void polynomial::print() const {
    bool firstTerm = true; // Used to handle the '+' sign correctly
    for (const auto& term : polynomialMap) {
        power pow = term.first;
        coeff coef = term.second;
        // Handling the first term without a leading '+'
        if (!firstTerm) {
            std::cout << " + ";
        } else {
            firstTerm = false;
        }
        // Print the term
        std::cout << coef << "x^" << pow;
    }
    std::cout << std::endl; // End the line after printing the polynomial
}

// polynomial& polynomial::operator=(const polynomial &other) {
//     if (this != &other) {
//         polynomialVec = other.polynomialVec;
//     }
//     return *this;
// }

// polynomial polynomial::operator+(int val) const {
//     std::vector<std::pair<power,coeff>> copyPolyVec = getPolyVec();
//     int i = 0;
//     while (copyPolyVec[i].first != 0 && i < copyPolyVec.size()) {
//         i++;
//     }
//     if (i == copyPolyVec.size()) {
//         copyPolyVec.push_back({0,val});
//     } else {
//         copyPolyVec[i].second += val;
//     }
//     return polynomial(copyPolyVec.begin(), copyPolyVec.end());
// }
polynomial polynomial::operator+(int val) const {
    std::map<power, coeff> result = getPolyMap();
    auto it = result.find(0); // Look for the term with power 0
    if (it == result.end()) {
        // If term with power 0 doesn't exist, add a new term
        result.insert({0, val});
    } else {
        // If term with power 0 exists, update its coefficient
        it->second += val;
    }
    return polynomial(result.begin(), result.end()); // Return a copy of the current object
}

// polynomial polynomial::operator+(const polynomial& p) const {

//     std::vector<std::pair<power,coeff>> copyPolyVecP1 = this->canonical_form();
//     std::vector<std::pair<power,coeff>> copyPolyVecP2 = p.canonical_form();

//     std::vector<std::pair<power,coeff>> resultVec;

//     std::vector<int> visited_j;

//     for (int i = 0; i < copyPolyVecP1.size(); i++) {
//         for (int j = 0; j < copyPolyVecP2.size(); j++) {
//             if (copyPolyVecP1[i].first == copyPolyVecP2[j].first) {
//                 resultVec.push_back({copyPolyVecP1[i].first, copyPolyVecP1[i].second + copyPolyVecP2[j].second});
//                 visited_j.push_back(j);
//                 break;
//             } else if (j == copyPolyVecP2.size()-1) {
//                 resultVec.push_back({copyPolyVecP1[i].first, copyPolyVecP1[i].second});
//             }
//         }
//     }

//     if (visited_j.size() != copyPolyVecP2.size()) {
//         std::unordered_set<int> visitedIndices(visited_j.begin(), visited_j.end());
//         for (int j = 0; j < copyPolyVecP2.size(); j++) {
//             if (visitedIndices.find(j) == visitedIndices.end()) {
//                 resultVec.push_back(copyPolyVecP2[j]);
//             }
//         }
//     }
    
//     return polynomial(resultVec.begin(), resultVec.end());

// }
polynomial polynomial::operator+(const polynomial& p) const {

    std::map<power, coeff> copyPolyVecP1 = this->getPolyMap();
    std::map<power, coeff> copyPolyVecP2 = p.getPolyMap();

    std::map<power, coeff> resultVec;

    std::vector<int> visited_j;

    for (const auto& term : copyPolyVecP1) {
        resultVec[term.first] += term.second;
    }

    for (const auto& term : copyPolyVecP2) {
        resultVec[term.first] += term.second;
    }
    
    return polynomial(resultVec.begin(), resultVec.end());

}

polynomial operator+(int val, const polynomial& p) {
    polynomial copy_p(p);
    return copy_p + val;
}

// polynomial polynomial::operator*(int val) const {
//     std::vector<std::pair<power,coeff>> copyPolyVec = getPolyVec();
//     for (int i = 0; i < copyPolyVec.size(); i++) {
//         copyPolyVec[i].second = copyPolyVec[i].second * val;
//     }
//     return polynomial(copyPolyVec.begin(), copyPolyVec.end());
// }
polynomial polynomial::operator*(int val) const {
    std::map<power, coeff> copyPolyVec = getPolyMap();
    for (const auto& term : copyPolyVec) {
        copyPolyVec[term.first] *= val;
    }
    return polynomial(copyPolyVec.begin(), copyPolyVec.end());
}

////////MAP code

polynomial polynomial::operator*(const polynomial& p) const {
    std::map<power, coeff> p1 = getPolyMap();
    std::map<power, coeff> p2 = p.getPolyMap();
    if(p2.size()>p1.size()){
        std::swap(p1, p2);
    }
    // std::map<power, coeff> res = ParBF(p1, p2, 2);   ///Recursive solution
    //MT solution
    unsigned int numThreads = std::thread::hardware_concurrency();
    // unsigned int numThreads = 16;
    //std::cout<< "NUM THREADS: " << n << std::endl;

    std::thread threads[numThreads];
    std::map<power, coeff> sols[numThreads];
    std::map<power, coeff> splitPolys[numThreads];

    auto iter = std::next(p1.begin(), p1.size() / numThreads);
    
    for(int i = 0; i < numThreads; ++i){
        
        if(i == 0){
            splitPolys[i].insert(p1.begin(), iter);
        }
        else if(i == numThreads - 1){
            splitPolys[i].insert(iter, p1.end());
        }
        else{
            auto end = std::next(iter, p1.size()/numThreads);
            splitPolys[i].insert(iter, end);
            iter = end;
        }
    
        // threads[i] = std::thread(BF, splitPolys[i], p2, std::ref(sols[i]));
        threads[i] = std::thread(ParBF, splitPolys[i], p2, 1, std::ref(sols[i]));
        // splitPolys[i].insert()
    }

    for(int i = 0; i < numThreads; ++i){
        threads[i].join();
        // std::cout << "SIZE: " << sols[i].size() << std::endl;
    }

    polynomial result;
    for(int i = 0; i < numThreads; ++i){
        result = result + polynomial(sols[i].begin(), sols[i].end());
    }

    // std::map<power, coeff> A1, A2, A3, A4;
    // std::map<power, coeff> sol1, sol2, sol3, sol4;
    // auto quart1A = std::next(p1.begin(), p1.size() / n);
    // auto quart2A = std::next(quart1A, p1.size() / n);
    // auto quart3A = std::next(quart2A, p1.size() / n);
    // A1.insert(p1.begin(), quart1A);
    // A2.insert(quart1A, quart2A);
    // A3.insert(quart2A, quart3A);
    // A4.insert(quart3A, p1.end());
    // std::thread t1(BF, A1, p2, std::ref(sol1));
    // std::thread t2(BF, A2, p2, std::ref(sol2));
    // std::thread t3(BF, A3, p2, std::ref(sol3));
    // std::thread t4(BF, A4, p2, std::ref(sol4));
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // polynomial half1(sol1.begin(), sol1.end());
    // polynomial half2(sol2.begin(), sol2.end());
    // polynomial half3(sol3.begin(), sol3.end());
    // polynomial half4(sol4.begin(), sol4.end());
    // return half1+half2+half3+half4;
    return (result);
}

// polynomial polynomial::operator*(const polynomial& p) const {
//     polynomial p1(*this);
//     polynomial p2(p);
//     polynomial result = multiply_helper(p1, p2);
//     return result;
// }


polynomial operator*(int val, const polynomial& p) {
    polynomial copy_p(p);
    return copy_p * val;
}

// size_t polynomial::find_degree_of() const {
//     size_t max = 0;
//     for(int i = 0; i < polynomialVec.size(); i++){
//         if(polynomialVec[i].first > max && polynomialVec[i].second != 0) {
//             max = polynomialVec[i].first;
//         }
//     }
//     return max;
// }
size_t polynomial::find_degree_of() const {
    if (polynomialMap.empty()) {
        // If the map is empty, the degree is typically considered to be 0
        return 0;
    } else {
        // The degree is the highest power in the polynomial
        return polynomialMap.rbegin()->first;
    }
}

// std::vector<std::pair<power, coeff>> polynomial::canonical_form() const {
//     std::vector<std::pair<power, coeff>> combinedFinalVec;
//     std::vector<std::pair<power, coeff>> res = polynomialVec;
//     std::sort(res.begin(), res.end(), [](const auto& a, const auto& b) {
//         return a.first > b.first;
//     });
//     for (size_t i = 0; i < res.size(); i++) {
//         if (res[i].second != 0) {
//             combinedFinalVec.push_back(res[i]);
//         } 
//     }
//     if (combinedFinalVec.size() == 0)  {
//         combinedFinalVec.push_back({0,0});
//     }
//     return combinedFinalVec;
// }
std::vector<std::pair<power, coeff>> polynomial::canonical_form() const {
    std::vector<std::pair<power, coeff>> canonicalVec;
    for (auto it = polynomialMap.rbegin(); it != polynomialMap.rend(); ++it) {
        if (it->second != 0) {
            canonicalVec.push_back(*it);
        }
    }
    if (canonicalVec.empty()) {
        // If the polynomial is just the constant 0, return a single entry [(0, 0)]
        canonicalVec.push_back({0, 0});
    }
    return canonicalVec;
}

// polynomial polynomial::operator%(const polynomial& p) const {

//     std::vector<std::pair<power, coeff>> canForm = this->canonical_form();
//     polynomial remainder(canForm.begin(),canForm.end());

//     canForm = p.canonical_form();
//     polynomial divisor(canForm.begin(),canForm.end());

//     size_t divisorDegree = p.find_degree_of();
//     coeff divisorLeadingCoeff = divisor.polynomialVec.front().second;

//     while ((!remainder.isZero()) && (remainder.find_degree_of() >= divisorDegree)) {
        
//         size_t degreeDiff = remainder.find_degree_of() - divisorDegree;
//         coeff coeffDiff = remainder.polynomialVec.front().second / divisorLeadingCoeff;

//         std::vector<std::pair<power, coeff>> negativeTermVec = {{degreeDiff, -coeffDiff}};
//         polynomial negativeTerm(negativeTermVec.begin(), negativeTermVec.end());

//         polynomial t = negativeTerm * divisor;

//         remainder = remainder + (negativeTerm * divisor);

//         canForm = remainder.canonical_form();
//         remainder = polynomial(canForm.begin(), canForm.end());

//     }

//     return remainder;
// }
polynomial polynomial::operator%(const polynomial& p) const {
    std::map<power, coeff> p1 = getPolyMap();
    print();
    std::map<power, coeff> p2 = p.getPolyMap();
    p.print();
    std::map<power, coeff> res = polynomialModulo(p1, p2);
    // for (const auto& term : res) {
    //     std::cout << term.second << "x^" << term.first << " ";
    // }
    return polynomial(res.begin(), res.end());
}


bool polynomial::isZero() const {
    auto itZero = polynomialMap.find(0);
    bool keyZeroPresent = (itZero != polynomialMap.end());
    bool valueAssociatedWithKeyZeroIsZero = (keyZeroPresent && itZero->second == 0);
    return polynomialMap.size() == 1 && valueAssociatedWithKeyZeroIsZero;
}

// void multiply_helper_f(std::pair<power, coeff> p1, std::vector<std::pair<power, coeff>> p2, std::vector<std::pair<power, coeff>> &res){
    
//     for (std::pair<power, coeff> i : p2) {
//         std::pair<power, coeff> resu(i.first + p1.first, i.second * p1.second);

//         // Use lock_guard for thread safety
//         // std::lock_guard<std::mutex> lock(mtx);
//         res.push_back(resu);
//     }
// }

//////MAP CODE

void multiply_helper_f(std::pair<power, coeff> p1, std::map<power, coeff> p2, std::map<power, coeff> &res){
    for (const auto& i : p2) {
        std::pair<power, coeff> resu = {i.first + p1.first, i.second * p1.second};
        // Use lock_guard for thread safety
        // std::lock_guard<std::mutex> lock(mtx);
        res.insert(resu);
    }
}

// polynomial multiply_helper(polynomial& p1, polynomial& p2) {
        
//     std::vector<std::pair<power,coeff>> copyPolyVecP1 = p1.getPolyVec();
//     std::vector<std::pair<power,coeff>> copyPolyVecP2 = p2.getPolyVec();

//     if (copyPolyVecP2.size() > copyPolyVecP1.size()) {
//         std::swap(copyPolyVecP1, copyPolyVecP2);
//     }

//     polynomial resul;


//     const int numThreads = 8; // Change this to the desired number of threads

//     for (int i = 0; i < copyPolyVecP1.size(); i += numThreads) {
//         std::vector<std::pair<power, coeff>> res[numThreads];

//         std::vector<std::thread> tS;

//         for (int j = 0; j < numThreads && i + j < copyPolyVecP1.size(); ++j) {
//             tS.emplace_back(multiply_helper_f, copyPolyVecP1[i + j], copyPolyVecP2, std::ref(res[j]));
//         }

//         for (auto& thread : tS) {
//             thread.join();
//         }
        
//         // std::cout<<"working"<<std::endl;

//         for (int j = 0; j < numThreads && i + j < copyPolyVecP1.size(); ++j) {
//             resul = resul + polynomial(res[j].begin(), res[j].end());
//         }
//     }

//     return resul;
// }


////MAP CODE

std::vector<power> getKeys(const std::map<power, coeff>& myMap) {
    std::vector<power> keys;

    for (const auto& entry : myMap) {
        keys.push_back(entry.first);
    }

    return keys;
}

polynomial multiply_helper(polynomial& p1, polynomial& p2) {
        
    std::map<power, coeff> copyPolyVecP1 = p1.getPolyMap();
    std::map<power, coeff> copyPolyVecP2 = p2.getPolyMap();

    if (copyPolyVecP2.size() > copyPolyVecP1.size()) {
        std::swap(copyPolyVecP1, copyPolyVecP2);
    }

    polynomial resul;


    const int numThreads = 6; // Change this to the desired number of threads

    std::vector<power> keys1 = getKeys(copyPolyVecP1);
    // std::vector<power> keys2 = getKeys(copyPolyVecP2);
    

    for (size_t i = 0; i < keys1.size(); i += 0) {
        std::map<power, coeff> res[numThreads];



        std::vector<std::thread> tS;

        for (int j = 0; j < numThreads && i + j < keys1.size(); ++j) {
            std::pair<power, coeff> pair1 = {keys1[i + j], copyPolyVecP1[keys1[i + j]]};
            tS.emplace_back(multiply_helper_f, pair1, copyPolyVecP2, std::ref(res[j]));
        }

        for (auto& thread : tS) {
            thread.join();
        }
        
        std::cout<<"working"<<std::endl;

        for (int j = 0; j < numThreads && i + j < copyPolyVecP1.size(); ++j) {
            polynomial px = polynomial(res[j].begin(), res[j].end());
            // px.print();
            resul = resul + px;
        }

        i+=numThreads;
    }

    return resul;
}

std::map<power, coeff> ParBF(const std::map<power, coeff>& A, const std::map<power, coeff>& B, int d, std::map<power, coeff>& sol) {
    std::map<power, coeff> C;

    // Base case: if depth is <= 0 or A has only one term
    if (d <= 0 || A.size() == 1) {
        for (const auto& termA : A) {
            for (const auto& termB : B) {
                power sumPower = termA.first + termB.first;
                coeff productCoeff = termA.second * termB.second;
                C[sumPower] += productCoeff;
            }
        }
        return C;
    }

    // Split the polynomials
    std::map<power, coeff> A1, A2;
    auto midA = std::next(A.begin(), A.size() / 2);
    A1.insert(A.begin(), midA);
    A2.insert(midA, A.end());

    // Recursive calls
    std::map<power, coeff> C1 = ParBF(A1, B, d - 1, sol);
    std::map<power, coeff> C2 = ParBF(A2, B, d - 1, sol);

    // Merge the results
    for (const auto& term : C1) {
        C[term.first] += term.second;
    }

    for (const auto& term : C2) {
        C[term.first] += term.second;
    }

    sol = C;
    return C;
}

void BF(std::map<power, coeff> A, std::map<power, coeff> B, std::map<power, coeff>& sol) {
    std::map<power, coeff> result;

    for (const auto& termA : A) {
        for (const auto& termB : B) {
            power sumPower = termA.first + termB.first;
            coeff productCoeff = termA.second * termB.second;
            result[sumPower] += productCoeff;
        }
    }

    sol = result;
}

std::map<power, coeff> polynomialModulo(const std::map<power, coeff>& dividend, const std::map<power, coeff>& divisor) {
    std::map<power, coeff> remainder = dividend;

    while (!remainder.empty() && remainder.rbegin()->first >= divisor.rbegin()->first) {
        // Find the leading term of the remainder and divisor
        auto remainderTerm = *remainder.rbegin();
        auto divisorTerm = *divisor.rbegin();

        // Calculate the difference in powers
        int degreeDiff = remainderTerm.first - divisorTerm.first;

        // Calculate the coefficient ratio
        coeff coeffRatio = remainderTerm.second / divisorTerm.second;

        // Subtract the divisor multiplied by the ratio from the remainder
        for (const auto& term : divisor) {
            remainder[term.first + degreeDiff] -= term.second * coeffRatio;
        }

        // Remove terms with zero coefficients
        auto it = remainder.begin();
        while (it != remainder.end()) {
            if (it->second == 0.0) {
                it = remainder.erase(it);
            } else {
                ++it;
            }
        }
    }
    if(remainder.empty()){
        remainder[0] = 0;
    }

    return remainder;
}
