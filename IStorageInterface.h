#pragma once

#include <cstdint>
#include <cstddef>

// Storage Interface (unchanged)
class IStorageInterface {
public:
    virtual bool write(size_t idx, uint32_t entry) = 0;
    virtual bool read(size_t idx, uint32_t& entry) = 0;
    virtual ~IStorageInterface() {}
};


