#pragma once
#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>

namespace alex {
    template <typename T>
    class Vector {
        private:
            T* data_ = nullptr;
            size_t size_ = 0;
            size_t capacity_ = 0;

            void grow();
        public:
            Vector() = default;
            explicit Vector(size_t count);
            Vector(size_t count, const T& value);
            Vector(std::initializer_list<T> ilist);

            ~Vector();

            Vector(const Vector& other);
            Vector(Vector&& other) noexcept;
            Vector& operator=(Vector other) noexcept;

            friend void swap(Vector& a, Vector& b) noexcept {
                using std::swap;
                swap(a.data_, b.data_);
                swap(a.size_, b.size_);
                swap(a.capacity_, b.capacity_);
            }

            T& operator[](size_t index);
            const T& operator[](size_t index) const;
            T& at(size_t index);

            void push_back(const T& value);
            void push_back(T&& value);
            void pop_back();

            template <typename... Args>
            void emplace_back(Args&&... args);

            void clear() noexcept;
            void reserve(size_t new_capacity);



            bool empty() const noexcept {return size_ == 0;}
            size_t size() const noexcept {return size_;}
            size_t capacity() const noexcept {return capacity_;} 
    };

    template <typename T>
    Vector<T>::Vector(size_t count) {
        reserve(count);
        for (size_t i = 0; i < count; i++) {
            new (data_ + i) T();
        }
        size_ = count;
    }

    template <typename T>
    Vector<T>::Vector(size_t count, const T& value) {
        reserve(count);
        for (size_t i = 0; i < count; i++) {
            new (data_ + i) T(value);
        }
        size_ = count;
    }
    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> ilist) {
        for (auto e : ilist) {
            push_back(e);
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector& other) {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; i++) {
            new (data_ + i) T(other.data_[i]);
        }
        size_ = other.size_;
    }
    template <typename T>
    Vector<T>::Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector other) noexcept {
        swap(*this, other);
        return *this;
    }
    
    template <typename T>
    T& Vector<T>::operator[](size_t index) {
        return data_[index];
    }
    template <typename T>
    const T& Vector<T>::operator[](size_t index) const {
        return data_[index];
    }

    template <typename T>
    T& Vector<T>::at(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
    template <typename T>
    void Vector<T>::grow() {
        size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
        reserve(new_capacity);
    }

    

    template <typename T>
    void Vector<T>::reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        for (size_t i = 0; i < size_; i++) {
            new (new_data + i) T(std::move(data_[i]));
            data_[i].~T();
        }
        ::operator delete(data_);
        data_ = new_data;
        capacity_ = new_capacity;
    }

    template <typename T>
    void Vector<T>::push_back(const T& value) {
        if (size_ == capacity_) grow();
        new (data_ + size_) T(value);
        size_++;
    }
    template <typename T>
    void Vector<T>::push_back(T&& value) {
        if (size_ == capacity_) grow();
        new (data_ + size_) T(std::move(value));
        size_++;
    }
    template <typename T>
    void Vector<T>::pop_back() {
        if (size_ == 0) return;
        data_[size_ - 1].~T();
        size_--;
    }

    template <typename T>
    template <typename... Args>
    void Vector<T>::emplace_back(Args&&... args) {
        if (size_ == capacity_) grow();
        new (data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }

    template <typename T>
    void Vector<T>::clear() noexcept {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
        size_ = 0;
    }

    template <typename T>
    Vector<T>::~Vector() {
        clear();
        ::operator delete (data_);
    }

    

}