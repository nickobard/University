#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <cmath>

#include <iostream>

using namespace std;
#endif /* __PROGTEST__ */

// 2^6 = 64B minimal size of the block (64 - 24 = 40 are minimum bytes for allocation)
constexpr int MIN_BLOCK_SIZE = 64;
constexpr int MAX_BLOCKS = sizeof(size_t) * 8;


struct Block {
    bool allocated = false;
    int size = 0;
    Block *next = nullptr;
    Block *previous = nullptr;

};

constexpr int HEADER_SIZE = sizeof(Block);

void *g_mem_pool = nullptr;
int g_mem_size = 0;
int g_allocated_blocks = 0;
Block *g_blocks[MAX_BLOCKS] = {};

void *shift(void *ptr, int offset) {
    uint8_t *shifted = reinterpret_cast<uint8_t *>(ptr) + offset;
    return shifted;
}

int get_block_index(int size) {
    if (size < MIN_BLOCK_SIZE)
        return log2(MIN_BLOCK_SIZE);
    return ceil(log2(size));
}

void add_block(void *block_ptr, int block_size) {
    int index = get_block_index(block_size);
    Block *block = reinterpret_cast<Block *>(block_ptr);
    block->allocated = false;
    block->size = block_size;
    block->previous = nullptr;
    block->next = g_blocks[index];
    if (g_blocks[index] != nullptr)
        g_blocks[index]->previous = block;
    g_blocks[index] = block;
}

void remove_block(Block *block) {
    if (block->next != nullptr)
        block->next->previous = block->previous;
    if (block->previous != nullptr)
        block->previous->next = block->next;
    else {
        auto index = get_block_index(block->size);
        g_blocks[index] = block->next;
    }
}

void *allocate_block(Block *block) {
    block->allocated = true;
    g_allocated_blocks++;
    return shift(block, sizeof(Block));
}

bool is_valid_pool() {
    return g_mem_pool != nullptr && g_mem_size > 0;
}

Block *divide_block(Block *to_divide, int supremum_size) {
    int half_size = to_divide->size >> 1;
    to_divide->size = half_size;
    Block *buddy = reinterpret_cast<Block *>(shift(to_divide, half_size));
    add_block(buddy, half_size);

    if (half_size == supremum_size) {
        return to_divide;
    } else {
        return divide_block(to_divide, supremum_size);
    }
}

void HeapInit(void *memPool, int memSize) {
    if (memPool == nullptr || memSize <= 0)
        return;
    g_mem_pool = memPool;
    g_mem_size = memSize;
    g_allocated_blocks = 0;
    for (auto &block: g_blocks)
        block = nullptr;

    int block_size = 1 << get_block_index(memSize);
    while (block_size >= MIN_BLOCK_SIZE) {
        if (block_size <= memSize) {
            add_block(memPool, block_size);
            memSize -= block_size;
            memPool = shift(memPool, block_size);
            block_size = 1 << get_block_index(memSize);
            continue;
        }
        block_size >>= 1;
    }
}

void *HeapAlloc(int size) {
    if (!is_valid_pool()
        || size <= 0
        || size > g_mem_size)
        return nullptr;
    int index = get_block_index(size + HEADER_SIZE);
    if (g_blocks[index] != nullptr) {
        Block *free_block = g_blocks[index];
        remove_block(free_block);
        return allocate_block(free_block);
    }
    const int supremum_size = 1 << index;
    while (index < MAX_BLOCKS) {
        if (g_blocks[index] == nullptr) {
            index++;
            continue;
        }
        int block_size = 1 << index;
        if (block_size > size) {
            auto to_divide = g_blocks[index];
            remove_block(to_divide);
            auto to_allocate = divide_block(to_divide, supremum_size);
            return allocate_block(to_allocate);
        }
    }
    return nullptr;
}

bool is_valid_pointer(void *block) {
    uint8_t *start = reinterpret_cast<uint8_t *>(g_mem_pool);
    uint8_t *block_position = reinterpret_cast<uint8_t *>(block) - HEADER_SIZE;
    auto delta = block_position - start;
    return delta % MIN_BLOCK_SIZE == 0;
}

Block *find_block(void *block) {
    void *block_to_find = shift(block, -HEADER_SIZE);
    Block *current_location = reinterpret_cast<Block *>(g_mem_pool);
    while (current_location <= block_to_find) {
        if (current_location == block_to_find)
            return current_location;
        current_location = reinterpret_cast<Block *>(shift(current_location, current_location->size));
    }
    return nullptr;
}

int get_delta(void *end_ptr, void *start_ptr = g_mem_pool) {
    uint8_t *start = reinterpret_cast<uint8_t *>(start_ptr);
    uint8_t *end = reinterpret_cast<uint8_t *>(end_ptr);
    return end - start;
}

Block *find_block_fast(void *block_to_find) {
    block_to_find = shift(block_to_find, -HEADER_SIZE);

    void *current_block_ptr = g_mem_pool;
    int remaining_size = g_mem_size;
    int current_block_size = 1 << get_block_index(remaining_size);

    while (true) {
        if (current_block_size < MIN_BLOCK_SIZE)
            return nullptr;
        if (current_block_size > remaining_size) {
            current_block_size >>= 1;
            continue;
        }

        void *next_block_ptr = shift(current_block_ptr, current_block_size);
        if (next_block_ptr > block_to_find) {
            break;
        } else {
            current_block_ptr = next_block_ptr;
            remaining_size -= current_block_size;
            current_block_size = 1 << get_block_index(remaining_size);
        }
    }

    while (current_block_ptr < block_to_find) {
        int delta = get_delta(block_to_find, current_block_ptr);
        int half = current_block_size >> 1;
        if (delta >= half) {
            if (reinterpret_cast<Block *>(current_block_ptr)->size == current_block_size) {
                return nullptr;
            } else {

                current_block_ptr = shift(current_block_ptr, half);
            }
        }
        current_block_size = half;
    }
    return reinterpret_cast<Block *>(current_block_ptr);
}


void merge_buddy(Block *block) {
    int delta = get_delta(block);
    int parent_size = block->size * 2;
    Block *buddy = nullptr;
    if (delta % parent_size == 0) {
        buddy = reinterpret_cast<Block *>(shift(block, block->size));
        if (buddy >= shift(g_mem_pool, g_mem_size))
            return;
        if (buddy->size != block->size
            || buddy->allocated)
            return;
        remove_block(buddy);
        remove_block(block);
        block->size = parent_size;
        add_block(block, parent_size);
        merge_buddy(block);
    } else {
        buddy = reinterpret_cast<Block *>(shift(block, -block->size));
        if (buddy->size != block->size
            || buddy->allocated)
            return;
        remove_block(buddy);
        remove_block(block);
        buddy->size = parent_size;
        add_block(buddy, parent_size);
        merge_buddy(buddy);
    }
}

bool HeapFree(void *blk) {
    if (!is_valid_pool()
        || blk == nullptr
        || blk < g_mem_pool
        || blk > shift(g_mem_pool, g_mem_size)
        || !is_valid_pointer(blk))
        return false;
    auto block = find_block_fast(blk);
    if (block == nullptr || !block->allocated)
        return false;
    block->allocated = false;
    g_allocated_blocks--;
    add_block(block, block->size);
    merge_buddy(block);
    return true;
}

void HeapDone(int *pendingBlk) {
    if (pendingBlk != nullptr)
        *pendingBlk = g_allocated_blocks;
}

#ifndef __PROGTEST__

int main(void) {
    assert(sizeof(Block) == 24);
    assert(get_block_index(0) == 6);
    assert(get_block_index(4) == 6);
    assert(get_block_index(16) == 6);
    assert(get_block_index(64) == 6);
    assert(get_block_index(63) == 6);
    assert(get_block_index(65) == 7);
    assert(get_block_index(127) == 7);
    assert(get_block_index(128) == 7);
    assert(get_block_index(129) == 8);

    int size = 1063;
    int index = get_block_index(size);
    assert(index == 11);
    int size_cap = 1 << index;
    assert(size_cap == 2048);
    assert((size_cap >>= 1) == 1024);
    assert((size_cap >>= 1) == 512);
    assert((size_cap >>= 1) == 256);
    assert((size_cap >>= 1) == 128);


    uint8_t *p0, *p1, *p2, *p3, *p4;
    int pendingBlk;
    static uint8_t memPool[3 * 1048576];

    HeapInit(memPool, 2097152);

    assert(is_valid_pointer(shift(g_mem_pool, 64 + sizeof(Block))));
    assert(is_valid_pointer(shift(g_mem_pool, 0 + sizeof(Block))));
    assert(!is_valid_pointer(shift(g_mem_pool, 63 + sizeof(Block))));
    assert ((p0 = (uint8_t *) HeapAlloc(512000)) != NULL);
    memset(p0, 0, 512000);
    assert ((p1 = (uint8_t *) HeapAlloc(511000)) != NULL);
    memset(p1, 0, 511000);
    assert ((p2 = (uint8_t *) HeapAlloc(26000)) != NULL);
    memset(p2, 0, 26000);
    HeapDone(&pendingBlk);
    assert (pendingBlk == 3);
    HeapInit(memPool, 2097152);
    assert ((p0 = (uint8_t *) HeapAlloc(1000000)) != NULL);
    memset(p0, 0, 1000000);
    assert ((p1 = (uint8_t *) HeapAlloc(250000)) != NULL);
    memset(p1, 0, 250000);
    assert ((p2 = (uint8_t *) HeapAlloc(250000)) != NULL);
    memset(p2, 0, 250000);
    assert ((p3 = (uint8_t *) HeapAlloc(250000)) != NULL);
    memset(p3, 0, 250000);
    assert ((p4 = (uint8_t *) HeapAlloc(50000)) != NULL);
    memset(p4, 0, 50000);


    assert (HeapFree(p2));

    assert (HeapFree(p4));

    assert (HeapFree(p3));

    assert (HeapFree(p1));

    assert ((p1 = (uint8_t *) HeapAlloc(500000)) != NULL);
    memset(p1, 0, 500000);
    assert (HeapFree(p0));
    assert (HeapFree(p1));
    HeapDone(&pendingBlk);
    assert (pendingBlk == 0);


    HeapInit(memPool, 2359296);
    assert ((p0 = (uint8_t *) HeapAlloc(1000000)) != NULL);
    memset(p0, 0, 1000000);
    assert ((p1 = (uint8_t *) HeapAlloc(500000)) != NULL);
    memset(p1, 0, 500000);
    assert ((p2 = (uint8_t *) HeapAlloc(500000)) != NULL);
    memset(p2, 0, 500000);
    assert ((p3 = (uint8_t *) HeapAlloc(500000)) == NULL);
    assert (HeapFree(p2));
    assert ((p2 = (uint8_t *) HeapAlloc(300000)) != NULL);
    memset(p2, 0, 300000);
    assert (HeapFree(p0));
    assert (HeapFree(p1));
    HeapDone(&pendingBlk);
    assert (pendingBlk == 1);


    HeapInit(memPool, 2359296);
    assert ((p0 = (uint8_t *) HeapAlloc(1000000)) != NULL);
    memset(p0, 0, 1000000);
    assert (!HeapFree(p0 + 1000));
    HeapDone(&pendingBlk);
    assert (pendingBlk == 1);
    /*

    */

    return 0;
}

#endif /* __PROGTEST__ */

