#ifndef COLLECTIONOF_H
#define COLLECTIONOF_H

#include <cstddef>
#include <iterator>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <type_traits>


template <typename T, bool IsShared = true>
class CollectionOf {
public:
    using ClearT =
        std::remove_pointer_t<
            std::remove_reference_t<
                std::remove_cv_t<T>>>;

    template <typename U>
    using TypePtr = std::conditional_t<IsShared, std::shared_ptr<U>, U*>;

    template <typename U>
    using Collection = std::vector<U>;

    using size_type = size_t;

private:
    Collection<TypePtr<ClearT>> m_objects;

public:
    template <typename U, bool S>
    friend void swap(CollectionOf<U, S>&, CollectionOf<U, S>&);

public:
    CollectionOf() :
        m_objects {} {}

    CollectionOf(const CollectionOf& other) :
        m_objects { other.m_objects } {}

    CollectionOf(CollectionOf&& other) noexcept :
        m_objects { other.m_objects } {}

    CollectionOf& operator=(const CollectionOf& other) {
        if (this != &other) {
            Clear();
            m_objects = other.m_objects;
        }

        return *this;
    }

    CollectionOf& operator=(CollectionOf&& other) noexcept {
        if (this != &other) {
            Clear();
            m_objects = std::move(other.m_objects);
        }

        return *this;
    }

    ~CollectionOf() {
        Clear();
    }

public:
    TypePtr<ClearT> operator[](size_type idx) {
        return m_objects[idx];
    }

    const TypePtr<ClearT> operator[](size_type idx) const {
        return m_objects[idx];
    }

    TypePtr<ClearT> At(size_type idx) {
        return m_objects.at(idx);
    }

    const TypePtr<ClearT> At(size_type idx) const {
        return m_objects.at(idx);
    }

    size_type Size() const {
        return m_objects.size();
    }

    bool IsEmpty() const {
        return m_objects.empty();
    }

    TypePtr<ClearT> Front() {
        return m_objects.front();
    }

    const TypePtr<ClearT> Front() const {
        return m_objects.front();
    }

    TypePtr<ClearT> Back() {
        return m_objects.back();
    }

    const TypePtr<ClearT> Back() const {
        return m_objects.back();
    }

    void Add(TypePtr<ClearT> object) {
        m_objects.push_back(object);
    }

    void Delete(size_type idx) {
        if (idx >= Size()) return;

        if constexpr (IsShared) {
            m_objects.at(idx).reset();
        }

        m_objects.erase(std::next(m_objects.begin(), idx));
    }

    void Delete(TypePtr<ClearT> object) {
        auto newEnd = std::remove(m_objects.begin(), m_objects.end(), object);

        if constexpr (IsShared) {
            std::for_each(newEnd, m_objects.end(), [](TypePtr<ClearT> obj) {
                obj.reset();
            });
        }

        m_objects.erase(newEnd, m_objects.end());
    }

    void Clear() {
        if constexpr (IsShared) {
            for (TypePtr<ClearT>& object : m_objects) {
                object.reset();
            }
        }

        m_objects.clear();
    }

    Collection<TypePtr<ClearT>>& Get() {
        return m_objects;
    }

    const Collection<TypePtr<ClearT>>& Get() const {
        return m_objects;
    }

    decltype(auto) begin() noexcept {
        return m_objects.begin();
    }

    decltype(auto) begin() const noexcept {
        return m_objects.begin();
    }

    decltype(auto) end() noexcept {
        return m_objects.end();
    }

    decltype(auto) end() const noexcept {
        return m_objects.end();
    }

    decltype(auto) rbegin() noexcept {
        return m_objects.rbegin();
    }

    decltype(auto) rbegin() const noexcept {
        return m_objects.rbegin();
    }

    decltype(auto) rend() noexcept {
        return m_objects.rend();
    }

    decltype(auto) rend() const noexcept {
        return m_objects.rend();
    }

    decltype(auto) cbegin() const noexcept {
        return m_objects.cbegin();
    }

    decltype(auto) cend() const noexcept {
        return m_objects.cend();
    }

    decltype(auto) crbegin() const noexcept {
        return m_objects.crbegin();
    }

    decltype(auto) crend() const noexcept {
        return m_objects.crend();
    }
};

template <typename T>
using CollectionOfShared = CollectionOf<T, true>;

template <typename T>
using CollectionOfPtr = CollectionOf<T, false>;


template <typename U, bool S = true>
void swap(CollectionOf<U, S>& rhs, CollectionOf<U, S>& lhs) {
    if (&rhs == &lhs) return;

    using std::swap;

    swap(rhs.m_objects, lhs.m_objects);
}


#endif // COLLECTIONOF_H
