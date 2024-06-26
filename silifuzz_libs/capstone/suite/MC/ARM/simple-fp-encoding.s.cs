# CS_ARCH_ARM, CS_MODE_ARM, None
0xa0,0x0b,0x71,0xee = vadd.f64 d16, d17, d16
0x80,0x0a,0x30,0xee = vadd.f32 s0, s1, s0
0xe0,0x0b,0x71,0xee = vsub.f64 d16, d17, d16
0xc0,0x0a,0x30,0xee = vsub.f32 s0, s1, s0
0xa0,0x0b,0xc1,0xee = vdiv.f64 d16, d17, d16
0x80,0x0a,0x80,0xee = vdiv.f32 s0, s1, s0
0xa3,0x2a,0xc2,0xee = vdiv.f32 s5, s5, s7
0x07,0x5b,0x85,0xee = vdiv.f64 d5, d5, d7
0xa0,0x0b,0x61,0xee = vmul.f64 d16, d17, d16
0xa1,0x4b,0x64,0xee = vmul.f64 d20, d20, d17
0x80,0x0a,0x20,0xee = vmul.f32 s0, s1, s0
0xaa,0x5a,0x65,0xee = vmul.f32 s11, s11, s21
0xe0,0x0b,0x61,0xee = vnmul.f64 d16, d17, d16
0xc0,0x0a,0x20,0xee = vnmul.f32 s0, s1, s0
0x60,0x1b,0xf4,0xee = vcmp.f64 d17, d16
0x40,0x0a,0xf4,0xee = vcmp.f32 s1, s0
0x40,0x1b,0xf5,0xee = vcmp.f64 d17, #0
0x40,0x0a,0xf5,0xee = vcmp.f32 s1, #0
0xe0,0x1b,0xf4,0xee = vcmpe.f64 d17, d16
0xc0,0x0a,0xf4,0xee = vcmpe.f32 s1, s0
0xc0,0x0b,0xf5,0xee = vcmpe.f64 d16, #0
0xc0,0x0a,0xb5,0xee = vcmpe.f32 s0, #0
0xe0,0x0b,0xf0,0xee = vabs.f64 d16, d16
0xc0,0x0a,0xb0,0xee = vabs.f32 s0, s0
0xe0,0x0b,0xb7,0xee = vcvt.f32.f64 s0, d16
0xc0,0x0a,0xf7,0xee = vcvt.f64.f32 d16, s0
0x60,0x0b,0xf1,0xee = vneg.f64 d16, d16
0x40,0x0a,0xb1,0xee = vneg.f32 s0, s0
0xe0,0x0b,0xf1,0xee = vsqrt.f64 d16, d16
0xc0,0x0a,0xb1,0xee = vsqrt.f32 s0, s0
0xc0,0x0b,0xf8,0xee = vcvt.f64.s32 d16, s0
0xc0,0x0a,0xb8,0xee = vcvt.f32.s32 s0, s0
0x40,0x0b,0xf8,0xee = vcvt.f64.u32 d16, s0
0x40,0x0a,0xb8,0xee = vcvt.f32.u32 s0, s0
0xe0,0x0b,0xbd,0xee = vcvt.s32.f64 s0, d16
0xc0,0x0a,0xbd,0xee = vcvt.s32.f32 s0, s0
0xe0,0x0b,0xbc,0xee = vcvt.u32.f64 s0, d16
0xc0,0x0a,0xbc,0xee = vcvt.u32.f32 s0, s0
0xa1,0x0b,0x42,0xee = vmla.f64 d16, d18, d17
0x00,0x0a,0x41,0xee = vmla.f32 s1, s2, s0
0xe1,0x0b,0x42,0xee = vmls.f64 d16, d18, d17
0x40,0x0a,0x41,0xee = vmls.f32 s1, s2, s0
0xe1,0x0b,0x52,0xee = vnmla.f64 d16, d18, d17
0x40,0x0a,0x51,0xee = vnmla.f32 s1, s2, s0
0xa1,0x0b,0x52,0xee = vnmls.f64 d16, d18, d17
0x00,0x0a,0x51,0xee = vnmls.f32 s1, s2, s0
0x10,0xfa,0xf1,0xee = vmrs APSR_nzcv, fpscr
0x10,0xfa,0xf1,0xee = vmrs APSR_nzcv, fpscr
0x10,0xfa,0xf1,0xee = vmrs APSR_nzcv, fpscr
0x10,0x2a,0xf0,0xee = vmrs r2, fpsid
0x10,0x3a,0xf0,0xee = vmrs r3, fpsid
0x10,0x4a,0xf7,0xee = vmrs r4, mvfr0
0x10,0x5a,0xf6,0xee = vmrs r5, mvfr1
0x60,0x0b,0xf1,0x1e = vnegne.f64 d16, d16
0x10,0x0a,0x00,0x1e = vmovne s0, r0
0x10,0x1a,0x00,0x0e = vmoveq s0, r1
0x10,0x1a,0x11,0xee = vmov r1, s2
0x10,0x3a,0x02,0xee = vmov s4, r3
0x12,0x1b,0x55,0xec = vmov r1, r5, d2
0x14,0x3b,0x49,0xec = vmov d4, r3, r9
0x10,0x0a,0xf1,0xee = vmrs r0, fpscr
0x10,0x0a,0xf8,0xee = vmrs r0, fpexc
0x10,0x0a,0xf0,0xee = vmrs r0, fpsid
0x10,0x1a,0xf9,0xee = vmrs r1, fpinst
0x10,0x8a,0xfa,0xee = vmrs r8, fpinst2
0x10,0x0a,0xe1,0xee = vmsr fpscr, r0
0x10,0x0a,0xe8,0xee = vmsr fpexc, r0
0x10,0x0a,0xe0,0xee = vmsr fpsid, r0
0x10,0x3a,0xe9,0xee = vmsr fpinst, r3
0x10,0x4a,0xea,0xee = vmsr fpinst2, r4
0x08,0x0b,0xf0,0xee = vmov.f64 d16, #3.000000e+00
0x08,0x0a,0xb0,0xee = vmov.f32 s0, #3.000000e+00
0x08,0x0b,0xf8,0xee = vmov.f64 d16, #-3.000000e+00
0x08,0x0a,0xb8,0xee = vmov.f32 s0, #-3.000000e+00
0x10,0x0a,0x00,0xee = vmov s0, r0
0x90,0x1a,0x00,0xee = vmov s1, r1
0x10,0x2a,0x01,0xee = vmov s2, r2
0x90,0x3a,0x01,0xee = vmov s3, r3
0x10,0x0a,0x10,0xee = vmov r0, s0
0x90,0x1a,0x10,0xee = vmov r1, s1
0x10,0x2a,0x11,0xee = vmov r2, s2
0x90,0x3a,0x11,0xee = vmov r3, s3
0x30,0x0b,0x51,0xec = vmov r0, r1, d16
0x31,0x1a,0x42,0xec = vmov s3, s4, r1, r2
0x11,0x1a,0x42,0xec = vmov s2, s3, r1, r2
0x31,0x1a,0x52,0xec = vmov r1, r2, s3, s4
0x11,0x1a,0x52,0xec = vmov r1, r2, s2, s3
0x1f,0x1b,0x42,0xec = vmov d15, r1, r2
0x30,0x1b,0x42,0xec = vmov d16, r1, r2
0x1f,0x1b,0x52,0xec = vmov r1, r2, d15
0x30,0x1b,0x52,0xec = vmov r1, r2, d16
0x00,0x1b,0xd0,0xed = vldr d17, [r0]
0x00,0x0a,0x9e,0xed = vldr s0, [lr]
0x00,0x0b,0x9e,0xed = vldr d0, [lr]
0x08,0x1b,0x92,0xed = vldr d1, [r2, #0x20]
0x08,0x1b,0x12,0xed = vldr d1, [r2, #-0x20]
0x00,0x2b,0x93,0xed = vldr d2, [r3]
0x00,0x3b,0x9f,0xed = vldr d3, [pc]
0x00,0x3b,0x9f,0xed = vldr d3, [pc]
0x00,0x3b,0x1f,0xed = vldr d3, [pc, #-0]
0x00,0x6a,0xd0,0xed = vldr s13, [r0]
0x08,0x0a,0xd2,0xed = vldr s1, [r2, #0x20]
0x08,0x0a,0x52,0xed = vldr s1, [r2, #-0x20]
0x00,0x1a,0x93,0xed = vldr s2, [r3]
0x00,0x2a,0xdf,0xed = vldr s5, [pc]
0x00,0x2a,0xdf,0xed = vldr s5, [pc]
0x00,0x2a,0x5f,0xed = vldr s5, [pc, #-0]
0x00,0x4b,0x81,0xed = vstr d4, [r1]
0x06,0x4b,0x81,0xed = vstr d4, [r1, #0x18]
0x06,0x4b,0x01,0xed = vstr d4, [r1, #-0x18]
0x00,0x0a,0x8e,0xed = vstr s0, [lr]
0x00,0x0b,0x8e,0xed = vstr d0, [lr]
0x00,0x2a,0x81,0xed = vstr s4, [r1]
0x06,0x2a,0x81,0xed = vstr s4, [r1, #0x18]
0x06,0x2a,0x01,0xed = vstr s4, [r1, #-0x18]
0x0c,0x2b,0x91,0xec = vldmia r1, {d2, d3, d4, d5, d6, d7}
0x06,0x1a,0x91,0xec = vldmia r1, {s2, s3, s4, s5, s6, s7}
0x0c,0x2b,0x81,0xec = vstmia r1, {d2, d3, d4, d5, d6, d7}
0x06,0x1a,0x81,0xec = vstmia r1, {s2, s3, s4, s5, s6, s7}
0x10,0x8b,0x2d,0xed = vpush {d8, d9, d10, d11, d12, d13, d14, d15}
0x07,0x0b,0xb5,0xec = fldmiax r5!, {d0, d1, d2}
0x05,0x4b,0x90,0x0c = fldmiaxeq r0, {d4, d5}
0x07,0x4b,0x35,0x1d = fldmdbxne r5!, {d4, d5, d6}
0x11,0x0b,0xa5,0xec = fstmiax r5!, {d0, d1, d2, d3, d4, d5, d6, d7}
0x05,0x8b,0x84,0x0c = fstmiaxeq r4, {d8, d9}
0x07,0x2b,0x27,0x1d = fstmdbxne r7!, {d2, d3, d4}
0x40,0x0b,0xbd,0xee = vcvtr.s32.f64 s0, d0
0x60,0x0a,0xbd,0xee = vcvtr.s32.f32 s0, s1
0x40,0x0b,0xbc,0xee = vcvtr.u32.f64 s0, d0
0x60,0x0a,0xbc,0xee = vcvtr.u32.f32 s0, s1
0x90,0x8a,0x00,0xee = vmov s1, r8
0x10,0x4a,0x01,0xee = vmov s2, r4
0x90,0x6a,0x01,0xee = vmov s3, r6
0x10,0x1a,0x02,0xee = vmov s4, r1
0x90,0x2a,0x02,0xee = vmov s5, r2
0x10,0x3a,0x03,0xee = vmov s6, r3
0x10,0x1a,0x14,0xee = vmov r1, s8
0x10,0x2a,0x12,0xee = vmov r2, s4
0x10,0x3a,0x13,0xee = vmov r3, s6
0x90,0x4a,0x10,0xee = vmov r4, s1
0x10,0x5a,0x11,0xee = vmov r5, s2
0x90,0x6a,0x11,0xee = vmov r6, s3
0xc6,0x0a,0xbb,0xee = vcvt.f32.u32 s0, s0, #0x14
0xc0,0x0b,0xba,0xee = vcvt.f64.s32 d0, d0, #0x20
0x67,0x0a,0xbb,0xee = vcvt.f32.u16 s0, s0, #1
0x40,0x0b,0xba,0xee = vcvt.f64.s16 d0, d0, #0x10
0xc6,0x0a,0xfa,0xee = vcvt.f32.s32 s1, s1, #0x14
0xc0,0x4b,0xfb,0xee = vcvt.f64.u32 d20, d20, #0x20
0x67,0x8a,0xfa,0xee = vcvt.f32.s16 s17, s17, #1
0x40,0x7b,0xfb,0xee = vcvt.f64.u16 d23, d23, #0x10
0xc6,0x6a,0xbf,0xee = vcvt.u32.f32 s12, s12, #0x14
0xc0,0x2b,0xbe,0xee = vcvt.s32.f64 d2, d2, #0x20
0x67,0xea,0xbf,0xee = vcvt.u16.f32 s28, s28, #1
0x40,0xfb,0xbe,0xee = vcvt.s16.f64 d15, d15, #0x10
0xc6,0x0a,0xfe,0xee = vcvt.s32.f32 s1, s1, #0x14
0xc0,0x4b,0xff,0xee = vcvt.u32.f64 d20, d20, #0x20
0x67,0x8a,0xfe,0xee = vcvt.s16.f32 s17, s17, #1
0x40,0x7b,0xff,0xee = vcvt.u16.f64 d23, d23, #0x10
0x10,0x40,0x80,0xf2 = vmov.i32 d4, #0x0
0x12,0x46,0x84,0xf2 = vmov.i32 d4, #0x42000000
0x00,0x2a,0xf7,0xee = vmov.f32 s5, #1.000000e+00
0x00,0x2a,0xf4,0xee = vmov.f32 s5, #1.250000e-01
0x0e,0x2a,0xff,0xee = vmov.f32 s5, #-1.875000e+00
0x03,0x2a,0xfe,0xee = vmov.f32 s5, #-5.937500e-01
0x00,0x6b,0xb7,0xee = vmov.f64 d6, #1.000000e+00
0x00,0x6b,0xb4,0xee = vmov.f64 d6, #1.250000e-01
0x0e,0x6b,0xbf,0xee = vmov.f64 d6, #-1.875000e+00
0x03,0x6b,0xbe,0xee = vmov.f64 d6, #-5.937500e-01
0x10,0x7f,0x87,0xf2 = vmov.f32 d7, #1.000000e+00
0x10,0x7f,0x84,0xf2 = vmov.f32 d7, #1.250000e-01
0x1e,0x7f,0x87,0xf3 = vmov.f32 d7, #-1.875000e+00
0x13,0x7f,0x86,0xf3 = vmov.f32 d7, #-5.937500e-01
0x50,0x0f,0xc7,0xf2 = vmov.f32 q8, #1.000000e+00
0x50,0x0f,0xc4,0xf2 = vmov.f32 q8, #1.250000e-01
0x5e,0x0f,0xc7,0xf3 = vmov.f32 q8, #-1.875000e+00
0x53,0x0f,0xc6,0xf3 = vmov.f32 q8, #-5.937500e-01
