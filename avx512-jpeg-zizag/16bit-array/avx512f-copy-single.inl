        
        // row 0
        __m512i row0 = _mm512_setzero_si512();
        const __m512i A0_00_shuf = _mm512_setr_epi32(0, 4, -1, -1, -1, -1, 9, 2, 6, 13, -1, -1, -1, -1, -1, -1);
        const __m512i A0_00_perm = _mm512_permutexvar_epi32(A0_00_shuf, A);
        const __m512i A0_00_mask = _mm512_setr_epi32(0x0000ffff, 0x0000ffff, 0, 0, 0, 0, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0, 0, 0, 0, 0, 0);
        row0 = _mm512_ternarylogic_epi32(row0, A0_00_perm, A0_00_mask, 0xf8);
        const __m512i A0_10_shuf = _mm512_setr_epi32(-1, -1, 4, 1, 8, -1, -1, -1, -1, -1, -1, -1, 13, 6, 3, 10);
        const __m512i A0_10_perm = _mm512_permutexvar_epi32(A0_10_shuf, A);
        const __m512i A0_10_mask = _mm512_setr_epi32(0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1);
        row0 = _mm512_ternarylogic_epi32(row0, _mm512_srli_epi32(A0_10_perm, 16), A0_10_mask, 0xf8);
        const __m512i A0_01_shuf = _mm512_setr_epi32(-1, 8, 1, 5, 12, -1, -1, -1, -1, -1, -1, -1, 10, 3, 7, 14);
        const __m512i A0_01_perm = _mm512_permutexvar_epi32(A0_01_shuf, A);
        const __m512i A0_01_mask = _mm512_setr_epi32(0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1);
        row0 = _mm512_ternarylogic_epi32(row0, _mm512_slli_epi32(A0_01_perm, 16), A0_01_mask, 0xf8);
        const __m512i A0_11_shuf = _mm512_setr_epi32(0, -1, -1, -1, -1, 12, 5, 2, 9, -1, -1, -1, -1, -1, -1, -1);
        const __m512i A0_11_perm = _mm512_permutexvar_epi32(A0_11_shuf, A);
        const __m512i A0_11_mask = _mm512_setr_epi32(0xffff0000, 0, 0, 0, 0, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0, 0, 0, 0, 0, 0, 0);
        row0 = _mm512_ternarylogic_epi32(row0, A0_11_perm, A0_11_mask, 0xf8);
        const __m512i B0_00_shuf = _mm512_setr_epi32(-1, -1, -1, -1, -1, 0, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1);
        const __m512i B0_00_perm = _mm512_permutexvar_epi32(B0_00_shuf, B);
        const __m512i B0_00_mask = _mm512_setr_epi32(0, 0, 0, 0, 0, 0x0000ffff, 0, 0, 0, 0, 0x0000ffff, 0, 0, 0, 0, 0);
        row0 = _mm512_ternarylogic_epi32(row0, B0_00_perm, B0_00_mask, 0xf8);
        // row0[22] := B[9]
        {
        const __m128i   src = _mm512_extracti32x4_epi32(B, 1);
        const __m128i   trg = _mm512_extracti32x4_epi32(row0, 2);
        const uint16_t word = _mm_extract_epi16(src, 1);
        const __m128i   mod = _mm_insert_epi16(trg, word, 6);
        row0 = _mm512_inserti32x4(row0, mod, 2);
        }
        const __m512i B0_01_shuf = _mm512_setr_epi32(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 1, -1, -1, -1, -1);
        const __m512i B0_01_perm = _mm512_permutexvar_epi32(B0_01_shuf, B);
        const __m512i B0_01_mask = _mm512_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0);
        row0 = _mm512_ternarylogic_epi32(row0, _mm512_slli_epi32(B0_01_perm, 16), B0_01_mask, 0xf8);
        // row0[19] := B[1]
        {
        const __m128i   src = _mm512_extracti32x4_epi32(B, 0);
        const __m128i   trg = _mm512_extracti32x4_epi32(row0, 2);
        const uint16_t word = _mm_extract_epi16(src, 1);
        const __m128i   mod = _mm_insert_epi16(trg, word, 3);
        row0 = _mm512_inserti32x4(row0, mod, 2);
        }
        
        // row 1
        __m512i row1 = _mm512_setzero_si512();
        // row1[12] := A[30]
        {
        const __m128i   src = _mm512_extracti32x4_epi32(A, 3);
        const __m128i   trg = _mm512_extracti32x4_epi32(row1, 1);
        const uint16_t word = _mm_extract_epi16(src, 6);
        const __m128i   mod = _mm_insert_epi16(trg, word, 4);
        row1 = _mm512_inserti32x4(row1, mod, 1);
        }
        const __m512i A1_10_shuf = _mm512_setr_epi32(-1, -1, -1, -1, 14, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        const __m512i A1_10_perm = _mm512_permutexvar_epi32(A1_10_shuf, A);
        const __m512i A1_10_mask = _mm512_setr_epi32(0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        row1 = _mm512_ternarylogic_epi32(row1, _mm512_srli_epi32(A1_10_perm, 16), A1_10_mask, 0xf8);
        // row1[9] := A[22]
        {
        const __m128i   src = _mm512_extracti32x4_epi32(A, 2);
        const __m128i   trg = _mm512_extracti32x4_epi32(row1, 1);
        const uint16_t word = _mm_extract_epi16(src, 6);
        const __m128i   mod = _mm_insert_epi16(trg, word, 1);
        row1 = _mm512_inserti32x4(row1, mod, 1);
        }
        const __m512i A1_11_shuf = _mm512_setr_epi32(-1, -1, -1, -1, -1, 11, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1);
        const __m512i A1_11_perm = _mm512_permutexvar_epi32(A1_11_shuf, A);
        const __m512i A1_11_mask = _mm512_setr_epi32(0, 0, 0, 0, 0, 0xffff0000, 0, 0, 0, 0, 0xffff0000, 0, 0, 0, 0, 0);
        row1 = _mm512_ternarylogic_epi32(row1, A1_11_perm, A1_11_mask, 0xf8);
        const __m512i B1_00_shuf = _mm512_setr_epi32(-1, -1, -1, -1, -1, -1, -1, 6, 13, 10, 3, -1, -1, -1, -1, 15);
        const __m512i B1_00_perm = _mm512_permutexvar_epi32(B1_00_shuf, B);
        const __m512i B1_00_mask = _mm512_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff, 0, 0, 0, 0, 0x0000ffff);
        row1 = _mm512_ternarylogic_epi32(row1, B1_00_perm, B1_00_mask, 0xf8);
        const __m512i B1_10_shuf = _mm512_setr_epi32(1, 8, 12, 5, -1, -1, -1, -1, -1, -1, -1, 3, 10, 14, 7, -1);
        const __m512i B1_10_perm = _mm512_permutexvar_epi32(B1_10_shuf, B);
        const __m512i B1_10_mask = _mm512_setr_epi32(-1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0);
        row1 = _mm512_ternarylogic_epi32(row1, _mm512_srli_epi32(B1_10_perm, 16), B1_10_mask, 0xf8);
        const __m512i B1_01_shuf = _mm512_setr_epi32(5, 12, 9, 2, -1, -1, -1, -1, -1, -1, -1, 7, 14, 11, -1, -1);
        const __m512i B1_01_perm = _mm512_permutexvar_epi32(B1_01_shuf, B);
        const __m512i B1_01_mask = _mm512_setr_epi32(-1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0);
        row1 = _mm512_ternarylogic_epi32(row1, _mm512_slli_epi32(B1_01_perm, 16), B1_01_mask, 0xf8);
        const __m512i B1_11_shuf = _mm512_setr_epi32(-1, -1, -1, -1, -1, -1, 2, 9, 13, 6, -1, -1, -1, -1, 11, 15);
        const __m512i B1_11_perm = _mm512_permutexvar_epi32(B1_11_shuf, B);
        const __m512i B1_11_mask = _mm512_setr_epi32(0, 0, 0, 0, 0, 0, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0, 0, 0, 0, 0xffff0000, 0xffff0000);
        row1 = _mm512_ternarylogic_epi32(row1, B1_11_perm, B1_11_mask, 0xf8);