
#include <cstdint>
#include <cstddef>
#include "IStorageInterface.h"
#include "ErrorCodes.h"

class CircularErrorBuffer {

public:
    CircularErrorBuffer(IStorageInterface& stor, size_t cap);
    bool logError(ErrorCode code);

private:
    // Now encapsulated lookup
    uint16_t lookupErrorValue(ErrorCode code) const;
    bool pop(uint32_t& entry);
    size_t size() const;
    size_t getHead() const { return head_; }
    size_t getTail() const { return tail_; }
    bool isFull() const { return full_; }
    bool isEmpty() const { return (head_ == tail_) && !full_; }

    IStorageInterface& storage_;
    size_t capacity_;
    size_t head_;
    size_t tail_;
    bool full_;
};
