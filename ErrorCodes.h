#pragma once

#include <cstdint>
#include <cstddef>

enum class ErrorCode : uint16_t {
    ERR_NONE = 0x0000,
    ERR_TIMEOUT = 0x0001,
    ERR_OVERFLOW = 0x0002,
    ERR_HW_FAIL = 0x0003,
    ERR_FREQ_LOCK = 0x0004,
    ERR_UNKNOWN = 0xFFFF
};

struct ErrorEntry {
    ErrorCode code;
    uint16_t value;
};

static const ErrorEntry ErrorTable[] = {
    {ErrorCode::ERR_NONE,      0x0000},
    {ErrorCode::ERR_TIMEOUT,   0x1001},
    {ErrorCode::ERR_OVERFLOW,  0x2002},
    {ErrorCode::ERR_HW_FAIL,   0x3003},
    {ErrorCode::ERR_FREQ_LOCK, 0x4004},
};
