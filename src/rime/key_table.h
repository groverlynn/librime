// encoding: utf-8
//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2011-04-17 GONG Chen <chen.sst@gmail.com>
//
#ifndef RIME_KEY_TABLE_H_
#define RIME_KEY_TABLE_H_

#include <X11/keysym.h>
#include <rime_api.h>

typedef enum {
  kShiftMask = 1U << 0,
  kLockMask = 1U << 1,
  kControlMask = 1U << 2,
  kMod1Mask = 1U << 3,
  kAltMask = kMod1Mask,
  kMod2Mask = 1U << 4,
  kMod3Mask = 1U << 5,
  kMod4Mask = 1U << 6,
  kMod5Mask = 1U << 7,
  kButton1Mask = 1U << 8,
  kButton2Mask = 1U << 9,
  kButton3Mask = 1U << 10,
  kButton4Mask = 1U << 11,
  kButton5Mask = 1U << 12,

  /* The next few modifiers are used by XKB, so we skip to the end.
   * Bits 15 - 23 are currently unused. Bit 29 is used internally.
   */

  /* ibus :) mask */
  kHandledMask = 1U << 24,
  kForwardMask = 1U << 25,
  kIgnoredMask = kForwardMask,

  kSuperMask = 1U << 26,
  kHyperMask = 1U << 27,
  kMetaMask = 1U << 28,

  kReleaseMask = 1U << 30,

  kModifierMask = 0x5f001fffU
} RimeModifier;

// 给定modifier文字，返回马赛克值
// 例如 RimeGetModifierByName("Alt") == (1 << 3)
// 如果不认得所给的键名，返回 0
RIME_API unsigned int RimeGetModifierByName(const char* name);

// 给一个数值，取得最低的非0位所对应的modifier文字
// 例如 RimeGetModifierName(12) == "Control"
// 取不到则返回 NULL
RIME_API const char* RimeGetModifierName(unsigned int modifier);

// 由键名取得键值
// 查无此键则返回 XK_VoidSymbol
RIME_API unsigned int RimeGetKeycodeByName(const char* name);

// 由键值取得键名
// 不认得此键，则返回 NULL
RIME_API const char* RimeGetKeyName(unsigned int keycode);

#endif  // RIME_KEY_TABLE_H_
