/************************************************************************

	Trie speedup - trie_next: SSE implementation

	author: Wojciech Muła
	e-mail: wojciech_mula@poczta.onet.pl
	last update: 2013-09-30

	license: simplifed BSD

************************************************************************/

#define _POSIX_C_SOURCE 200112

#include "trie.h"
#include <string.h>
#include <stdlib.h>


#define SIMD_ALIGN 16
#define ALIGNED_SIZE(size) (SIMD_ALIGN*(((size) + SIMD_ALIGN - 1)/SIMD_ALIGN))

TrieNode* trie_next(TrieNode* node, const char letter) {
    const int n = node->n;

    int dummy;
    __asm__ __volatile__ (
        "movzbl %%al, %%eax                 \n"
        "imul   $0x01010101, %%eax, %%eax   \n"
        "movd   %%eax, %%xmm0               \n"
        "pshufd $0x00, %%xmm0, %%xmm0       \n"
        : "=a" (dummy)
        : "a" (letter)
    );

    size_t i, j;
    for (i = 0; i < n; i+=16) {
        __asm__ __volatile__ (
            "movdqa (%%eax), %%xmm1         \n"
            "pcmpeqb %%xmm0, %%xmm1         \n"
            "pmovmskb %%xmm1, %%eax         \n"
            "bsf %%eax, %%eax               \n"
            "setz %%ah                      \n"
            : "=a" (j)
            : "a"  (&(node->chars[i]))
        );
        if (j < 256) {
            return node->next[i+j];
        }
    }

    return NULL;
}

void trie_add_link(TrieNode* node, TrieNode* newnode, const char letter) {
	const size_t old_count = node->n;
	const size_t new_count = old_count + 1;

	if (ALIGNED_SIZE(new_count) > ALIGNED_SIZE(old_count)) {
		char* tmp;
		posix_memalign((void**)&tmp, SIMD_ALIGN, ALIGNED_SIZE(new_count));

		memset(tmp, 0, ALIGNED_SIZE(new_count));
		memcpy(tmp, node->chars, old_count);

		free(node->chars);
		node->chars = tmp;
	}

    node->n += 1;
    node->next = (TrieNode**)realloc(node->next, sizeof(TrieNode*) * node->n);

    node->chars[node->n - 1] = letter;
    node->next [node->n - 1] = newnode;
}

