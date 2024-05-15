#include "poly.h"
#include <map>
#include <thread>
#include <algorithm>

//#include <sort>


polynomial::polynomial() {
    // std::map<power, coeff> def;
    // def[0] = 0;
    // pol = def;
    //degree = 0;
}

// template <typename Iter>
// polynomial::polynomial(Iter begin, Iter end) {
//     polynomial p1;
//     while(begin != end) {
//         if((*begin).second != 0) {
//             p1.pol[(*begin).first] = (*begin).second;
//             if((*begin).first > p1.degree) {
//                 p1.degree = (*begin).first;
//             }
//             begin++;
//         }
//     }
// }

polynomial::polynomial(const polynomial &other) : pol(other.pol), degree(other.degree) {
    //polynomial(other.pol.begin(), other.pol.end());
}

void polynomial::print() const{
    bool check = true;
    auto begin = this->pol.begin();
    while(begin != this->pol.end()) {
        if(!check) {
            std::cout << " + ";
        }
        else {
            check = false;
        }
        if((*begin).second != 0) {
            std::cout << (*begin).second << "x^" << (*begin).first;
        }
        begin++;
        
    }
    std::cout << std::endl;
}

polynomial &polynomial::operator=(const polynomial &other) {
    if(this == &other) return *this;

    polynomial temp = other;
    std::swap(this->pol, temp.pol);
    std::swap(this->degree, temp.degree);
    return *this;
}

size_t polynomial::find_degree_of() {
    for(auto iter : this->pol) {
        if(iter.first > this->degree) {
            this->degree = iter.first;
        }
    }
    return this->degree;
}

void polynomial::updateDegree() {
    degree = 0;
    for(auto iter : this->pol) {
        if(iter.first > this->degree) {
            this->degree = iter.first;
        }
    }
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const {
    std::vector<std::pair<power, coeff>> vec;
    //std::map<power, coeff> ordered = (this->pol.begin(), this->pol.end());
    for(auto iter : this->pol) {
        vec.push_back(iter);
    }
    if(vec.empty()) {
        vec.push_back({0,0});
    }
    std::sort(vec.begin(), vec.end(), [&](std::pair<power, coeff>& pow1, std::pair<power, coeff> & pow2) {return pow1.first > pow2.first;});
    return vec;
}

polynomial polynomial::operator%(const polynomial& p) const {
    polynomial remainder = *this;
    auto otherMax = p.degree;

    while(!remainder.pol.empty() && (remainder.degree >= otherMax)) {
        auto currMax = remainder.degree;
        size_t pow = currMax - otherMax;
        int coeff = remainder.pol[currMax] / p.getMap()[otherMax];

         for(auto map : p.pol) {
            remainder.pol[map.first + pow] -= map.second * coeff;
            if(remainder.pol[map.first + pow] == 0) {
                remainder.pol.erase(map.first + pow);
                if(map.first + pow == remainder.degree) {
                    remainder.updateDegree();
                }
            }
            //remainder.print();
        }
    }
    if(remainder.pol.empty()) {
        remainder.pol[0] = 0;
    }
    return remainder;
}

polynomial polynomial::operator+(const polynomial& p) const {
    polynomial result;

    for(auto val : this->pol) {
        result.pol[val.first] += val.second;
        if(result.pol[val.first] == 0) {
            result.pol.erase(val.first);
        }
    }
    for(auto val : p.pol) {
        result.pol[val.first] += val.second;
        if(result.pol[val.first] == 0) {
            result.pol.erase(val.first);
        }
    }
    return result;
}

void polynomial::strip(const polynomial& p, size_t degDec) {
    for(auto iter : p.pol) {
        this->pol.erase(iter.first);
        this->pol[iter.first - degDec] = iter.second;
    }
}

polynomial plus2(polynomial& p1, polynomial& p2, size_t degDec) {
    polynomial result;

    for(auto val : p1.getMap()) {
        result.getMap()[val.first - degDec] += val.second;
        if(result.getMap()[val.first - degDec] == 0) {
            result.getMap().erase(val.first - degDec);
        }
    }
    for(auto val : p2.getMap()) {
        result.getMap()[val.first - degDec] += val.second;
        if(result.getMap()[val.first - degDec] == 0) {
            result.getMap().erase(val.first - degDec);
        }
    }
    return result;
}

polynomial polynomial::operator-(const polynomial& p) const {
    polynomial result;
    result.degree = this->degree > p.degree ? this->degree : p.degree;

    for(auto val : this->pol) {
        result.pol[val.first] = val.second;
        if(result.pol[val.first] == 0) {
            if(val.first == degree) {
                result.updateDegree();
            }
            result.pol.erase(val.first);
        }
    }
    for(auto val : p.pol) {
        result.pol[val.first] -= val.second;
        if(result.pol[val.first] == 0) {
            if(val.first == degree) {
                result.updateDegree();
            }
            result.pol.erase(val.first);
        }
    }
    return result;
}

polynomial polynomial::operator+(const int val) const {
    polynomial result;
    
    result = *this;

    result.pol[0] = result.pol[0] + val;
    if(result.pol[0] == 0) {
        result.pol.erase(0);
    }

    return result;
    
}

polynomial polynomial::singleMult(const polynomial& p) const{
    polynomial result;

    for(auto currval : p.pol) {
        for(auto pval : this->pol) {
            result.pol[currval.first + pval.first] += currval.second * pval.second;
            if(result.pol[currval.first + pval.first] == 0) {
                result.pol.erase(currval.first + pval.first);
            }
        }
    }
    return result;
}

void multHelper(const polynomial& split, const polynomial& other, std::unordered_map<power,coeff>& subResults) {
    polynomial split0;
    polynomial split1;
    //polynomial splitcopy = split;
    polynomial other0;
    polynomial other1;
    //polynomial othercopy = other;
    //0s will be of degree < degree/2 and 1s degree/2 and up
    //Will not be exact because we dont know if degree/2 exists, Can force it to exist
    //probbly make sure the degrees are equal
    // size_t splitDeg = splitcopy.find_degree_of();
    size_t otherDeg = other.getDegree();

    // if(splitDeg % 2 != 0) {
    //     splitDeg += 1;
    // }
    if(otherDeg % 2 != 0) {
        otherDeg += 1;
    }

    std::unordered_map<power, coeff> splitMap = split.getMap();
    std::unordered_map<power, coeff> otherMap = other.getMap();


    if(splitMap.find(otherDeg/2) == splitMap.end()) {
        splitMap[otherDeg/2] = 0;
    }

    if(otherMap.find(otherDeg/2) == otherMap.end()) {
        otherMap[otherDeg/2] = 0;
    }

    auto iterSplit = splitMap.find(otherDeg/2);
    auto otherSplit = otherMap.find(otherDeg/2);
    auto splitPrev = std::prev(iterSplit, 1);
    auto otherPrev = std::prev(otherSplit, 1);


    split0 = polynomial(splitMap.begin(), iterSplit);
    split1 = polynomial(iterSplit, splitMap.end());
    split1.strip(split1, otherDeg/2);

    other0 = polynomial(otherMap.begin(), otherSplit);
    other1 = polynomial(otherSplit, otherMap.end());
    other1.strip(other1, otherDeg/2);
    // other1

    polynomial tempSplit = split0 + split1;
    polynomial tempOther = other0 + other1;

    polynomial x = tempSplit.singleMult(tempOther);
    polynomial y = split0.singleMult(other0);
    polynomial z = split1.singleMult(other1);

    polynomial middle = x - y - z;
    std::map<power, coeff> xHalfDeg;
    std::map<power, coeff> xDeg;
    xHalfDeg[otherDeg/2] = 1; 
    xDeg[otherDeg] = 1;
    polynomial halfPoly = polynomial(xHalfDeg.begin(), xHalfDeg.end());
    polynomial fullPoly = polynomial(xDeg.begin(), xDeg.end());

    subResults = (y + middle.singleMult(halfPoly) + z.singleMult(fullPoly)).getMap();
}

void multHelper2(const polynomial& split, const polynomial& other, std::unordered_map<power,coeff>& result) {
    for(auto currval : split.getMap()) {
        for(auto pval : other.getMap()) {
            result[currval.first + pval.first] += currval.second * pval.second;
            if(result[currval.first + pval.first] == 0) {
                result.erase(currval.first + pval.first);
            }
        }
    }
}

polynomial polynomial::operator*(const polynomial& p) const {
    polynomial result;

    // for(auto currval : this->pol) {
    //     for(auto pval : p.pol) {
    //         result.pol[currval.first + pval.first] += currval.second * pval.second;
    //         if(result.pol[currval.first + pval.first] == 0) {
    //             result.pol.erase(currval.first + pval.first);
    //         }
    //     }
    // }
    // return result;

    //split bigger polynomial
    polynomial split;
    polynomial other;
    if(p.pol.size() > this->pol.size()) {
        split = p;
        other = *this;
    }
    else {
        split = *this;
        other = p;
    }

    int threads = 8;
    polynomial divPoly[threads];
    polynomial subResults[threads];
    std::thread thr[threads];

    auto begin = split.pol.begin();
    auto size = split.pol.size();
    auto perPoly = size / threads;
    auto end = std::next(begin, perPoly);


    for(int i = 0; i < threads; i++) {
        if(i == threads - 1) {
            divPoly[i].pol = polynomial(begin, split.pol.end()).pol;
            //thr[i] = std::thread(multHelper2, polynomial(begin, split.pol.end()).pol, polynomial(other.pol.begin(), other.pol.end()), std::ref(subResults[i].pol));
        }
        else {
            divPoly[i].pol = polynomial(begin, end).pol;
            //thr[i] = std::thread(multHelper2, polynomial(begin, end).pol, polynomial(other.pol.begin(), other.pol.end()), std::ref(subResults[i].pol));
            begin = end;
            std::advance(end, perPoly);
        }
        thr[i] = std::thread(multHelper2, divPoly[i], polynomial(other.pol.begin(), other.pol.end()), std::ref(subResults[i].pol));
    }

    for(int k = 0; k < threads; k++) {
        thr[k].join();
    }

    for(int i = 0; i < threads; i++) {
        result = result + subResults[i];
    }

    // std::map<power, coeff> sub;
    // multHelper(polynomial(split.pol.begin(), split.pol.end()), other, sub);

    // result.pol = sub;
    result.updateDegree();
    return result;

}



polynomial polynomial::operator*(const int val) const {
    polynomial result;
    

    for(auto curr : this->pol) {
        result.pol[curr.first] = curr.second * val;
        if(result.pol[curr.first] == 0) {
            result.pol.erase(curr.first);
        }
    }
    return result;
    
}

polynomial operator+(const int val, const polynomial& p) {
    polynomial result = p;
    return result + val;
}

polynomial operator*(const int val, const polynomial& p) {
    polynomial result = p;
    return result * val;
}