#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>

class SetOfIntegers {
public:
    static constexpr std::size_t kCapacity = 100;

    SetOfIntegers() = default;

    SetOfIntegers(const int values[], std::size_t size) {
        for (std::size_t i = 0; i < size; ++i) {
            insert(values[i]);
        }
    }

    bool contains(int value) const {
        return indexOf(value) != count_;
    }

    bool empty() const {
        return count_ == 0;
    }

    void insert(int value) {
        if (contains(value)) {
            return;
        }
        if (count_ == kCapacity) {
            throw std::overflow_error("Set capacity exceeded.");
        }
        elements_[count_++] = value;
    }

    void erase(int value) {
        const std::size_t index = indexOf(value);
        if (index == count_) {
            return;
        }

        for (std::size_t i = index; i + 1 < count_; ++i) {
            elements_[i] = elements_[i + 1];
        }
        --count_;
    }

    SetOfIntegers setUnion(const SetOfIntegers& other) const {
        SetOfIntegers result = *this;
        for (std::size_t i = 0; i < other.count_; ++i) {
            result.insert(other.elements_[i]);
        }
        return result;
    }

    SetOfIntegers intersection(const SetOfIntegers& other) const {
        SetOfIntegers result;
        for (std::size_t i = 0; i < count_; ++i) {
            if (other.contains(elements_[i])) {
                result.insert(elements_[i]);
            }
        }
        return result;
    }

    SetOfIntegers difference(const SetOfIntegers& other) const {
        SetOfIntegers result;
        for (std::size_t i = 0; i < count_; ++i) {
            if (!other.contains(elements_[i])) {
                result.insert(elements_[i]);
            }
        }
        return result;
    }

    void clear() {
        count_ = 0;
    }

    std::size_t size() const {
        return count_;
    }

    void print() const {
        std::cout << "{ ";
        for (std::size_t i = 0; i < count_; ++i) {
            std::cout << elements_[i];
            if (i + 1 < count_) {
                std::cout << ", ";
            }
        }
        std::cout << " }\n";
    }

private:
    std::array<int, kCapacity> elements_{};
    std::size_t count_ = 0;

    std::size_t indexOf(int value) const {
        for (std::size_t i = 0; i < count_; ++i) {
            if (elements_[i] == value) {
                return i;
            }
        }
        return count_;
    }
};

int main() {
    const int initialValues[] = {1, 5, 8, 7, 6};
    SetOfIntegers first(initialValues, 5);
    SetOfIntegers second;
    second.insert(7);
    second.insert(9);

    first.insert(9);
    first.erase(5);

    std::cout << "Union: ";
    first.setUnion(second).print();

    std::cout << "Intersection: ";
    first.intersection(second).print();

    std::cout << "Difference: ";
    first.difference(second).print();

    SetOfIntegers cleared = first.setUnion(second);
    cleared.clear();
    std::cout << "After clear: ";
    cleared.print();
    std::cout << "Size: " << cleared.size() << '\n';

    return 0;
}
