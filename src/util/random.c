#include "ft_ssl.h"

int get_random_dev(void)
{
    int dev;

    dev = open("/dev/urandom", O_RDONLY);
    if (dev == -1)
    {
        error_msg("random device could not be opened");
        return -1;
    }
    return dev;
}

uint64_t read_random_bytes(const int random_dev)
{
    uint64_t bytes;

    if (read(random_dev, &bytes, sizeof(bytes)) == -1)
    {
        error_msg("could not read from random device");
        return 0;
    }
    return bytes;
}

uint64_t rand_ui64(const int random_dev)
{
    uint64_t rand_ui64;

    rand_ui64 = read_random_bytes(random_dev);
    return rand_ui64;
}

uint64_t rand_range_ui64(const int random_dev, const uint64_t min, const uint64_t max)
{
    return rand_ui64(random_dev) % (max - min) + min;
}
