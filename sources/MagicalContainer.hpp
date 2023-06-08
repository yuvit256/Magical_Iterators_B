#pragma once
#include <vector>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> _elem;
        vector<int *> primes;

    public:
        MagicalContainer() = default;
        void addElement(int elem);
        void removeElement(int elem);
        int size() const;

        class AscendingIterator
        {
        private:
            vector<int>::iterator curr_asec;
            MagicalContainer &mgc;

        public:
            AscendingIterator(MagicalContainer &magical_container);
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator() = default;
            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            int operator*();
            AscendingIterator& operator++();
            AscendingIterator begin();
            AscendingIterator end();
        };
        class SideCrossIterator
        {
        private:
            vector<int>::reverse_iterator right;
            vector<int>::iterator left;
            int left_index;
            int right_index;
            int index;
            MagicalContainer &mgc;

        public:
            SideCrossIterator(MagicalContainer &magical_container);
            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator() = default;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            int operator*();
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };
        class PrimeIterator
        {
        private:
            vector<int *>::iterator curr_prime;
            MagicalContainer &mgc;

        public:
            PrimeIterator(MagicalContainer &magical_container);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator() = default;
            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            int operator*();
            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();
        };
    };
};