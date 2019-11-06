#include "sha256.h"

void Pad(vector<uint8_t>& msg)
{
    uint64_t l          = (uint64_t)msg.size() * 8;
    uint64_t k          = 512 - ((l + 65LL) % 512);

    if (k > 8)
    {
        msg.push_back(0x80);

        for (uint64_t i = 0; i < k - 1; i++)
            msg.push_back(0);

        msg.push_back(l);
    }
    else
    {
        msg.push_back(0x80000000 | l);
    }
        
    assert((msg.size() * 8) % 512 == 0);
}

void TestPad()
{
    vector<uint8_t> msg = { 'a', 'b', 'c' };

    printf("Orig message:\n");
    for (uint32_t i = 0; i < msg.size(); i++)
    {
        printf("0x%lx ", msg[i]);
    }

    Pad(msg);

    printf("Padded message:\n");
    for (uint32_t i = 0; i < msg.size(); i++)
    {
        printf("0x%lx ", msg[i]);
    }

    __debugbreak();
}

void TestSHA256()
{
    TestPad();
}