#pragma once

#include "IStorageInterface.h"
#include <cstdint>
#include <cstddef>

// Adapt these to your actual DDR3 configuration!
#define DDR3_STORAGE_BASE_ADDRESS 0x80000000  // Example start address!
#define DDR3_STORAGE_CAPACITY      1024       // Number of uint32_t entries

class DDR3RamStorage : public IStorageInterface {
public:
    // User must ensure the memory region is valid & safe!
    DDR3RamStorage(uintptr_t baseAddress, size_t capacity)
        : baseAddress_(baseAddress), capacity_(capacity) {
        volatile uint32_t* target = reinterpret_cast<volatile uint32_t*>(baseAddress_);
        for (size_t idx = 0; idx < capacity_; ++idx) {
            target[idx] = 0U;
        }
    }

    bool write(size_t idx, uint32_t entry) override {
        if (idx >= capacity_) return false;
        volatile uint32_t* target = reinterpret_cast<volatile uint32_t*>(baseAddress_);
        target[idx] = entry;
        return true;
    }

    bool read(size_t idx, uint32_t& entry) override {
        if (idx >= capacity_) return false;
        volatile uint32_t* target = reinterpret_cast<volatile uint32_t*>(baseAddress_);
        entry = target[idx];
        return true;
    }

private:
    uintptr_t baseAddress_;
    size_t capacity_;
};

