# CS_ARCH_HPPA, CS_MODE_HPPA_11+CS_MODE_BIG_ENDIAN, None
0x24,0x41,0x40,0xc3 = cldwx,3 r1(sr1,rp),r3
0x24,0x41,0x60,0xc3 = cldwx,3,s r1(sr1,rp),r3
0x24,0x41,0x40,0xe3 = cldwx,3,m r1(sr1,rp),r3
0x24,0x41,0x60,0xe3 = cldwx,3,sm r1(sr1,rp),r3
0x24,0x41,0x68,0xe3 = cldwx,3,sm,sl r1(sr1,rp),r3
0x2c,0x41,0x40,0xc3 = clddx,3 r1(sr1,rp),r3
0x2c,0x41,0x60,0xc3 = clddx,3,s r1(sr1,rp),r3
0x2c,0x41,0x40,0xe3 = clddx,3,m r1(sr1,rp),r3
0x2c,0x41,0x60,0xe3 = clddx,3,sm r1(sr1,rp),r3
0x2c,0x41,0x68,0xe3 = clddx,3,sm,sl r1(sr1,rp),r3
0x24,0x62,0x42,0xc1 = cstwx,3 r1,rp(sr1,r3)
0x24,0x62,0x62,0xc1 = cstwx,3,s r1,rp(sr1,r3)
0x24,0x62,0x42,0xe1 = cstwx,3,m r1,rp(sr1,r3)
0x24,0x62,0x46,0xe1 = cstwx,3,m,bc r1,rp(sr1,r3)
0x24,0x62,0x62,0xe1 = cstwx,3,sm r1,rp(sr1,r3)
0x24,0x62,0x6a,0xe1 = cstwx,3,sm,sl r1,rp(sr1,r3)
0x2c,0x62,0x42,0xc1 = cstdx,3 r1,rp(sr1,r3)
0x2c,0x62,0x62,0xc1 = cstdx,3,s r1,rp(sr1,r3)
0x2c,0x62,0x42,0xe1 = cstdx,3,m r1,rp(sr1,r3)
0x2c,0x62,0x46,0xe1 = cstdx,3,m,bc r1,rp(sr1,r3)
0x2c,0x62,0x62,0xe1 = cstdx,3,sm r1,rp(sr1,r3)
0x2c,0x62,0x6a,0xe1 = cstdx,3,sm,sl r1,rp(sr1,r3)
0x24,0x3e,0x50,0xc2 = cldws,3 0xf(sr1,r1),rp
0x24,0x3e,0x50,0xe2 = cldws,3,ma 0xf(sr1,r1),rp
0x24,0x3e,0x70,0xe2 = cldws,3,mb 0xf(sr1,r1),rp
0x24,0x3e,0x78,0xe2 = cldws,3,mb,sl 0xf(sr1,r1),rp
0x2c,0x3e,0x50,0xc2 = cldds,3 0xf(sr1,r1),rp
0x2c,0x3e,0x50,0xe2 = cldds,3,ma 0xf(sr1,r1),rp
0x2c,0x3e,0x70,0xe2 = cldds,3,mb 0xf(sr1,r1),rp
0x2c,0x3e,0x78,0xe2 = cldds,3,mb,sl 0xf(sr1,r1),rp
0x24,0x5e,0x52,0xc1 = cstws,3 r1,0xf(sr1,rp)
0x24,0x5e,0x52,0xe1 = cstws,3,ma r1,0xf(sr1,rp)
0x24,0x5e,0x56,0xe1 = cstws,3,ma,bc r1,0xf(sr1,rp)
0x24,0x5e,0x72,0xe1 = cstws,3,mb r1,0xf(sr1,rp)
0x24,0x5e,0x7a,0xe1 = cstws,3,mb,sl r1,0xf(sr1,rp)
0x2c,0x5e,0x52,0xc1 = cstds,3 r1,0xf(sr1,rp)
0x2c,0x5e,0x52,0xe1 = cstds,3,ma r1,0xf(sr1,rp)
0x2c,0x5e,0x56,0xe1 = cstds,3,ma,bc r1,0xf(sr1,rp)
0x2c,0x5e,0x72,0xe1 = cstds,3,mb r1,0xf(sr1,rp)
0x2c,0x5e,0x7a,0xe1 = cstds,3,mb,sl r1,0xf(sr1,rp)