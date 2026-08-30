#include <stddef.h>

void *memset(void *destination, int value, size_t length) {
    unsigned char *bytes = destination;
    for (size_t i = 0; i < length; ++i) bytes[i] = (unsigned char)value;
    return destination;
}

void *memcpy(void *destination, const void *source, size_t length) {
    unsigned char *out = destination;
    const unsigned char *in = source;
    for (size_t i = 0; i < length; ++i) out[i] = in[i];
    return destination;
}

size_t strlen(const char *value) {
    size_t length = 0;
    while (value && value[length]) ++length;
    return length;
}

char *strncpy(char *destination, const char *source, size_t length) {
    size_t i = 0;
    for (; i < length && source[i]; ++i) destination[i] = source[i];
    for (; i < length; ++i) destination[i] = '\0';
    return destination;
}
