#include <inttypes.h>

#define BLOOM_SIZE 128
#define BFI_MAGIC 0x053e // 1342
#define BFI_HEADER 8
#define BFI_RECORDS_PER_PAGE 1000
#define BFI_PK_SIZE sizeof(uint32_t)
#define BFI_PAGE_SIZE (BFI_PK_SIZE + BLOOM_SIZE) * BFI_RECORDS_PER_PAGE

// a bunch of blooms in a file
typedef struct {
    uint16_t    magic_number;
    uint8_t     version;
    uint8_t     unused; // bring it to 8 byte header
    uint32_t    records;
    int         fp;
    char *      map;
    int32_t     current_page;
    int32_t     total_pages;
    uint32_t *  pks;
    char *      page;
} bfi;

void    bfi_generate(char * input[], int items, char ** ptr);
int     bfi_contains(char * haystack, char * needle, int len);

bfi*    bfi_open(char * filename);
void    bfi_close(bfi * index);
int     bfi_sync(bfi * index);

int     bfi_index(bfi * index, int pk, char * input[], int items);
int     bfi_lookup(bfi * index, char * input[], int items, uint32_t ** ptr);
