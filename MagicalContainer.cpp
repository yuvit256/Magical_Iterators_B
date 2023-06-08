#include <iostream>
#include <algorithm>
#include "MagicalContainer.hpp"

using namespace std;

namespace ariel
{
    bool isPrime(int num)
    {
        if (num <= 1)
            return false;
        for (int i = 2; i < num; i++)
            if (num % i == 0)
                return false;
        return true;
    }

    void MagicalContainer::addElement(int elem)
    {
        if (auto i = find(_elem.begin(), _elem.end(), elem) != _elem.end())
        {
            throw runtime_error("Cannot add existing element");
        }
        else
        {
            _elem.push_back(elem);
            sort(_elem.begin(), _elem.end());
        }

        primes.clear();
        for (auto it = _elem.begin(); it != _elem.end(); ++it)
        {
            if (isPrime(*it))
            {
                primes.push_back(&(*it));
            }
        }
    }

    void MagicalContainer::removeElement(int elem)
    {
        auto i = find(_elem.begin(), _elem.end(), elem);
        if (i != _elem.end())
        {
            _elem.erase(i);
        }
        else
        {
            throw runtime_error("Cannot remove a non-existing element");
        }
        primes.clear();
    }

    int MagicalContainer::size() const
    {
        return _elem.size();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magical_container) : mgc(magical_container), curr_asec(magical_container._elem.begin()) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : mgc(other.mgc), curr_asec(other.curr_asec) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&(mgc) != &(other.mgc))
        {
            throw runtime_error("Different containers");
        }
        if (this != &other)
        {
            mgc = other.mgc;
            curr_asec = other.curr_asec;
        }
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator &other) const
    {
        return curr_asec == other.curr_asec;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator &other) const
    {
        return curr_asec != other.curr_asec;
    }

    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const
    {
        return curr_asec < other.curr_asec;
    }

    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const
    {
        return other.curr_asec < curr_asec;
    }

    int MagicalContainer::AscendingIterator::operator*()
    {
        if (curr_asec == mgc._elem.end())
        {
            throw std::runtime_error("Iterator is out of range");
        }
        return *curr_asec;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
    {
        if (curr_asec >= mgc._elem.end())
        {
            throw std::runtime_error("out of range");
        }
        curr_asec++;
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        AscendingIterator newBegin(mgc);
        newBegin.curr_asec = mgc._elem.begin();
        return newBegin;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        AscendingIterator newEnd(mgc);
        newEnd.curr_asec = mgc._elem.end();
        return newEnd;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magical_container) : mgc(magical_container), left(magical_container._elem.begin()), right(magical_container._elem.rbegin()), index(0), left_index(0), right_index(magical_container._elem.size() - 1)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : mgc(other.mgc), left(other.left), right(other.right), index(other.index), left_index(other.left_index), right_index(other.right_index) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&other == this)
        {
            return *this;
        }

        if (&mgc != &(other.mgc))
        {
            throw runtime_error("Different containers");
        }

        mgc = other.mgc;
        left = other.left;
        right = other.right;
        index = other.index;
        left_index = other.left_index;
        right_index = other.right_index;

        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator &other) const
    {
        return left_index == other.left_index && right_index == other.right_index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator &other) const
    {
        return left_index != other.left_index || right_index != other.right_index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const
    {
        return left_index < other.left_index;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const
    {
        return other.left_index < left_index;
    }

    int MagicalContainer::SideCrossIterator::operator*()
    {
        int size = mgc._elem.size();
        if (size != 0)
        {
            if (left_index > right_index)
            {
                throw runtime_error("out of range");
            }
        }
        if (index % 2 == 0)
        {
            return *left;
        }
        return *right;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        if (left_index > right_index)
        {
            throw runtime_error("out of range");
        }
        if (index % 2 == 0)
        {
            left++;
            left_index++;
        }
        else
        {
            right++;
            right_index--;
        }
        index++;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        SideCrossIterator newBegin(mgc);
        return newBegin;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        SideCrossIterator newEnd(mgc);
        int size = mgc._elem.size();
        if (size % 2 == 0)
        {
            newEnd.right_index = (size / 2) - 1;
            newEnd.left_index = (size / 2);
        }
        else
        {
            newEnd.right_index = (size / 2);
            newEnd.left_index = (size / 2) + 1;
        }
        advance(newEnd.left, newEnd.left_index);
        advance(newEnd.right, newEnd.right_index);
        newEnd.index = size;
        return newEnd;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magical_container) : mgc(magical_container), curr_prime(magical_container.primes.begin()) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : mgc(other.mgc), curr_prime(other.curr_prime) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&(mgc) != &(other.mgc))
        {
            throw runtime_error("Different containers");
        }
        if (this != &other)
        {
            mgc = other.mgc;
            curr_prime = other.curr_prime;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const
    {
        return curr_prime == other.curr_prime;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &other) const
    {
        return curr_prime != other.curr_prime;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const
    {
        return curr_prime < other.curr_prime;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const
    {
        return other.curr_prime < curr_prime;
    }

    int MagicalContainer::PrimeIterator::operator*()
    {
        if (curr_prime == mgc.primes.end())
        {
            throw std::runtime_error("Iterator is out of range");
        }
        return **curr_prime;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        if (curr_prime >= mgc.primes.end())
        {
            throw std::runtime_error("out of range");
        }
        curr_prime++;
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        PrimeIterator newBegin(mgc);
        newBegin.curr_prime = mgc.primes.begin();
        return newBegin;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        PrimeIterator newEnd(mgc);
        newEnd.curr_prime = mgc.primes.end();
        return newEnd;
    }

}