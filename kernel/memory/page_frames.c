#include "asterion.h"

void page_allocator_init(page_allocator_t *allocator, uint64_t bytes) {
    if (!allocator) return;
    allocator->total_pages = bytes / ASTERION_PAGE_SIZE;
    allocator->used_pages = 0;
    allocator->high_watermark = 0;
}

ast_status_t page_alloc(page_allocator_t *allocator, uint64_t count) {
    if (!allocator || count == 0 || allocator->used_pages + count > allocator->total_pages) return AST_ERR_INVALID;
    allocator->used_pages += count;
    if (allocator->used_pages > allocator->high_watermark) allocator->high_watermark = allocator->used_pages;
    return AST_OK;
}

ast_status_t page_free(page_allocator_t *allocator, uint64_t count) {
    if (!allocator || count == 0 || count > allocator->used_pages) return AST_ERR_INVALID;
    allocator->used_pages -= count;
    return AST_OK;
}
