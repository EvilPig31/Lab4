#ifndef ARRAY_H
#define ARRAY_H

#include <utility>
#include <memory>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    void reallocate(size_t new_capacity){
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        for(size_t i = 0; i < size_; ++i){
            new_data[i] = std::move(data_[i]);
        }
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
public:
    Array() : size_(0), capacity_(0){}
    explicit Array(size_t size) : size_(size), capacity_(size){
        if (size > 0){
            data_ = std::shared_ptr<T[]>(new T[capacity_]);
        }
    }
    Array(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()){
        if (size_ > 0){
            data_ = std::shared_ptr<T[]>(new T[capacity_]);
            size_t i = 0;
            for (const auto &item : init){
                data_[i++] = item;
            }
        }
    }
    Array(const Array &other) : size_(other.size_), capacity_(other.capacity_){
        if (size_ > 0){
            data_ = std::shared_ptr<T[]>(new T[capacity_]);
            for (size_t i = 0; i < size_; ++i){
                data_[i] = other.data_[i];
            }
        }
    }
    Array(Array &&other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_){
        other.size_ = 0;
        other.capacity_ = 0;
    }
    ~Array() = default;
    Array &operator=(const Array &other){
        if (this != &other){
            std::shared_ptr<T[]> new_data;
            if (other.size_ > 0){
                new_data = std::shared_ptr<T[]>(new T[other.capacity_]);
                for (size_t i = 0; i < other.size_; ++i){
                    new_data[i] = other.data_[i];
                }
            }
            data_ = std::move(new_data);
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }
    T &operator[](size_t index){
        if(index >= size_){
            throw std::out_of_range("Array index out of bounds");
        }
        return data_[index];
    }
    const T &operator[](size_t index) const{
        if (index >= size_){
            throw std::out_of_range("Array index out of bounds");
        }
        return data_[index];
    }
    void push_back(const T &value){
        if (size_ >=capacity_){
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }
    void push_back(T &&value){
        if (size_ >= capacity_){
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }
    void remove(size_t index){
        if (index >= size_){
            throw std::out_of_range("Array index out of bounds");
        }
        for (size_t i = index; i < size_ - 1; ++i){
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    void clear(){
        size_ = 0;
    }
    size_t size() const {return size_;}
    size_t capacity() const {return capacity_;}
    bool empty() const {return size_ == 0;}
    T* begin() {return data_.get();}
    const T* begin() const{return data_.get();}
    T* end() {return data_.get() + size_;}
    const T* end() const{return data_.get() + size_;}
};

#endif