#include "cpu.h"

namespace gb {

/* Perform opcode dispatching. */

void Cpu_::Execute(const u8 opcode) {
    switch (opcode) {
        case 0x00: Opcode_00(); break;
        case 0x01: Opcode_01(); break;
        case 0x02: Opcode_02(); break;
        case 0x03: Opcode_03(); break;
        case 0x04: Opcode_04(); break;
        case 0x05: Opcode_05(); break;
        case 0x06: Opcode_06(); break;
        case 0x07: Opcode_07(); break;
        case 0x08: Opcode_08(); break;
        case 0x09: Opcode_09(); break;
        case 0x0A: Opcode_0A(); break;
        case 0x0B: Opcode_0B(); break;
        case 0x0C: Opcode_0C(); break;
        case 0x0D: Opcode_0D(); break;
        case 0x0E: Opcode_0E(); break;
        case 0x0F: Opcode_0F(); break;
        case 0x10: Opcode_10(); break;
        case 0x11: Opcode_11(); break;
        case 0x12: Opcode_12(); break;
        case 0x13: Opcode_13(); break;
        case 0x14: Opcode_14(); break;
        case 0x15: Opcode_15(); break;
        case 0x16: Opcode_16(); break;
        case 0x17: Opcode_17(); break;
        case 0x18: Opcode_18(); break;
        case 0x19: Opcode_19(); break;
        case 0x1A: Opcode_1A(); break;
        case 0x1B: Opcode_1B(); break;
        case 0x1C: Opcode_1C(); break;
        case 0x1D: Opcode_1D(); break;
        case 0x1E: Opcode_1E(); break;
        case 0x1F: Opcode_1F(); break;
        case 0x20: Opcode_20(); break;
        case 0x21: Opcode_21(); break;
        case 0x22: Opcode_22(); break;
        case 0x23: Opcode_23(); break;
        case 0x24: Opcode_24(); break;
        case 0x25: Opcode_25(); break;
        case 0x26: Opcode_26(); break;
        case 0x27: Opcode_27(); break;
        case 0x28: Opcode_28(); break;
        case 0x29: Opcode_29(); break;
        case 0x2A: Opcode_2A(); break;
        case 0x2B: Opcode_2B(); break;
        case 0x2C: Opcode_2C(); break;
        case 0x2D: Opcode_2D(); break;
        case 0x2E: Opcode_2E(); break;
        case 0x2F: Opcode_2F(); break;
        case 0x30: Opcode_30(); break;
        case 0x31: Opcode_31(); break;
        case 0x32: Opcode_32(); break;
        case 0x33: Opcode_33(); break;
        case 0x34: Opcode_34(); break;
        case 0x35: Opcode_35(); break;
        case 0x36: Opcode_36(); break;
        case 0x37: Opcode_37(); break;
        case 0x38: Opcode_38(); break;
        case 0x39: Opcode_39(); break;
        case 0x3A: Opcode_3A(); break;
        case 0x3B: Opcode_3B(); break;
        case 0x3C: Opcode_3C(); break;
        case 0x3D: Opcode_3D(); break;
        case 0x3E: Opcode_3E(); break;
        case 0x3F: Opcode_3F(); break;
        case 0x40: Opcode_40(); break;
        case 0x41: Opcode_41(); break;
        case 0x42: Opcode_42(); break;
        case 0x43: Opcode_43(); break;
        case 0x44: Opcode_44(); break;
        case 0x45: Opcode_45(); break;
        case 0x46: Opcode_46(); break;
        case 0x47: Opcode_47(); break;
        case 0x48: Opcode_48(); break;
        case 0x49: Opcode_49(); break;
        case 0x4A: Opcode_4A(); break;
        case 0x4B: Opcode_4B(); break;
        case 0x4C: Opcode_4C(); break;
        case 0x4D: Opcode_4D(); break;
        case 0x4E: Opcode_4E(); break;
        case 0x4F: Opcode_4F(); break;
        case 0x50: Opcode_50(); break;
        case 0x51: Opcode_51(); break;
        case 0x52: Opcode_52(); break;
        case 0x53: Opcode_53(); break;
        case 0x54: Opcode_54(); break;
        case 0x55: Opcode_55(); break;
        case 0x56: Opcode_56(); break;
        case 0x57: Opcode_57(); break;
        case 0x58: Opcode_58(); break;
        case 0x59: Opcode_59(); break;
        case 0x5A: Opcode_5A(); break;
        case 0x5B: Opcode_5B(); break;
        case 0x5C: Opcode_5C(); break;
        case 0x5D: Opcode_5D(); break;
        case 0x5E: Opcode_5E(); break;
        case 0x5F: Opcode_5F(); break;
        case 0x60: Opcode_60(); break;
        case 0x61: Opcode_61(); break;
        case 0x62: Opcode_62(); break;
        case 0x63: Opcode_63(); break;
        case 0x64: Opcode_64(); break;
        case 0x65: Opcode_65(); break;
        case 0x66: Opcode_66(); break;
        case 0x67: Opcode_67(); break;
        case 0x68: Opcode_68(); break;
        case 0x69: Opcode_69(); break;
        case 0x6A: Opcode_6A(); break;
        case 0x6B: Opcode_6B(); break;
        case 0x6C: Opcode_6C(); break;
        case 0x6D: Opcode_6D(); break;
        case 0x6E: Opcode_6E(); break;
        case 0x6F: Opcode_6F(); break;
        case 0x70: Opcode_70(); break;
        case 0x71: Opcode_71(); break;
        case 0x72: Opcode_72(); break;
        case 0x73: Opcode_73(); break;
        case 0x74: Opcode_74(); break;
        case 0x75: Opcode_75(); break;
        case 0x76: Opcode_76(); break;
        case 0x77: Opcode_77(); break;
        case 0x78: Opcode_78(); break;
        case 0x79: Opcode_79(); break;
        case 0x7A: Opcode_7A(); break;
        case 0x7B: Opcode_7B(); break;
        case 0x7C: Opcode_7C(); break;
        case 0x7D: Opcode_7D(); break;
        case 0x7E: Opcode_7E(); break;
        case 0x7F: Opcode_7F(); break;
        case 0x80: Opcode_80(); break;
        case 0x81: Opcode_81(); break;
        case 0x82: Opcode_82(); break;
        case 0x83: Opcode_83(); break;
        case 0x84: Opcode_84(); break;
        case 0x85: Opcode_85(); break;
        case 0x86: Opcode_86(); break;
        case 0x87: Opcode_87(); break;
        case 0x88: Opcode_88(); break;
        case 0x89: Opcode_89(); break;
        case 0x8A: Opcode_8A(); break;
        case 0x8B: Opcode_8B(); break;
        case 0x8C: Opcode_8C(); break;
        case 0x8D: Opcode_8D(); break;
        case 0x8E: Opcode_8E(); break;
        case 0x8F: Opcode_8F(); break;
        case 0x90: Opcode_90(); break;
        case 0x91: Opcode_91(); break;
        case 0x92: Opcode_92(); break;
        case 0x93: Opcode_93(); break;
        case 0x94: Opcode_94(); break;
        case 0x95: Opcode_95(); break;
        case 0x96: Opcode_96(); break;
        case 0x97: Opcode_97(); break;
        case 0x98: Opcode_98(); break;
        case 0x99: Opcode_99(); break;
        case 0x9A: Opcode_9A(); break;
        case 0x9B: Opcode_9B(); break;
        case 0x9C: Opcode_9C(); break;
        case 0x9D: Opcode_9D(); break;
        case 0x9E: Opcode_9E(); break;
        case 0x9F: Opcode_9F(); break;
        case 0xA0: Opcode_A0(); break;
        case 0xA1: Opcode_A1(); break;
        case 0xA2: Opcode_A2(); break;
        case 0xA3: Opcode_A3(); break;
        case 0xA4: Opcode_A4(); break;
        case 0xA5: Opcode_A5(); break;
        case 0xA6: Opcode_A6(); break;
        case 0xA7: Opcode_A7(); break;
        case 0xA8: Opcode_A8(); break;
        case 0xA9: Opcode_A9(); break;
        case 0xAA: Opcode_AA(); break;
        case 0xAB: Opcode_AB(); break;
        case 0xAC: Opcode_AC(); break;
        case 0xAD: Opcode_AD(); break;
        case 0xAE: Opcode_AE(); break;
        case 0xAF: Opcode_AF(); break;
        case 0xB0: Opcode_B0(); break;
        case 0xB1: Opcode_B1(); break;
        case 0xB2: Opcode_B2(); break;
        case 0xB3: Opcode_B3(); break;
        case 0xB4: Opcode_B4(); break;
        case 0xB5: Opcode_B5(); break;
        case 0xB6: Opcode_B6(); break;
        case 0xB7: Opcode_B7(); break;
        case 0xB8: Opcode_B8(); break;
        case 0xB9: Opcode_B9(); break;
        case 0xBA: Opcode_BA(); break;
        case 0xBB: Opcode_BB(); break;
        case 0xBC: Opcode_BC(); break;
        case 0xBD: Opcode_BD(); break;
        case 0xBE: Opcode_BE(); break;
        case 0xBF: Opcode_BF(); break;
        case 0xC0: Opcode_C0(); break;
        case 0xC1: Opcode_C1(); break;
        case 0xC2: Opcode_C2(); break;
        case 0xC3: Opcode_C3(); break;
        case 0xC4: Opcode_C4(); break;
        case 0xC5: Opcode_C5(); break;
        case 0xC6: Opcode_C6(); break;
        case 0xC7: Opcode_C7(); break;
        case 0xC8: Opcode_C8(); break;
        case 0xC9: Opcode_C9(); break;
        case 0xCA: Opcode_CA(); break;
        case 0xCB: Opcode_CB(); break;
        case 0xCC: Opcode_CC(); break;
        case 0xCD: Opcode_CD(); break;
        case 0xCE: Opcode_CE(); break;
        case 0xCF: Opcode_CF(); break;
        case 0xD0: Opcode_D0(); break;
        case 0xD1: Opcode_D1(); break;
        case 0xD2: Opcode_D2(); break;
        case 0xD3: Opcode_D3(); break;
        case 0xD4: Opcode_D4(); break;
        case 0xD5: Opcode_D5(); break;
        case 0xD6: Opcode_D6(); break;
        case 0xD7: Opcode_D7(); break;
        case 0xD8: Opcode_D8(); break;
        case 0xD9: Opcode_D9(); break;
        case 0xDA: Opcode_DA(); break;
        case 0xDB: Opcode_DB(); break;
        case 0xDC: Opcode_DC(); break;
        case 0xDD: Opcode_DD(); break;
        case 0xDE: Opcode_DE(); break;
        case 0xDF: Opcode_DF(); break;
        case 0xE0: Opcode_E0(); break;
        case 0xE1: Opcode_E1(); break;
        case 0xE2: Opcode_E2(); break;
        case 0xE3: Opcode_E3(); break;
        case 0xE4: Opcode_E4(); break;
        case 0xE5: Opcode_E5(); break;
        case 0xE6: Opcode_E6(); break;
        case 0xE7: Opcode_E7(); break;
        case 0xE8: Opcode_E8(); break;
        case 0xE9: Opcode_E9(); break;
        case 0xEA: Opcode_EA(); break;
        case 0xEB: Opcode_EB(); break;
        case 0xEC: Opcode_EC(); break;
        case 0xED: Opcode_ED(); break;
        case 0xEE: Opcode_EE(); break;
        case 0xEF: Opcode_EF(); break;
        case 0xF0: Opcode_F0(); break;
        case 0xF1: Opcode_F1(); break;
        case 0xF2: Opcode_F2(); break;
        case 0xF3: Opcode_F3(); break;
        case 0xF4: Opcode_F4(); break;
        case 0xF5: Opcode_F5(); break;
        case 0xF6: Opcode_F6(); break;
        case 0xF7: Opcode_F7(); break;
        case 0xF8: Opcode_F8(); break;
        case 0xF9: Opcode_F9(); break;
        case 0xFA: Opcode_FA(); break;
        case 0xFB: Opcode_FB(); break;
        case 0xFC: Opcode_FC(); break;
        case 0xFD: Opcode_FD(); break;
        case 0xFE: Opcode_FE(); break;
        case 0xFF: Opcode_FF(); break;
        default: return;
    }
}

void Cpu_::ExecuteEx(const u8 opcode) {
    switch (opcode) {
        case 0x00: Opcode_CB_00(); break;
        case 0x01: Opcode_CB_01(); break;
        case 0x02: Opcode_CB_02(); break;
        case 0x03: Opcode_CB_03(); break;
        case 0x04: Opcode_CB_04(); break;
        case 0x05: Opcode_CB_05(); break;
        case 0x06: Opcode_CB_06(); break;
        case 0x07: Opcode_CB_07(); break;
        case 0x08: Opcode_CB_08(); break;
        case 0x09: Opcode_CB_09(); break;
        case 0x0A: Opcode_CB_0A(); break;
        case 0x0B: Opcode_CB_0B(); break;
        case 0x0C: Opcode_CB_0C(); break;
        case 0x0D: Opcode_CB_0D(); break;
        case 0x0E: Opcode_CB_0E(); break;
        case 0x0F: Opcode_CB_0F(); break;
        case 0x10: Opcode_CB_10(); break;
        case 0x11: Opcode_CB_11(); break;
        case 0x12: Opcode_CB_12(); break;
        case 0x13: Opcode_CB_13(); break;
        case 0x14: Opcode_CB_14(); break;
        case 0x15: Opcode_CB_15(); break;
        case 0x16: Opcode_CB_16(); break;
        case 0x17: Opcode_CB_17(); break;
        case 0x18: Opcode_CB_18(); break;
        case 0x19: Opcode_CB_19(); break;
        case 0x1A: Opcode_CB_1A(); break;
        case 0x1B: Opcode_CB_1B(); break;
        case 0x1C: Opcode_CB_1C(); break;
        case 0x1D: Opcode_CB_1D(); break;
        case 0x1E: Opcode_CB_1E(); break;
        case 0x1F: Opcode_CB_1F(); break;
        case 0x20: Opcode_CB_20(); break;
        case 0x21: Opcode_CB_21(); break;
        case 0x22: Opcode_CB_22(); break;
        case 0x23: Opcode_CB_23(); break;
        case 0x24: Opcode_CB_24(); break;
        case 0x25: Opcode_CB_25(); break;
        case 0x26: Opcode_CB_26(); break;
        case 0x27: Opcode_CB_27(); break;
        case 0x28: Opcode_CB_28(); break;
        case 0x29: Opcode_CB_29(); break;
        case 0x2A: Opcode_CB_2A(); break;
        case 0x2B: Opcode_CB_2B(); break;
        case 0x2C: Opcode_CB_2C(); break;
        case 0x2D: Opcode_CB_2D(); break;
        case 0x2E: Opcode_CB_2E(); break;
        case 0x2F: Opcode_CB_2F(); break;
        case 0x30: Opcode_CB_30(); break;
        case 0x31: Opcode_CB_31(); break;
        case 0x32: Opcode_CB_32(); break;
        case 0x33: Opcode_CB_33(); break;
        case 0x34: Opcode_CB_34(); break;
        case 0x35: Opcode_CB_35(); break;
        case 0x36: Opcode_CB_36(); break;
        case 0x37: Opcode_CB_37(); break;
        case 0x38: Opcode_CB_38(); break;
        case 0x39: Opcode_CB_39(); break;
        case 0x3A: Opcode_CB_3A(); break;
        case 0x3B: Opcode_CB_3B(); break;
        case 0x3C: Opcode_CB_3C(); break;
        case 0x3D: Opcode_CB_3D(); break;
        case 0x3E: Opcode_CB_3E(); break;
        case 0x3F: Opcode_CB_3F(); break;
        case 0x40: Opcode_CB_40(); break;
        case 0x41: Opcode_CB_41(); break;
        case 0x42: Opcode_CB_42(); break;
        case 0x43: Opcode_CB_43(); break;
        case 0x44: Opcode_CB_44(); break;
        case 0x45: Opcode_CB_45(); break;
        case 0x46: Opcode_CB_46(); break;
        case 0x47: Opcode_CB_47(); break;
        case 0x48: Opcode_CB_48(); break;
        case 0x49: Opcode_CB_49(); break;
        case 0x4A: Opcode_CB_4A(); break;
        case 0x4B: Opcode_CB_4B(); break;
        case 0x4C: Opcode_CB_4C(); break;
        case 0x4D: Opcode_CB_4D(); break;
        case 0x4E: Opcode_CB_4E(); break;
        case 0x4F: Opcode_CB_4F(); break;
        case 0x50: Opcode_CB_50(); break;
        case 0x51: Opcode_CB_51(); break;
        case 0x52: Opcode_CB_52(); break;
        case 0x53: Opcode_CB_53(); break;
        case 0x54: Opcode_CB_54(); break;
        case 0x55: Opcode_CB_55(); break;
        case 0x56: Opcode_CB_56(); break;
        case 0x57: Opcode_CB_57(); break;
        case 0x58: Opcode_CB_58(); break;
        case 0x59: Opcode_CB_59(); break;
        case 0x5A: Opcode_CB_5A(); break;
        case 0x5B: Opcode_CB_5B(); break;
        case 0x5C: Opcode_CB_5C(); break;
        case 0x5D: Opcode_CB_5D(); break;
        case 0x5E: Opcode_CB_5E(); break;
        case 0x5F: Opcode_CB_5F(); break;
        case 0x60: Opcode_CB_60(); break;
        case 0x61: Opcode_CB_61(); break;
        case 0x62: Opcode_CB_62(); break;
        case 0x63: Opcode_CB_63(); break;
        case 0x64: Opcode_CB_64(); break;
        case 0x65: Opcode_CB_65(); break;
        case 0x66: Opcode_CB_66(); break;
        case 0x67: Opcode_CB_67(); break;
        case 0x68: Opcode_CB_68(); break;
        case 0x69: Opcode_CB_69(); break;
        case 0x6A: Opcode_CB_6A(); break;
        case 0x6B: Opcode_CB_6B(); break;
        case 0x6C: Opcode_CB_6C(); break;
        case 0x6D: Opcode_CB_6D(); break;
        case 0x6E: Opcode_CB_6E(); break;
        case 0x6F: Opcode_CB_6F(); break;
        case 0x70: Opcode_CB_70(); break;
        case 0x71: Opcode_CB_71(); break;
        case 0x72: Opcode_CB_72(); break;
        case 0x73: Opcode_CB_73(); break;
        case 0x74: Opcode_CB_74(); break;
        case 0x75: Opcode_CB_75(); break;
        case 0x76: Opcode_CB_76(); break;
        case 0x77: Opcode_CB_77(); break;
        case 0x78: Opcode_CB_78(); break;
        case 0x79: Opcode_CB_79(); break;
        case 0x7A: Opcode_CB_7A(); break;
        case 0x7B: Opcode_CB_7B(); break;
        case 0x7C: Opcode_CB_7C(); break;
        case 0x7D: Opcode_CB_7D(); break;
        case 0x7E: Opcode_CB_7E(); break;
        case 0x7F: Opcode_CB_7F(); break;
        case 0x80: Opcode_CB_80(); break;
        case 0x81: Opcode_CB_81(); break;
        case 0x82: Opcode_CB_82(); break;
        case 0x83: Opcode_CB_83(); break;
        case 0x84: Opcode_CB_84(); break;
        case 0x85: Opcode_CB_85(); break;
        case 0x86: Opcode_CB_86(); break;
        case 0x87: Opcode_CB_87(); break;
        case 0x88: Opcode_CB_88(); break;
        case 0x89: Opcode_CB_89(); break;
        case 0x8A: Opcode_CB_8A(); break;
        case 0x8B: Opcode_CB_8B(); break;
        case 0x8C: Opcode_CB_8C(); break;
        case 0x8D: Opcode_CB_8D(); break;
        case 0x8E: Opcode_CB_8E(); break;
        case 0x8F: Opcode_CB_8F(); break;
        case 0x90: Opcode_CB_90(); break;
        case 0x91: Opcode_CB_91(); break;
        case 0x92: Opcode_CB_92(); break;
        case 0x93: Opcode_CB_93(); break;
        case 0x94: Opcode_CB_94(); break;
        case 0x95: Opcode_CB_95(); break;
        case 0x96: Opcode_CB_96(); break;
        case 0x97: Opcode_CB_97(); break;
        case 0x98: Opcode_CB_98(); break;
        case 0x99: Opcode_CB_99(); break;
        case 0x9A: Opcode_CB_9A(); break;
        case 0x9B: Opcode_CB_9B(); break;
        case 0x9C: Opcode_CB_9C(); break;
        case 0x9D: Opcode_CB_9D(); break;
        case 0x9E: Opcode_CB_9E(); break;
        case 0x9F: Opcode_CB_9F(); break;
        case 0xA0: Opcode_CB_A0(); break;
        case 0xA1: Opcode_CB_A1(); break;
        case 0xA2: Opcode_CB_A2(); break;
        case 0xA3: Opcode_CB_A3(); break;
        case 0xA4: Opcode_CB_A4(); break;
        case 0xA5: Opcode_CB_A5(); break;
        case 0xA6: Opcode_CB_A6(); break;
        case 0xA7: Opcode_CB_A7(); break;
        case 0xA8: Opcode_CB_A8(); break;
        case 0xA9: Opcode_CB_A9(); break;
        case 0xAA: Opcode_CB_AA(); break;
        case 0xAB: Opcode_CB_AB(); break;
        case 0xAC: Opcode_CB_AC(); break;
        case 0xAD: Opcode_CB_AD(); break;
        case 0xAE: Opcode_CB_AE(); break;
        case 0xAF: Opcode_CB_AF(); break;
        case 0xB0: Opcode_CB_B0(); break;
        case 0xB1: Opcode_CB_B1(); break;
        case 0xB2: Opcode_CB_B2(); break;
        case 0xB3: Opcode_CB_B3(); break;
        case 0xB4: Opcode_CB_B4(); break;
        case 0xB5: Opcode_CB_B5(); break;
        case 0xB6: Opcode_CB_B6(); break;
        case 0xB7: Opcode_CB_B7(); break;
        case 0xB8: Opcode_CB_B8(); break;
        case 0xB9: Opcode_CB_B9(); break;
        case 0xBA: Opcode_CB_BA(); break;
        case 0xBB: Opcode_CB_BB(); break;
        case 0xBC: Opcode_CB_BC(); break;
        case 0xBD: Opcode_CB_BD(); break;
        case 0xBE: Opcode_CB_BE(); break;
        case 0xBF: Opcode_CB_BF(); break;
        case 0xC0: Opcode_CB_C0(); break;
        case 0xC1: Opcode_CB_C1(); break;
        case 0xC2: Opcode_CB_C2(); break;
        case 0xC3: Opcode_CB_C3(); break;
        case 0xC4: Opcode_CB_C4(); break;
        case 0xC5: Opcode_CB_C5(); break;
        case 0xC6: Opcode_CB_C6(); break;
        case 0xC7: Opcode_CB_C7(); break;
        case 0xC8: Opcode_CB_C8(); break;
        case 0xC9: Opcode_CB_C9(); break;
        case 0xCA: Opcode_CB_CA(); break;
        case 0xCB: Opcode_CB_CB(); break;
        case 0xCC: Opcode_CB_CC(); break;
        case 0xCD: Opcode_CB_CD(); break;
        case 0xCE: Opcode_CB_CE(); break;
        case 0xCF: Opcode_CB_CF(); break;
        case 0xD0: Opcode_CB_D0(); break;
        case 0xD1: Opcode_CB_D1(); break;
        case 0xD2: Opcode_CB_D2(); break;
        case 0xD3: Opcode_CB_D3(); break;
        case 0xD4: Opcode_CB_D4(); break;
        case 0xD5: Opcode_CB_D5(); break;
        case 0xD6: Opcode_CB_D6(); break;
        case 0xD7: Opcode_CB_D7(); break;
        case 0xD8: Opcode_CB_D8(); break;
        case 0xD9: Opcode_CB_D9(); break;
        case 0xDA: Opcode_CB_DA(); break;
        case 0xDB: Opcode_CB_DB(); break;
        case 0xDC: Opcode_CB_DC(); break;
        case 0xDD: Opcode_CB_DD(); break;
        case 0xDE: Opcode_CB_DE(); break;
        case 0xDF: Opcode_CB_DF(); break;
        case 0xE0: Opcode_CB_E0(); break;
        case 0xE1: Opcode_CB_E1(); break;
        case 0xE2: Opcode_CB_E2(); break;
        case 0xE3: Opcode_CB_E3(); break;
        case 0xE4: Opcode_CB_E4(); break;
        case 0xE5: Opcode_CB_E5(); break;
        case 0xE6: Opcode_CB_E6(); break;
        case 0xE7: Opcode_CB_E7(); break;
        case 0xE8: Opcode_CB_E8(); break;
        case 0xE9: Opcode_CB_E9(); break;
        case 0xEA: Opcode_CB_EA(); break;
        case 0xEB: Opcode_CB_EB(); break;
        case 0xEC: Opcode_CB_EC(); break;
        case 0xED: Opcode_CB_ED(); break;
        case 0xEE: Opcode_CB_EE(); break;
        case 0xEF: Opcode_CB_EF(); break;
        case 0xF0: Opcode_CB_F0(); break;
        case 0xF1: Opcode_CB_F1(); break;
        case 0xF2: Opcode_CB_F2(); break;
        case 0xF3: Opcode_CB_F3(); break;
        case 0xF4: Opcode_CB_F4(); break;
        case 0xF5: Opcode_CB_F5(); break;
        case 0xF6: Opcode_CB_F6(); break;
        case 0xF7: Opcode_CB_F7(); break;
        case 0xF8: Opcode_CB_F8(); break;
        case 0xF9: Opcode_CB_F9(); break;
        case 0xFA: Opcode_CB_FA(); break;
        case 0xFB: Opcode_CB_FB(); break;
        case 0xFC: Opcode_CB_FC(); break;
        case 0xFD: Opcode_CB_FD(); break;
        case 0xFE: Opcode_CB_FE(); break;
        case 0xFF: Opcode_CB_FF(); break;
        default: return;
    }
}

}
