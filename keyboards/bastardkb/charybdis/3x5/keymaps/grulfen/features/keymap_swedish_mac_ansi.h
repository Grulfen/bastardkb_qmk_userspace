// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * This file is copied from quantum/keymap_extras/keymap_swedish_pro_mac_ansi.h
 *
 *
 *
 */

#pragma once
#include "keycodes.h"
// clang-format off

// Aliases
#define AP_LABK KC_GRV  // <
#define AP_1    KC_1    // 1
#define AP_2    KC_2    // 2
#define AP_3    KC_3    // 3
#define AP_4    KC_4    // 4
#define AP_5    KC_5    // 5
#define AP_6    KC_6    // 6
#define AP_7    KC_7    // 7
#define AP_8    KC_8    // 8
#define AP_9    KC_9    // 9
#define AP_0    KC_0    // 0
#define AP_PLUS KC_MINS // +
#define AP_ACUT KC_EQL  // ´ (dead)
#define AP_Q    KC_Q    // Q
#define AP_W    KC_W    // W
#define AP_E    KC_E    // E
#define AP_R    KC_R    // R
#define AP_T    KC_T    // T
#define AP_Y    KC_Y    // Y
#define AP_U    KC_U    // U
#define AP_I    KC_I    // I
#define AP_O    KC_O    // O
#define AP_P    KC_P    // P
#define AP_ARNG KC_LBRC // Å
#define AP_DIAE KC_RBRC // ¨ (dead)
#define AP_QUOT KC_NUHS // '
#define AP_A    KC_A    // A
#define AP_S    KC_S    // S
#define AP_D    KC_D    // D
#define AP_F    KC_F    // F
#define AP_G    KC_G    // G
#define AP_H    KC_H    // H
#define AP_J    KC_J    // J
#define AP_K    KC_K    // K
#define AP_L    KC_L    // L
#define AP_ODIA KC_SCLN // Ö
#define AP_ADIA KC_QUOT // Ä
#define AP_Z    KC_Z    // Z
#define AP_X    KC_X    // X
#define AP_C    KC_C    // C
#define AP_V    KC_V    // V
#define AP_B    KC_B    // B
#define AP_N    KC_N    // N
#define AP_M    KC_M    // M
#define AP_COMM KC_COMM // ,
#define AP_DOT  KC_DOT  // .
#define AP_MINS KC_SLSH // -
#define AP_RABK S(AP_LABK) // >
#define AP_EXLM S(AP_1)    // !
#define AP_DQUO S(AP_2)    // "
#define AP_HASH S(AP_3)    // #
#define AP_EURO S(AP_4)    // €
#define AP_PERC S(AP_5)    // %
#define AP_AMPR S(AP_6)    // &
#define AP_SLSH S(AP_7)    // /
#define AP_LPRN S(AP_8)    // (
#define AP_RPRN S(AP_9)    // )
#define AP_EQL  S(AP_0)    // =
#define AP_QUES S(AP_PLUS) // ?
#define AP_GRV  S(AP_ACUT) // `
#define AP_CIRC S(AP_DIAE) // ^ (dead)
#define AP_ASTR S(AP_QUOT) // *
#define AP_SCLN S(AP_COMM) // ;
#define AP_COLN S(AP_DOT)  // :
#define AP_UNDS S(AP_MINS) // _
#define AP_LTEQ A(AP_LABK) // ≤
#define AP_COPY A(AP_1)    // ©
#define AP_AT   A(AP_2)    // @
#define AP_PND  A(AP_3)    // £
#define AP_DLR  A(AP_4)    // $
#define AP_INFN A(AP_5)    // ∞
#define AP_SECT A(AP_6)    // §
#define AP_PIPE A(AP_7)    // |
#define AP_LBRC A(AP_8)    // [
#define AP_RBRC A(AP_9)    // ]
#define AP_AEQL A(AP_0)    // ≈
#define AP_PLMN A(AP_PLUS) // ±
#define AP_BULT A(AP_Q)    // •
#define AP_OMEG A(AP_W)    // Ω
#define AP_EACU A(AP_E)    // É
#define AP_REGD A(AP_R)    // ®
#define AP_DAGG A(AP_T)    // †
#define AP_MICR A(AP_Y)    // µ
#define AP_UDIA A(AP_U)    // Ü
#define AP_DLSI A(AP_I)    // ı
#define AP_OE   A(AP_O)    // Œ
#define AP_PI   A(AP_P)    // π
#define AP_DOTA A(AP_ARNG) // ˙
#define AP_TILD A(AP_DIAE) // ~ (dead)
#define AP_TM   A(AP_QUOT) // ™
#define AP_APPL A(AP_A)    //  (Apple logo)
#define AP_SS   A(AP_S)    // ß
#define AP_PDIF A(AP_D)    // ∂
#define AP_FHK  A(AP_F)    // ƒ
#define AP_CEDL A(AP_G)    // ¸
#define AP_OGON A(AP_H)    // ˛
#define AP_SQRT A(AP_J)    // √
#define AP_FORD A(AP_K)    // ª
#define AP_FI   A(AP_L)    // ﬁ
#define AP_OSTR A(AP_ODIA) // Ø
#define AP_AE   A(AP_ADIA) // Æ
#define AP_DIV  A(AP_Z)    // ÷
#define AP_CCED A(AP_C)    // Ç
#define AP_LSAQ A(AP_V)    // ‹
#define AP_RSAQ A(AP_B)    // ›
#define AP_LSQU A(AP_N)    // ‘
#define AP_RSQU A(AP_M)    // ’
#define AP_SLQU A(AP_COMM) // ‚
#define AP_ELLP A(AP_DOT)  // …
#define AP_NDSH A(AP_MINS) // –
#define AP_GTEQ S(A(AP_LABK)) // ≥
#define AP_IEXL S(A(AP_1))    // ¡
#define AP_YEN  S(A(AP_3))    // ¥
#define AP_CENT S(A(AP_4))    // ¢
#define AP_PERM S(A(AP_5))    // ‰
#define AP_PILC S(A(AP_6))    // ¶
#define AP_BSLS S(A(AP_7))    // (backslash)
#define AP_LCBR S(A(AP_8))    // {
#define AP_RCBR S(A(AP_9))    // }
#define AP_NEQL S(A(AP_0))    // ≠
#define AP_IQUE S(A(AP_PLUS)) // ¿
#define AP_DEG  S(A(AP_Q))    // °
#define AP_DACU S(A(AP_W))    // ˝
#define AP_DDAG S(A(AP_T))    // ‡
#define AP_STIL S(A(AP_Y))    // ˜
#define AP_DCIR S(A(AP_I))    // ˆ
#define AP_NARP S(A(AP_P))    // ∏
#define AP_RNGA S(A(AP_ARNG)) // ˚
#define AP_LOZN S(A(AP_A))    // ◊
#define AP_NARS S(A(AP_S))    // ∑
#define AP_INCR S(A(AP_D))    // ∆
#define AP_INTG S(A(AP_F))    // ∫
#define AP_MACR S(A(AP_G))    // ¯
#define AP_BREV S(A(AP_H))    // ˘
#define AP_NOT  S(A(AP_J))    // ¬
#define AP_MORD S(A(AP_K))    // º
#define AP_FL   S(A(AP_L))    // ﬂ
#define AP_FRSL S(A(AP_Z))    // ⁄
#define AP_CARN S(A(AP_X))    // ˇ
#define AP_LDAQ S(A(AP_V))    // «
#define AP_RDAQ S(A(AP_B))    // »
#define AP_LDQU S(A(AP_N))    // “
#define AP_RDQU S(A(AP_M))    // ”
#define AP_DLQU S(A(AP_COMM)) // „
#define AP_MDDT S(A(AP_DOT))  // ·
#define AP_MDSH S(A(AP_MINS)) // —

