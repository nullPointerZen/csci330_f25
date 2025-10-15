#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <memory>

template <typename T>
class ResourceManager {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    static size_t total_allocated_bytes_;
    static size_t total_active_arrays_;

    void allocate_storage(size_t new_capacity) {
        if (new_capacity == 0) {
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        T* new_block = new T[new_capacity];
        data_ = new_block;
        capacity_ = new_capacity;
        total_allocated_bytes_ += sizeof(T) * new_capacity;
        total_active_arrays_ += 1;
    }

    void destroy_storage() noexcept {
        if (data_) {
            delete[] data_;
            data_ = nullptr;
            total_active_arrays_ -= 1;
        }
        capacity_ = 0;
        size_ = 0;
    }

public:
    ResourceManager() : data_(nullptr), size_(0), capacity_(0) {}
    explicit ResourceManager(size_t capacity) : data_(nullptr), size_(0), capacity_(0) { allocate_storage(capacity); }
    ResourceManager(std::initializer_list<T> init) : data_(nullptr), size_(0), capacity_(0) {
        allocate_storage(init.size());
        size_ = init.size();
        std::copy(init.begin(), init.end(), data_);
    }
    ResourceManager(const ResourceManager& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.capacity_ > 0) {
            allocate_storage(other.capacity_);
            size_ = other.size_;
            for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        }
    }
    ResourceManager(ResourceManager&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    ~ResourceManager() { destroy_storage(); }
    ResourceManager& operator=(ResourceManager other) { swap(other); return *this; }
    void swap(ResourceManager& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        ResourceManager temp(new_capacity);
        temp.size_ = size_;
        for (size_t i = 0; i < size_; ++i) temp.data_[i] = data_[i];
        swap(temp);
    }
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity_) reserve(std::max(new_size, capacity_ * 2 + 1));
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) data_[i] = value;
        }
        size_ = new_size;
    }
    void push_back(const T& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }
    void push_back(T&& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(value);
    }
    T& operator[](size_t idx) {
        if (idx >= size_) throw std::out_of_range("Index out of range");
        return data_[idx];
    }
    const T& operator[](size_t idx) const {
        if (idx >= size_) throw std::out_of_range("Index out of range");
        return data_[idx];
    }
    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }
    void clear() noexcept { size_ = 0; }
    static size_t total_allocated_bytes() noexcept { return total_allocated_bytes_; }
    static size_t total_active_arrays() noexcept { return total_active_arrays_; }
};

template <typename T>
size_t ResourceManager<T>::total_allocated_bytes_ = 0;

template <typename T>
size_t ResourceManager<T>::total_active_arrays_ = 0;

struct Student {
    int id{};
    std::string name;
    double gpa{};
    Student() = default;
    Student(int id_, std::string name_, double gpa_) : id(id_), name(std::move(name_)), gpa(gpa_) {}
};

class StudentDB {
private:
    ResourceManager<Student> store_;
    size_t count_{0};
    void ensure_capacity_for_one_more() {
        if (count_ == store_.capacity()) {
            size_t new_cap = store_.capacity() == 0 ? 4 : store_.capacity() * 2;
            store_.reserve(new_cap);
            std::cout << "[StudentDB] Capacity expanded to " << new_cap << "\n";
        }
    }
public:
    void add_student(const Student& s) {
        ensure_capacity_for_one_more();
        store_.resize(count_ + 1);
        store_[count_++] = s;
        std::cout << "[StudentDB] Added: #" << s.id << " " << s.name << " GPA=" << s.gpa << "\n";
    }
    bool remove_by_id(int id) {
        for (size_t i = 0; i < count_; ++i) {
            if (store_[i].id == id) {
                store_[i] = store_[count_ - 1];
                count_--;
                store_.resize(count_);
                std::cout << "[StudentDB] Removed student #" << id << "\n";
                return true;
            }
        }
        return false;
    }
    void report_memory() const {
        std::cout << "[StudentDB] Count=" << count_
                  << " Capacity=" << store_.capacity()
                  << " TotalAllocatedBytes=" << ResourceManager<Student>::total_allocated_bytes()
                  << " ActiveArrays=" << ResourceManager<Student>::total_active_arrays()
                  << "\n";
    }
    void list_all() const {
        for (size_t i = 0; i < count_; ++i) {
            std::cout << " - #" << store_[i].id << " " << store_[i].name << " GPA=" << store_[i].gpa << "\n";
        }
    }
};

int main() {
    StudentDB db;
    db.add_student(Student{1001, "Alice", 3.9});
    db.add_student(Student{1002, "Bob", 3.2});
    db.add_student(Student{1003, "Charlie", 3.6});
    db.report_memory();
    db.list_all();
    db.remove_by_id(1002);
    db.list_all();
    db.report_memory();
    return 0;
}
