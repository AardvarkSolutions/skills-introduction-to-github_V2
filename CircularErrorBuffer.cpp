#include "CircularErrorBuffer.h"

#include <cstdint>
#include <cstddef>
#include "IStorageInterface.h"
#include "ErrorCodes.h"



CircularErrorBuffer::CircularErrorBuffer(IStorageInterface& stor, size_t cap) : storage_(stor), capacity_(cap), head_(0), tail_(0), full_(false)
{

}

bool CircularErrorBuffer::logError(ErrorCode code)
{
    uint16_t errVal = lookupErrorValue(code);
    uint32_t entry = static_cast<uint32_t>(errVal) & 0xFFFF;
    bool success{ true };

    if (capacity_ == 0)
    {
        success = false;
    }
    else if (!storage_.write(head_, entry))
    {
        success = false;
    }
    else
    {
        head_ = (head_ + 1) % capacity_;

        if (full_) 
        {
            tail_ = (tail_ + 1) % capacity_; // Overwrite oldest
        }

        if (head_ == tail_)
        {
            full_ = true;
        }

        success = true;
    }

    return success;
}

uint16_t CircularErrorBuffer::lookupErrorValue(ErrorCode code) const
{
    for (size_t i = 0; i < sizeof(ErrorTable) / sizeof(ErrorEntry); ++i) {
        if (ErrorTable[i].code == code)
            return ErrorTable[i].value;
    }
    return static_cast<uint16_t>(ErrorCode::ERR_UNKNOWN);
}

bool CircularErrorBuffer::pop(uint32_t& entry)
{
    if (capacity_ == 0) return false;
    if ((head_ == tail_) && !full_) return false; // empty
    if (!storage_.read(tail_, entry)) return false;

    tail_ = (tail_ + 1) % capacity_;
    full_ = false;
    return true;
}

size_t CircularErrorBuffer::size() const
{
    if (full_) return capacity_;
    if (head_ >= tail_) return head_ - tail_;
    return capacity_ - (tail_ - head_);
}
