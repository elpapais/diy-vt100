
diy-vt100.elf:     file format elf32-msp430


Disassembly of section .text:

0000c000 <__watchdog_support>:
    c000:	55 42 20 01 	mov.b	&0x0120,r5	
    c004:	35 d0 08 5a 	bis	#23048,	r5	;#0x5a08
    c008:	82 45 1a 03 	mov	r5,	&0x031a	

0000c00c <__init_stack>:
    c00c:	31 40 00 04 	mov	#1024,	r1	;#0x0400

0000c010 <__do_copy_data>:
    c010:	3f 40 0c 00 	mov	#12,	r15	;#0x000c
    c014:	0f 93       	tst	r15		
    c016:	08 24       	jz	$+18     	;abs 0xc028
    c018:	92 42 1a 03 	mov	&0x031a,&0x0120	
    c01c:	20 01 
    c01e:	2f 83       	decd	r15		
    c020:	9f 4f 4a d4 	mov	-11190(r15),512(r15);0xd44a(r15), 0x0200(r15)
    c024:	00 02 
    c026:	f8 23       	jnz	$-14     	;abs 0xc018

0000c028 <__do_clear_bss>:
    c028:	3f 40 0e 01 	mov	#270,	r15	;#0x010e
    c02c:	0f 93       	tst	r15		
    c02e:	07 24       	jz	$+16     	;abs 0xc03e
    c030:	92 42 1a 03 	mov	&0x031a,&0x0120	
    c034:	20 01 
    c036:	1f 83       	dec	r15		
    c038:	cf 43 0c 02 	mov.b	#0,	524(r15);r3 As==00, 0x020c(r15)
    c03c:	f9 23       	jnz	$-12     	;abs 0xc030

0000c03e <main>:
    c03e:	b0 12 6a c0 	call	#0xc06a	
    c042:	b0 12 ea c1 	call	#0xc1ea	
    c046:	b0 12 40 c9 	call	#0xc940	
    c04a:	b0 12 4a c2 	call	#0xc24a	
    c04e:	3f 40 0d 00 	mov	#13,	r15	;#0x000d
    c052:	b0 12 4a c3 	call	#0xc34a	
    c056:	b0 12 b4 c7 	call	#0xc7b4	
    c05a:	32 d0 18 00 	bis	#24,	r2	;#0x0018
    c05e:	ff 3f       	jmp	$+0      	;abs 0xc05e

0000c060 <__stop_progExec__>:
    c060:	32 d0 f0 00 	bis	#240,	r2	;#0x00f0
    c064:	fd 3f       	jmp	$-4      	;abs 0xc060

0000c066 <__ctors_end>:
    c066:	30 40 d2 cc 	br	#0xccd2	

0000c06a <msp430_init>:
    c06a:	b2 40 80 5a 	mov	#23168,	&0x0120	;#0x5a80
    c06e:	20 01 
    c070:	d2 42 f8 10 	mov.b	&0x10f8,&0x0056	
    c074:	56 00 
    c076:	5f 42 ff 10 	mov.b	&0x10ff,r15	
    c07a:	7f 50 30 00 	add.b	#48,	r15	;#0x0030
    c07e:	c2 4f 57 00 	mov.b	r15,	&0x0057	
    c082:	30 41       	ret			

0000c084 <__block_select>:
    c084:	82 4f 00 02 	mov	r15,	&0x0200	
    c088:	30 41       	ret			

0000c08a <block>:
    c08a:	0f 12       	push	r15		
    c08c:	0e 12       	push	r14		
    c08e:	0d 12       	push	r13		
    c090:	0c 12       	push	r12		
    c092:	0b 12       	push	r11		
    c094:	d2 42 66 00 	mov.b	&0x0066,&0x0316	
    c098:	16 03 
    c09a:	f2 e0 40 00 	xor.b	#64,	&0x0021	;#0x0040
    c09e:	21 00 
    c0a0:	1b 42 00 02 	mov	&0x0200,r11	
    c0a4:	18 3c       	jmp	$+50     	;abs 0xc0d6
    c0a6:	db 92 16 03 	cmp.b	&0x0316,2(r11)	;0x0002(r11)
    c0aa:	02 00 
    c0ac:	12 20       	jnz	$+38     	;abs 0xc0d2
    c0ae:	3f 90 84 c0 	cmp	#-16252,r15	;#0xc084
    c0b2:	04 20       	jnz	$+10     	;abs 0xc0bc
    c0b4:	92 4b 04 00 	mov	4(r11),	&0x0200	;0x0004(r11)
    c0b8:	00 02 
    c0ba:	0b 3c       	jmp	$+24     	;abs 0xc0d2
    c0bc:	5f 4b 04 00 	mov.b	4(r11),	r15	;0x0004(r11)
    c0c0:	4f 93       	tst.b	r15		
    c0c2:	04 24       	jz	$+10     	;abs 0xc0cc
    c0c4:	5e 4b 05 00 	mov.b	5(r11),	r14	;0x0005(r11)
    c0c8:	b0 12 14 ca 	call	#0xca14	
    c0cc:	ab 12       	call	@r11		
    c0ce:	c2 43 0e 03 	mov.b	#0,	&0x030e	;r3 As==00
    c0d2:	3b 50 06 00 	add	#6,	r11	;#0x0006
    c0d6:	2f 4b       	mov	@r11,	r15	
    c0d8:	0f 93       	tst	r15		
    c0da:	e5 23       	jnz	$-52     	;abs 0xc0a6
    c0dc:	b2 90 e0 cc 	cmp	#-13088,&0x0200	;#0xcce0
    c0e0:	00 02 
    c0e2:	03 20       	jnz	$+8      	;abs 0xc0ea
    c0e4:	b0 12 7e c5 	call	#0xc57e	
    c0e8:	07 3c       	jmp	$+16     	;abs 0xc0f8
    c0ea:	b0 12 c0 c9 	call	#0xc9c0	
    c0ee:	4f 93       	tst.b	r15		
    c0f0:	03 20       	jnz	$+8      	;abs 0xc0f8
    c0f2:	b2 40 e0 cc 	mov	#-13088,&0x0200	;#0xcce0
    c0f6:	00 02 
    c0f8:	b0 12 08 cc 	call	#0xcc08	
    c0fc:	3b 41       	pop	r11		
    c0fe:	3c 41       	pop	r12		
    c100:	3d 41       	pop	r13		
    c102:	3e 41       	pop	r14		
    c104:	3f 41       	pop	r15		
    c106:	00 13       	reti			

0000c108 <nokia1100_send_data_brustmode>:
    c108:	0b 12       	push	r11		
    c10a:	0a 12       	push	r10		
    c10c:	f2 f0 f7 ff 	and.b	#-9,	&0x0029	;#0xfff7
    c110:	29 00 
    c112:	f2 f0 fd ff 	and.b	#-3,	&0x0029	;#0xfffd
    c116:	29 00 
    c118:	0c 43       	clr	r12		
    c11a:	23 3c       	jmp	$+72     	;abs 0xc162
    c11c:	0d 4f       	mov	r15,	r13	
    c11e:	0d 5c       	add	r12,	r13	
    c120:	6d 4d       	mov.b	@r13,	r13	
    c122:	e2 d2 29 00 	bis.b	#4,	&0x0029	;r2 As==10
    c126:	f2 d2 29 00 	bis.b	#8,	&0x0029	;r2 As==11
    c12a:	7b 40 09 00 	mov.b	#9,	r11	;#0x0009
    c12e:	13 3c       	jmp	$+40     	;abs 0xc156
    c130:	f2 f0 f7 ff 	and.b	#-9,	&0x0029	;#0xfff7
    c134:	29 00 
    c136:	1d b3       	bit	#1,	r13	;r3 As==01
    c138:	04 24       	jz	$+10     	;abs 0xc142
    c13a:	5a 42 29 00 	mov.b	&0x0029,r10	
    c13e:	6a d2       	bis.b	#4,	r10	;r2 As==10
    c140:	04 3c       	jmp	$+10     	;abs 0xc14a
    c142:	5a 42 29 00 	mov.b	&0x0029,r10	
    c146:	7a f0 fb ff 	and.b	#-5,	r10	;#0xfffb
    c14a:	c2 4a 29 00 	mov.b	r10,	&0x0029	
    c14e:	f2 d2 29 00 	bis.b	#8,	&0x0029	;r2 As==11
    c152:	12 c3       	clrc			
    c154:	4d 10       	rrc.b	r13		
    c156:	7b 53       	add.b	#-1,	r11	;r3 As==11
    c158:	eb 23       	jnz	$-40     	;abs 0xc130
    c15a:	f2 f0 f7 ff 	and.b	#-9,	&0x0029	;#0xfff7
    c15e:	29 00 
    c160:	1c 53       	inc	r12		
    c162:	0c 9e       	cmp	r14,	r12	
    c164:	db 23       	jnz	$-72     	;abs 0xc11c
    c166:	e2 d3 29 00 	bis.b	#2,	&0x0029	;r3 As==10
    c16a:	3a 41       	pop	r10		
    c16c:	3b 41       	pop	r11		
    c16e:	30 41       	ret			

0000c170 <nokia1100_send>:
    c170:	f2 f0 f7 ff 	and.b	#-9,	&0x0029	;#0xfff7
    c174:	29 00 
    c176:	f2 f0 fd ff 	and.b	#-3,	&0x0029	;#0xfffd
    c17a:	29 00 
    c17c:	7e 40 0a 00 	mov.b	#10,	r14	;#0x000a
    c180:	11 3c       	jmp	$+36     	;abs 0xc1a4
    c182:	f2 f0 f7 ff 	and.b	#-9,	&0x0029	;#0xfff7
    c186:	29 00 
    c188:	5d 42 29 00 	mov.b	&0x0029,r13	
    c18c:	3f b0 00 01 	bit	#256,	r15	;#0x0100
    c190:	02 24       	jz	$+6      	;abs 0xc196
    c192:	6d d2       	bis.b	#4,	r13	;r2 As==10
    c194:	02 3c       	jmp	$+6      	;abs 0xc19a
    c196:	7d f0 fb ff 	and.b	#-5,	r13	;#0xfffb
    c19a:	c2 4d 29 00 	mov.b	r13,	&0x0029	
    c19e:	f2 d2 29 00 	bis.b	#8,	&0x0029	;r2 As==11
    c1a2:	0f 5f       	rla	r15		
    c1a4:	7e 53       	add.b	#-1,	r14	;r3 As==11
    c1a6:	ed 23       	jnz	$-36     	;abs 0xc182
    c1a8:	e2 d3 29 00 	bis.b	#2,	&0x0029	;r3 As==10
    c1ac:	30 41       	ret			

0000c1ae <nokia1100_clear>:
    c1ae:	0b 12       	push	r11		
    c1b0:	3f 40 a4 00 	mov	#164,	r15	;#0x00a4
    c1b4:	b0 12 70 c1 	call	#0xc170	
    c1b8:	3f 40 b0 00 	mov	#176,	r15	;#0x00b0
    c1bc:	b0 12 70 c1 	call	#0xc170	
    c1c0:	0f 43       	clr	r15		
    c1c2:	b0 12 70 c1 	call	#0xc170	
    c1c6:	3f 40 18 00 	mov	#24,	r15	;#0x0018
    c1ca:	b0 12 70 c1 	call	#0xc170	
    c1ce:	3b 40 60 03 	mov	#864,	r11	;#0x0360
    c1d2:	3f 40 00 01 	mov	#256,	r15	;#0x0100
    c1d6:	b0 12 70 c1 	call	#0xc170	
    c1da:	3b 53       	add	#-1,	r11	;r3 As==11
    c1dc:	fa 23       	jnz	$-10     	;abs 0xc1d2
    c1de:	3f 40 a4 00 	mov	#164,	r15	;#0x00a4
    c1e2:	b0 12 70 c1 	call	#0xc170	
    c1e6:	3b 41       	pop	r11		
    c1e8:	30 41       	ret			

0000c1ea <nokia1100_init>:
    c1ea:	f2 d0 0f 00 	bis.b	#15,	&0x002a	;#0x000f
    c1ee:	2a 00 
    c1f0:	e2 d3 29 00 	bis.b	#2,	&0x0029	;r3 As==10
    c1f4:	f2 f0 fe ff 	and.b	#-2,	&0x0029	;#0xfffe
    c1f8:	29 00 
    c1fa:	d2 d3 29 00 	bis.b	#1,	&0x0029	;r3 As==01
    c1fe:	3f 40 2f 00 	mov	#47,	r15	;#0x002f
    c202:	b0 12 70 c1 	call	#0xc170	
    c206:	3f 40 23 00 	mov	#35,	r15	;#0x0023
    c20a:	b0 12 70 c1 	call	#0xc170	
    c20e:	3f 40 9f 00 	mov	#159,	r15	;#0x009f
    c212:	b0 12 70 c1 	call	#0xc170	
    c216:	3f 40 af 00 	mov	#175,	r15	;#0x00af
    c21a:	b0 12 70 c1 	call	#0xc170	
    c21e:	3f 40 a4 00 	mov	#164,	r15	;#0x00a4
    c222:	b0 12 70 c1 	call	#0xc170	
    c226:	3f 40 a6 00 	mov	#166,	r15	;#0x00a6
    c22a:	b0 12 70 c1 	call	#0xc170	
    c22e:	b0 12 ae c1 	call	#0xc1ae	
    c232:	3f 40 b0 00 	mov	#176,	r15	;#0x00b0
    c236:	b0 12 70 c1 	call	#0xc170	
    c23a:	0f 43       	clr	r15		
    c23c:	b0 12 70 c1 	call	#0xc170	
    c240:	3f 40 18 00 	mov	#24,	r15	;#0x0018
    c244:	b0 12 70 c1 	call	#0xc170	
    c248:	30 41       	ret			

0000c24a <splash>:
    c24a:	0b 12       	push	r11		
    c24c:	0a 12       	push	r10		
    c24e:	3b 40 02 02 	mov	#514,	r11	;#0x0202
    c252:	0a 4b       	mov	r11,	r10	
    c254:	3f 4a       	mov	@r10+,	r15	
    c256:	b0 12 50 c6 	call	#0xc650	
    c25a:	2f 4a       	mov	@r10,	r15	
    c25c:	b0 12 50 c6 	call	#0xc650	
    c260:	1f 4b 04 00 	mov	4(r11),	r15	;0x0004(r11)
    c264:	b0 12 50 c6 	call	#0xc650	
    c268:	1f 4b 06 00 	mov	6(r11),	r15	;0x0006(r11)
    c26c:	b0 12 50 c6 	call	#0xc650	
    c270:	1f 4b 08 00 	mov	8(r11),	r15	;0x0008(r11)
    c274:	b0 12 50 c6 	call	#0xc650	
    c278:	b0 12 08 cc 	call	#0xcc08	
    c27c:	3a 41       	pop	r10		
    c27e:	3b 41       	pop	r11		
    c280:	30 41       	ret			

0000c282 <uart_send>:
    c282:	5e 42 03 00 	mov.b	&0x0003,r14	
    c286:	2e f3       	and	#2,	r14	;r3 As==10
    c288:	fc 27       	jz	$-6      	;abs 0xc282
    c28a:	c2 4f 67 00 	mov.b	r15,	&0x0067	
    c28e:	30 41       	ret			

0000c290 <uart_send_int>:
    c290:	0b 12       	push	r11		
    c292:	0a 12       	push	r10		
    c294:	4a 4f       	mov.b	r15,	r10	
    c296:	4f 9e       	cmp.b	r14,	r15	
    c298:	1d 24       	jz	$+60     	;abs 0xc2d4
    c29a:	7f 90 0a 00 	cmp.b	#10,	r15	;#0x000a
    c29e:	16 28       	jnc	$+46     	;abs 0xc2cc
    c2a0:	7e 40 cd ff 	mov.b	#-51,	r14	;#0xffcd
    c2a4:	b0 12 b2 cc 	call	#0xccb2	
    c2a8:	0b 4f       	mov	r15,	r11	
    c2aa:	8b 10       	swpb	r11		
    c2ac:	12 c3       	clrc			
    c2ae:	4b 10       	rrc.b	r11		
    c2b0:	12 c3       	clrc			
    c2b2:	4b 10       	rrc.b	r11		
    c2b4:	12 c3       	clrc			
    c2b6:	4b 10       	rrc.b	r11		
    c2b8:	4f 4b       	mov.b	r11,	r15	
    c2ba:	b0 12 82 c2 	call	#0xc282	
    c2be:	4b 5b       	rla.b	r11		
    c2c0:	4e 4b       	mov.b	r11,	r14	
    c2c2:	4e 5e       	rla.b	r14		
    c2c4:	4e 5e       	rla.b	r14		
    c2c6:	4b 5e       	add.b	r14,	r11	
    c2c8:	4f 4a       	mov.b	r10,	r15	
    c2ca:	4f 8b       	sub.b	r11,	r15	
    c2cc:	7f 50 30 00 	add.b	#48,	r15	;#0x0030
    c2d0:	b0 12 82 c2 	call	#0xc282	
    c2d4:	3a 41       	pop	r10		
    c2d6:	3b 41       	pop	r11		
    c2d8:	30 41       	ret			

0000c2da <uart_send_string>:
    c2da:	0b 12       	push	r11		
    c2dc:	0b 4f       	mov	r15,	r11	
    c2de:	03 3c       	jmp	$+8      	;abs 0xc2e6
    c2e0:	b0 12 82 c2 	call	#0xc282	
    c2e4:	1b 53       	inc	r11		
    c2e6:	6f 4b       	mov.b	@r11,	r15	
    c2e8:	4f 93       	tst.b	r15		
    c2ea:	fa 23       	jnz	$-10     	;abs 0xc2e0
    c2ec:	3b 41       	pop	r11		
    c2ee:	30 41       	ret			

0000c2f0 <uart_send_param>:
    c2f0:	0b 12       	push	r11		
    c2f2:	0a 12       	push	r10		
    c2f4:	09 12       	push	r9		
    c2f6:	08 12       	push	r8		
    c2f8:	49 4f       	mov.b	r15,	r9	
    c2fa:	4a 4e       	mov.b	r14,	r10	
    c2fc:	48 4d       	mov.b	r13,	r8	
    c2fe:	7f 40 1b 00 	mov.b	#27,	r15	;#0x001b
    c302:	b0 12 82 c2 	call	#0xc282	
    c306:	4f 49       	mov.b	r9,	r15	
    c308:	0c 3c       	jmp	$+26     	;abs 0xc322
    c30a:	4c 4b       	mov.b	r11,	r12	
    c30c:	4e 48       	mov.b	r8,	r14	
    c30e:	5f 4c 0f 03 	mov.b	783(r12),r15	;0x030f(r12)
    c312:	b0 12 90 c2 	call	#0xc290	
    c316:	5b 53       	inc.b	r11		
    c318:	5b 92 0e 03 	cmp.b	&0x030e,r11	
    c31c:	04 2c       	jc	$+10     	;abs 0xc326
    c31e:	7f 40 3b 00 	mov.b	#59,	r15	;#0x003b
    c322:	b0 12 82 c2 	call	#0xc282	
    c326:	5b 92 0e 03 	cmp.b	&0x030e,r11	
    c32a:	ef 2b       	jnc	$-32     	;abs 0xc30a
    c32c:	4f 4a       	mov.b	r10,	r15	
    c32e:	b0 12 82 c2 	call	#0xc282	
    c332:	38 41       	pop	r8		
    c334:	39 41       	pop	r9		
    c336:	3a 41       	pop	r10		
    c338:	3b 41       	pop	r11		
    c33a:	30 41       	ret			

0000c33c <uart_set_baud>:
    c33c:	c2 4f 62 00 	mov.b	r15,	&0x0062	
    c340:	8f 10       	swpb	r15		
    c342:	4f 4f       	mov.b	r15,	r15	
    c344:	c2 4f 63 00 	mov.b	r15,	&0x0063	
    c348:	30 41       	ret			

0000c34a <uart_init>:
    c34a:	f2 40 06 00 	mov.b	#6,	&0x0026	;#0x0006
    c34e:	26 00 
    c350:	f2 40 06 00 	mov.b	#6,	&0x0041	;#0x0006
    c354:	41 00 
    c356:	f2 d0 40 00 	bis.b	#64,	&0x0061	;#0x0040
    c35a:	61 00 
    c35c:	b0 12 3c c3 	call	#0xc33c	
    c360:	f2 40 06 00 	mov.b	#6,	&0x0064	;#0x0006
    c364:	64 00 
    c366:	f2 f0 fe ff 	and.b	#-2,	&0x0061	;#0xfffe
    c36a:	61 00 
    c36c:	d2 d3 01 00 	bis.b	#1,	&0x0001	;r3 As==01
    c370:	30 41       	ret			

0000c372 <vt100_set_doubleheight_tophalf>:
    c372:	3f 40 0c 02 	mov	#524,	r15	;#0x020c
    c376:	0e 4f       	mov	r15,	r14	
    c378:	2e 53       	incd	r14		
    c37a:	6f 4f       	mov.b	@r15,	r15	
    c37c:	0f 5f       	rla	r15		
    c37e:	0f 5f       	rla	r15		
    c380:	0f 5f       	rla	r15		
    c382:	0f 5f       	rla	r15		
    c384:	0f 5f       	rla	r15		
    c386:	0e 5f       	add	r15,	r14	
    c388:	fe d0 20 00 	bis.b	#32,	1(r14)	;#0x0020, 0x0001(r14)
    c38c:	01 00 
    c38e:	30 41       	ret			

0000c390 <vt100_set_doubleheight_bottomhalf>:
    c390:	3f 40 0c 02 	mov	#524,	r15	;#0x020c
    c394:	0e 4f       	mov	r15,	r14	
    c396:	2e 53       	incd	r14		
    c398:	6f 4f       	mov.b	@r15,	r15	
    c39a:	0f 5f       	rla	r15		
    c39c:	0f 5f       	rla	r15		
    c39e:	0f 5f       	rla	r15		
    c3a0:	0f 5f       	rla	r15		
    c3a2:	0f 5f       	rla	r15		
    c3a4:	0e 5f       	add	r15,	r14	
    c3a6:	fe d0 40 00 	bis.b	#64,	1(r14)	;#0x0040, 0x0001(r14)
    c3aa:	01 00 
    c3ac:	30 41       	ret			

0000c3ae <vt100_set_doublewidth>:
    c3ae:	3f 40 0c 02 	mov	#524,	r15	;#0x020c
    c3b2:	0e 4f       	mov	r15,	r14	
    c3b4:	2e 53       	incd	r14		
    c3b6:	6f 4f       	mov.b	@r15,	r15	
    c3b8:	0f 5f       	rla	r15		
    c3ba:	0f 5f       	rla	r15		
    c3bc:	0f 5f       	rla	r15		
    c3be:	0f 5f       	rla	r15		
    c3c0:	0f 5f       	rla	r15		
    c3c2:	0e 5f       	add	r15,	r14	
    c3c4:	fe d0 80 ff 	bis.b	#-128,	1(r14)	;#0xff80, 0x0001(r14)
    c3c8:	01 00 
    c3ca:	30 41       	ret			

0000c3cc <vt100_select_attribute>:
    c3cc:	0b 12       	push	r11		
    c3ce:	0a 12       	push	r10		
    c3d0:	09 12       	push	r9		
    c3d2:	08 12       	push	r8		
    c3d4:	58 42 0e 03 	mov.b	&0x030e,r8	
    c3d8:	f2 b2 18 03 	bit.b	#8,	&0x0318	;r2 As==11
    c3dc:	0e 43       	clr	r14		
    c3de:	0e 6e       	rlc	r14		
    c3e0:	f2 b0 20 00 	bit.b	#32,	&0x0318	;#0x0020
    c3e4:	18 03 
    c3e6:	0f 43       	clr	r15		
    c3e8:	0f 6f       	rlc	r15		
    c3ea:	f2 b0 10 00 	bit.b	#16,	&0x0318	;#0x0010
    c3ee:	18 03 
    c3f0:	0b 43       	clr	r11		
    c3f2:	0b 6b       	rlc	r11		
    c3f4:	f2 b0 40 00 	bit.b	#64,	&0x0318	;#0x0040
    c3f8:	18 03 
    c3fa:	0c 43       	clr	r12		
    c3fc:	0c 6c       	rlc	r12		
    c3fe:	3a 40 0f 03 	mov	#783,	r10	;#0x030f
    c402:	49 43       	clr.b	r9		
    c404:	15 3c       	jmp	$+44     	;abs 0xc430
    c406:	fa 92 00 00 	cmp.b	#8,	0(r10)	;r2 As==11, 0x0000(r10)
    c40a:	10 2c       	jc	$+34     	;abs 0xc42c
    c40c:	6d 4a       	mov.b	@r10,	r13	
    c40e:	0d 5d       	rla	r13		
    c410:	10 4d 20 ce 	br	-12768(r13)	;0xce20(r13)
    c414:	4c 43       	clr.b	r12		
    c416:	4b 43       	clr.b	r11		
    c418:	4f 43       	clr.b	r15		
    c41a:	4e 43       	clr.b	r14		
    c41c:	07 3c       	jmp	$+16     	;abs 0xc42c
    c41e:	5e 43       	mov.b	#1,	r14	;r3 As==01
    c420:	05 3c       	jmp	$+12     	;abs 0xc42c
    c422:	5c 43       	mov.b	#1,	r12	;r3 As==01
    c424:	03 3c       	jmp	$+8      	;abs 0xc42c
    c426:	5f 43       	mov.b	#1,	r15	;r3 As==01
    c428:	01 3c       	jmp	$+4      	;abs 0xc42c
    c42a:	5b 43       	mov.b	#1,	r11	;r3 As==01
    c42c:	59 53       	inc.b	r9		
    c42e:	1a 53       	inc	r10		
    c430:	49 98       	cmp.b	r8,	r9	
    c432:	e9 23       	jnz	$-44     	;abs 0xc406
    c434:	5e f3       	and.b	#1,	r14	;r3 As==01
    c436:	4e 5e       	rla.b	r14		
    c438:	4e 5e       	rla.b	r14		
    c43a:	4e 5e       	rla.b	r14		
    c43c:	5d 42 18 03 	mov.b	&0x0318,r13	
    c440:	7d f0 d7 ff 	and.b	#-41,	r13	;#0xffd7
    c444:	5f f3       	and.b	#1,	r15	;r3 As==01
    c446:	4f 5f       	rla.b	r15		
    c448:	4f 5f       	rla.b	r15		
    c44a:	4f 5f       	rla.b	r15		
    c44c:	4f 5f       	rla.b	r15		
    c44e:	4f 5f       	rla.b	r15		
    c450:	4d de       	bis.b	r14,	r13	
    c452:	4d df       	bis.b	r15,	r13	
    c454:	4f 4b       	mov.b	r11,	r15	
    c456:	5f f3       	and.b	#1,	r15	;r3 As==01
    c458:	4f 5f       	rla.b	r15		
    c45a:	4f 5f       	rla.b	r15		
    c45c:	4f 5f       	rla.b	r15		
    c45e:	4f 5f       	rla.b	r15		
    c460:	7d f0 ef ff 	and.b	#-17,	r13	;#0xffef
    c464:	4d df       	bis.b	r15,	r13	
    c466:	c2 4d 18 03 	mov.b	r13,	&0x0318	
    c46a:	5c f3       	and.b	#1,	r12	;r3 As==01
    c46c:	7f 40 06 00 	mov.b	#6,	r15	;#0x0006
    c470:	4c 5c       	rla.b	r12		
    c472:	7f 53       	add.b	#-1,	r15	;r3 As==11
    c474:	fd 23       	jnz	$-4      	;abs 0xc470
    c476:	5f 42 18 03 	mov.b	&0x0318,r15	
    c47a:	7f f0 bf ff 	and.b	#-65,	r15	;#0xffbf
    c47e:	4f dc       	bis.b	r12,	r15	
    c480:	c2 4f 18 03 	mov.b	r15,	&0x0318	
    c484:	38 41       	pop	r8		
    c486:	39 41       	pop	r9		
    c488:	3a 41       	pop	r10		
    c48a:	3b 41       	pop	r11		
    c48c:	30 41       	ret			

0000c48e <vt100_bell_init>:
    c48e:	f2 d0 20 00 	bis.b	#32,	&0x002a	;#0x0020
    c492:	2a 00 
    c494:	f2 f0 df ff 	and.b	#-33,	&0x0029	;#0xffdf
    c498:	29 00 
    c49a:	30 41       	ret			

0000c49c <vt100_audio_bell>:
    c49c:	f2 d0 20 00 	bis.b	#32,	&0x0029	;#0x0020
    c4a0:	29 00 
    c4a2:	3f 40 82 06 	mov	#1666,	r15	;#0x0682
    c4a6:	1f 83       	dec	r15		
    c4a8:	fe 23       	jnz	$-2      	;abs 0xc4a6
    c4aa:	f2 f0 df ff 	and.b	#-33,	&0x0029	;#0xffdf
    c4ae:	29 00 
    c4b0:	30 41       	ret			

0000c4b2 <vt100_visual_bell>:
    c4b2:	3f 40 a5 00 	mov	#165,	r15	;#0x00a5
    c4b6:	b0 12 70 c1 	call	#0xc170	
    c4ba:	3f 40 82 06 	mov	#1666,	r15	;#0x0682
    c4be:	1f 83       	dec	r15		
    c4c0:	fe 23       	jnz	$-2      	;abs 0xc4be
    c4c2:	3f 40 a4 00 	mov	#164,	r15	;#0x00a4
    c4c6:	b0 12 70 c1 	call	#0xc170	
    c4ca:	30 41       	ret			

0000c4cc <vt100_bell>:
    c4cc:	b0 12 9c c4 	call	#0xc49c	
    c4d0:	30 41       	ret			

0000c4d2 <vt100_buffer_clear_char>:
    c4d2:	4e 4e       	mov.b	r14,	r14	
    c4d4:	4f 4f       	mov.b	r15,	r15	
    c4d6:	0f 5f       	rla	r15		
    c4d8:	0f 5f       	rla	r15		
    c4da:	0f 5f       	rla	r15		
    c4dc:	0f 5f       	rla	r15		
    c4de:	0f 5e       	add	r14,	r15	
    c4e0:	1f 53       	inc	r15		
    c4e2:	0f 5f       	rla	r15		
    c4e4:	3f 50 0c 02 	add	#524,	r15	;#0x020c
    c4e8:	cf 43 00 00 	mov.b	#0,	0(r15)	;r3 As==00, 0x0000(r15)
    c4ec:	ff f0 f0 ff 	and.b	#-16,	1(r15)	;#0xfff0, 0x0001(r15)
    c4f0:	01 00 
    c4f2:	30 41       	ret			

0000c4f4 <vt100_buffer_shiftup>:
    c4f4:	0b 12       	push	r11		
    c4f6:	3d 40 0c 02 	mov	#524,	r13	;#0x020c
    c4fa:	0e 43       	clr	r14		
    c4fc:	0f 4e       	mov	r14,	r15	
    c4fe:	0f 5f       	rla	r15		
    c500:	0f 5f       	rla	r15		
    c502:	0f 5f       	rla	r15		
    c504:	0f 5f       	rla	r15		
    c506:	0f 5f       	rla	r15		
    c508:	ff d0 10 00 	bis.b	#16,	527(r15);#0x0010, 0x020f(r15)
    c50c:	0f 02 
    c50e:	0f 43       	clr	r15		
    c510:	0c 4d       	mov	r13,	r12	
    c512:	0c 5f       	add	r15,	r12	
    c514:	9c 4c 22 00 	mov	34(r12),2(r12)	;0x0022(r12), 0x0002(r12)
    c518:	02 00 
    c51a:	2f 53       	incd	r15		
    c51c:	3f 90 20 00 	cmp	#32,	r15	;#0x0020
    c520:	f7 23       	jnz	$-16     	;abs 0xc510
    c522:	1e 53       	inc	r14		
    c524:	3d 50 20 00 	add	#32,	r13	;#0x0020
    c528:	3e 90 07 00 	cmp	#7,	r14	;#0x0007
    c52c:	e7 23       	jnz	$-48     	;abs 0xc4fc
    c52e:	f2 d0 10 00 	bis.b	#16,	&0x02ef	;#0x0010
    c532:	ef 02 
    c534:	4b 43       	clr.b	r11		
    c536:	4e 4b       	mov.b	r11,	r14	
    c538:	7f 40 07 00 	mov.b	#7,	r15	;#0x0007
    c53c:	b0 12 d2 c4 	call	#0xc4d2	
    c540:	5b 53       	inc.b	r11		
    c542:	7b 90 10 00 	cmp.b	#16,	r11	;#0x0010
    c546:	f7 23       	jnz	$-16     	;abs 0xc536
    c548:	3b 41       	pop	r11		
    c54a:	30 41       	ret			

0000c54c <vt100_buffer_newrow>:
    c54c:	5e 42 0c 02 	mov.b	&0x020c,r14	
    c550:	4f 4e       	mov.b	r14,	r15	
    c552:	0f 5f       	rla	r15		
    c554:	0f 5f       	rla	r15		
    c556:	0f 5f       	rla	r15		
    c558:	0f 5f       	rla	r15		
    c55a:	0f 5f       	rla	r15		
    c55c:	ff d0 10 00 	bis.b	#16,	527(r15);#0x0010, 0x020f(r15)
    c560:	0f 02 
    c562:	4f 4e       	mov.b	r14,	r15	
    c564:	5f 53       	inc.b	r15		
    c566:	c2 4f 0c 02 	mov.b	r15,	&0x020c	
    c56a:	7f 92       	cmp.b	#8,	r15	;r2 As==11
    c56c:	05 28       	jnc	$+12     	;abs 0xc578
    c56e:	b0 12 f4 c4 	call	#0xc4f4	
    c572:	f2 40 07 00 	mov.b	#7,	&0x020c	;#0x0007
    c576:	0c 02 
    c578:	c2 43 0d 02 	mov.b	#0,	&0x020d	;r3 As==00
    c57c:	30 41       	ret			

0000c57e <vt100_buffer_putchar>:
    c57e:	0b 12       	push	r11		
    c580:	0a 12       	push	r10		
    c582:	f2 92 0c 02 	cmp.b	#8,	&0x020c	;r2 As==11
    c586:	07 28       	jnc	$+16     	;abs 0xc596
    c588:	b0 12 f4 c4 	call	#0xc4f4	
    c58c:	f2 40 07 00 	mov.b	#7,	&0x020c	;#0x0007
    c590:	0c 02 
    c592:	c2 43 0d 02 	mov.b	#0,	&0x020d	;r3 As==00
    c596:	5b 42 0c 02 	mov.b	&0x020c,r11	
    c59a:	4f 4b       	mov.b	r11,	r15	
    c59c:	5a 42 0d 02 	mov.b	&0x020d,r10	
    c5a0:	4d 4a       	mov.b	r10,	r13	
    c5a2:	0e 4f       	mov	r15,	r14	
    c5a4:	0e 5e       	rla	r14		
    c5a6:	0e 5e       	rla	r14		
    c5a8:	0e 5e       	rla	r14		
    c5aa:	0e 5e       	rla	r14		
    c5ac:	0e 5d       	add	r13,	r14	
    c5ae:	1e 53       	inc	r14		
    c5b0:	0e 5e       	rla	r14		
    c5b2:	3e 50 0c 02 	add	#524,	r14	;#0x020c
    c5b6:	de 42 16 03 	mov.b	&0x0316,0(r14)	;0x0000(r14)
    c5ba:	00 00 
    c5bc:	f2 b0 20 00 	bit.b	#32,	&0x0318	;#0x0020
    c5c0:	18 03 
    c5c2:	0d 43       	clr	r13		
    c5c4:	0d 6d       	rlc	r13		
    c5c6:	5d f3       	and.b	#1,	r13	;r3 As==01
    c5c8:	4d 5d       	rla.b	r13		
    c5ca:	4d 5d       	rla.b	r13		
    c5cc:	5c 4e 01 00 	mov.b	1(r14),	r12	;0x0001(r14)
    c5d0:	7c f0 fb ff 	and.b	#-5,	r12	;#0xfffb
    c5d4:	4c dd       	bis.b	r13,	r12	
    c5d6:	ce 4c 01 00 	mov.b	r12,	1(r14)	;0x0001(r14)
    c5da:	f2 b0 40 00 	bit.b	#64,	&0x0318	;#0x0040
    c5de:	18 03 
    c5e0:	0d 43       	clr	r13		
    c5e2:	0d 6d       	rlc	r13		
    c5e4:	5d f3       	and.b	#1,	r13	;r3 As==01
    c5e6:	4d 5d       	rla.b	r13		
    c5e8:	7c f0 fd ff 	and.b	#-3,	r12	;#0xfffd
    c5ec:	4c dd       	bis.b	r13,	r12	
    c5ee:	ce 4c 01 00 	mov.b	r12,	1(r14)	;0x0001(r14)
    c5f2:	f2 b0 10 00 	bit.b	#16,	&0x0318	;#0x0010
    c5f6:	18 03 
    c5f8:	0d 43       	clr	r13		
    c5fa:	0d 6d       	rlc	r13		
    c5fc:	5d f3       	and.b	#1,	r13	;r3 As==01
    c5fe:	4d 5d       	rla.b	r13		
    c600:	4d 5d       	rla.b	r13		
    c602:	4d 5d       	rla.b	r13		
    c604:	7c f0 f7 ff 	and.b	#-9,	r12	;#0xfff7
    c608:	4c dd       	bis.b	r13,	r12	
    c60a:	ce 4c 01 00 	mov.b	r12,	1(r14)	;0x0001(r14)
    c60e:	f2 b2 18 03 	bit.b	#8,	&0x0318	;r2 As==11
    c612:	0d 43       	clr	r13		
    c614:	0d 6d       	rlc	r13		
    c616:	5d f3       	and.b	#1,	r13	;r3 As==01
    c618:	7c f0 fe ff 	and.b	#-2,	r12	;#0xfffe
    c61c:	4c dd       	bis.b	r13,	r12	
    c61e:	ce 4c 01 00 	mov.b	r12,	1(r14)	;0x0001(r14)
    c622:	0f 5f       	rla	r15		
    c624:	0f 5f       	rla	r15		
    c626:	0f 5f       	rla	r15		
    c628:	0f 5f       	rla	r15		
    c62a:	0f 5f       	rla	r15		
    c62c:	ff d0 10 00 	bis.b	#16,	527(r15);#0x0010, 0x020f(r15)
    c630:	0f 02 
    c632:	4f 4a       	mov.b	r10,	r15	
    c634:	5f 53       	inc.b	r15		
    c636:	c2 4f 0d 02 	mov.b	r15,	&0x020d	
    c63a:	7f 90 10 00 	cmp.b	#16,	r15	;#0x0010
    c63e:	05 28       	jnc	$+12     	;abs 0xc64a
    c640:	c2 43 0d 02 	mov.b	#0,	&0x020d	;r3 As==00
    c644:	5b 53       	inc.b	r11		
    c646:	c2 4b 0c 02 	mov.b	r11,	&0x020c	
    c64a:	3a 41       	pop	r10		
    c64c:	3b 41       	pop	r11		
    c64e:	30 41       	ret			

0000c650 <vt100_buffer_putstr>:
    c650:	0b 12       	push	r11		
    c652:	0b 4f       	mov	r15,	r11	
    c654:	04 3c       	jmp	$+10     	;abs 0xc65e
    c656:	8f 11       	sxt	r15		
    c658:	b0 12 7e c5 	call	#0xc57e	
    c65c:	1b 53       	inc	r11		
    c65e:	6f 4b       	mov.b	@r11,	r15	
    c660:	4f 93       	tst.b	r15		
    c662:	f9 23       	jnz	$-12     	;abs 0xc656
    c664:	3b 41       	pop	r11		
    c666:	30 41       	ret			

0000c668 <vt100_fill_all_E>:
    c668:	3d 40 0c 02 	mov	#524,	r13	;#0x020c
    c66c:	0e 43       	clr	r14		
    c66e:	0f 4e       	mov	r14,	r15	
    c670:	0f 5f       	rla	r15		
    c672:	0f 5f       	rla	r15		
    c674:	0f 5f       	rla	r15		
    c676:	0f 5f       	rla	r15		
    c678:	0f 5f       	rla	r15		
    c67a:	ff d0 10 00 	bis.b	#16,	527(r15);#0x0010, 0x020f(r15)
    c67e:	0f 02 
    c680:	0f 43       	clr	r15		
    c682:	0c 4d       	mov	r13,	r12	
    c684:	0c 5f       	add	r15,	r12	
    c686:	fc 40 45 00 	mov.b	#69,	2(r12)	;#0x0045, 0x0002(r12)
    c68a:	02 00 
    c68c:	2f 53       	incd	r15		
    c68e:	3f 90 20 00 	cmp	#32,	r15	;#0x0020
    c692:	f7 23       	jnz	$-16     	;abs 0xc682
    c694:	1e 53       	inc	r14		
    c696:	3d 50 20 00 	add	#32,	r13	;#0x0020
    c69a:	3e 92       	cmp	#8,	r14	;r2 As==11
    c69c:	e8 23       	jnz	$-46     	;abs 0xc66e
    c69e:	30 41       	ret			

0000c6a0 <vt100_erase>:
    c6a0:	0b 12       	push	r11		
    c6a2:	0a 12       	push	r10		
    c6a4:	09 12       	push	r9		
    c6a6:	5f 42 0f 03 	mov.b	&0x030f,r15	
    c6aa:	5f 93       	cmp.b	#1,	r15	;r3 As==01
    c6ac:	29 24       	jz	$+84     	;abs 0xc700
    c6ae:	03 28       	jnc	$+8      	;abs 0xc6b6
    c6b0:	6f 93       	cmp.b	#2,	r15	;r3 As==10
    c6b2:	7c 20       	jnz	$+250    	;abs 0xc7ac
    c6b4:	3d 3c       	jmp	$+124    	;abs 0xc730
    c6b6:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c6ba:	0f 5f       	rla	r15		
    c6bc:	0f 5f       	rla	r15		
    c6be:	0f 5f       	rla	r15		
    c6c0:	0f 5f       	rla	r15		
    c6c2:	0f 5f       	rla	r15		
    c6c4:	ff d0 10 00 	bis.b	#16,	527(r15);#0x0010, 0x020f(r15)
    c6c8:	0f 02 
    c6ca:	5b 42 0d 02 	mov.b	&0x020d,r11	
    c6ce:	06 3c       	jmp	$+14     	;abs 0xc6dc
    c6d0:	4e 4b       	mov.b	r11,	r14	
    c6d2:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c6d6:	b0 12 d2 c4 	call	#0xc4d2	
    c6da:	5b 53       	inc.b	r11		
    c6dc:	7b 90 10 00 	cmp.b	#16,	r11	;#0x0010
    c6e0:	f7 2b       	jnc	$-16     	;abs 0xc6d0
    c6e2:	64 3c       	jmp	$+202    	;abs 0xc7ac
    c6e4:	fe d0 10 00 	bis.b	#16,	527(r14);#0x0010, 0x020f(r14)
    c6e8:	0f 02 
    c6ea:	4a 43       	clr.b	r10		
    c6ec:	4e 4a       	mov.b	r10,	r14	
    c6ee:	4f 4b       	mov.b	r11,	r15	
    c6f0:	b0 12 d2 c4 	call	#0xc4d2	
    c6f4:	5a 53       	inc.b	r10		
    c6f6:	7a 90 10 00 	cmp.b	#16,	r10	;#0x0010
    c6fa:	f8 23       	jnz	$-14     	;abs 0xc6ec
    c6fc:	5b 53       	inc.b	r11		
    c6fe:	01 3c       	jmp	$+4      	;abs 0xc702
    c700:	4b 43       	clr.b	r11		
    c702:	4e 4b       	mov.b	r11,	r14	
    c704:	0e 5e       	rla	r14		
    c706:	0e 5e       	rla	r14		
    c708:	0e 5e       	rla	r14		
    c70a:	0e 5e       	rla	r14		
    c70c:	0e 5e       	rla	r14		
    c70e:	5b 92 0c 02 	cmp.b	&0x020c,r11	
    c712:	e8 2b       	jnc	$-46     	;abs 0xc6e4
    c714:	fe d0 10 00 	bis.b	#16,	527(r14);#0x0010, 0x020f(r14)
    c718:	0f 02 
    c71a:	4a 43       	clr.b	r10		
    c71c:	05 3c       	jmp	$+12     	;abs 0xc728
    c71e:	4e 4a       	mov.b	r10,	r14	
    c720:	4f 4b       	mov.b	r11,	r15	
    c722:	b0 12 d2 c4 	call	#0xc4d2	
    c726:	5a 53       	inc.b	r10		
    c728:	c2 9a 0d 02 	cmp.b	r10,	&0x020d	
    c72c:	f8 2f       	jc	$-14     	;abs 0xc71e
    c72e:	3e 3c       	jmp	$+126    	;abs 0xc7ac
    c730:	b0 12 ae c1 	call	#0xc1ae	
    c734:	0b 43       	clr	r11		
    c736:	49 4b       	mov.b	r11,	r9	
    c738:	0e 4b       	mov	r11,	r14	
    c73a:	0e 5e       	rla	r14		
    c73c:	0e 5e       	rla	r14		
    c73e:	0e 5e       	rla	r14		
    c740:	0e 5e       	rla	r14		
    c742:	0e 5e       	rla	r14		
    c744:	fe d0 10 00 	bis.b	#16,	527(r14);#0x0010, 0x020f(r14)
    c748:	0f 02 
    c74a:	4a 43       	clr.b	r10		
    c74c:	4e 4a       	mov.b	r10,	r14	
    c74e:	4f 49       	mov.b	r9,	r15	
    c750:	b0 12 d2 c4 	call	#0xc4d2	
    c754:	5a 53       	inc.b	r10		
    c756:	7a 90 10 00 	cmp.b	#16,	r10	;#0x0010
    c75a:	f8 23       	jnz	$-14     	;abs 0xc74c
    c75c:	1b 53       	inc	r11		
    c75e:	3b 92       	cmp	#8,	r11	;r2 As==11
    c760:	ea 23       	jnz	$-42     	;abs 0xc736
    c762:	5f 42 16 03 	mov.b	&0x0316,r15	
    c766:	7f 90 4a 00 	cmp.b	#74,	r15	;#0x004a
    c76a:	19 20       	jnz	$+52     	;abs 0xc79e
    c76c:	f2 f0 7f 00 	and.b	#127,	&0x020f	;#0x007f
    c770:	0f 02 
    c772:	f2 f0 7f 00 	and.b	#127,	&0x022f	;#0x007f
    c776:	2f 02 
    c778:	f2 f0 7f 00 	and.b	#127,	&0x024f	;#0x007f
    c77c:	4f 02 
    c77e:	f2 f0 7f 00 	and.b	#127,	&0x026f	;#0x007f
    c782:	6f 02 
    c784:	f2 f0 7f 00 	and.b	#127,	&0x028f	;#0x007f
    c788:	8f 02 
    c78a:	f2 f0 7f 00 	and.b	#127,	&0x02af	;#0x007f
    c78e:	af 02 
    c790:	f2 f0 7f 00 	and.b	#127,	&0x02cf	;#0x007f
    c794:	cf 02 
    c796:	f2 f0 7f 00 	and.b	#127,	&0x02ef	;#0x007f
    c79a:	ef 02 
    c79c:	07 3c       	jmp	$+16     	;abs 0xc7ac
    c79e:	7f 90 4b 00 	cmp.b	#75,	r15	;#0x004b
    c7a2:	04 20       	jnz	$+10     	;abs 0xc7ac
    c7a4:	c2 43 0d 02 	mov.b	#0,	&0x020d	;r3 As==00
    c7a8:	c2 43 0c 02 	mov.b	#0,	&0x020c	;r3 As==00
    c7ac:	39 41       	pop	r9		
    c7ae:	3a 41       	pop	r10		
    c7b0:	3b 41       	pop	r11		
    c7b2:	30 41       	ret			

0000c7b4 <vt100_cursor>:
    c7b4:	b2 40 05 00 	mov	#5,	&0x0172	;#0x0005
    c7b8:	72 01 
    c7ba:	b2 40 10 00 	mov	#16,	&0x0162	;#0x0010
    c7be:	62 01 
    c7c0:	b2 40 d0 01 	mov	#464,	&0x0160	;#0x01d0
    c7c4:	60 01 
    c7c6:	30 41       	ret			

0000c7c8 <timer0_interrupt>:
    c7c8:	0f 12       	push	r15		
    c7ca:	0e 12       	push	r14		
    c7cc:	0d 12       	push	r13		
    c7ce:	0c 12       	push	r12		
    c7d0:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c7d4:	0e 4f       	mov	r15,	r14	
    c7d6:	0e 5e       	rla	r14		
    c7d8:	0e 5e       	rla	r14		
    c7da:	0e 5e       	rla	r14		
    c7dc:	0e 5e       	rla	r14		
    c7de:	0e 5e       	rla	r14		
    c7e0:	5e 4e 0f 02 	mov.b	527(r14),r14	;0x020f(r14)
    c7e4:	3e b0 80 00 	bit	#128,	r14	;#0x0080
    c7e8:	0e 43       	clr	r14		
    c7ea:	0e 6e       	rlc	r14		
    c7ec:	4e 93       	tst.b	r14		
    c7ee:	08 24       	jz	$+18     	;abs 0xc800
    c7f0:	5e 42 0d 02 	mov.b	&0x020d,r14	
    c7f4:	7e 90 09 00 	cmp.b	#9,	r14	;#0x0009
    c7f8:	03 28       	jnc	$+8      	;abs 0xc800
    c7fa:	12 c3       	clrc			
    c7fc:	52 10 0d 02 	rrc.b	&0x020d	
    c800:	3f f0 0f 00 	and	#15,	r15	;#0x000f
    c804:	3f d0 b0 00 	bis	#176,	r15	;#0x00b0
    c808:	b0 12 70 c1 	call	#0xc170	
    c80c:	5f 42 0d 02 	mov.b	&0x020d,r15	
    c810:	3f f0 0f 00 	and	#15,	r15	;#0x000f
    c814:	b0 12 70 c1 	call	#0xc170	
    c818:	5f 42 0d 02 	mov.b	&0x020d,r15	
    c81c:	12 c3       	clrc			
    c81e:	4f 10       	rrc.b	r15		
    c820:	12 c3       	clrc			
    c822:	4f 10       	rrc.b	r15		
    c824:	12 c3       	clrc			
    c826:	4f 10       	rrc.b	r15		
    c828:	12 c3       	clrc			
    c82a:	4f 10       	rrc.b	r15		
    c82c:	7f d0 18 00 	bis.b	#24,	r15	;#0x0018
    c830:	3f f0 1f 00 	and	#31,	r15	;#0x001f
    c834:	b0 12 70 c1 	call	#0xc170	
    c838:	e2 b2 18 03 	bit.b	#4,	&0x0318	;r2 As==10
    c83c:	02 24       	jz	$+6      	;abs 0xc842
    c83e:	5d 43       	mov.b	#1,	r13	;r3 As==01
    c840:	01 3c       	jmp	$+4      	;abs 0xc844
    c842:	4d 43       	clr.b	r13		
    c844:	5e 42 0d 02 	mov.b	&0x020d,r14	
    c848:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c84c:	b0 12 ce ca 	call	#0xcace	
    c850:	5e 42 18 03 	mov.b	&0x0318,r14	
    c854:	6e f2       	and.b	#4,	r14	;r2 As==10
    c856:	5f 43       	mov.b	#1,	r15	;r3 As==01
    c858:	01 24       	jz	$+4      	;abs 0xc85c
    c85a:	4f 43       	clr.b	r15		
    c85c:	4f 5f       	rla.b	r15		
    c85e:	4f 5f       	rla.b	r15		
    c860:	5e 42 18 03 	mov.b	&0x0318,r14	
    c864:	7e f0 fb ff 	and.b	#-5,	r14	;#0xfffb
    c868:	4e df       	bis.b	r15,	r14	
    c86a:	c2 4e 18 03 	mov.b	r14,	&0x0318	
    c86e:	3c 41       	pop	r12		
    c870:	3d 41       	pop	r13		
    c872:	3e 41       	pop	r14		
    c874:	3f 41       	pop	r15		
    c876:	00 13       	reti			

0000c878 <vt100_cursor_backward>:
    c878:	5f 42 0d 02 	mov.b	&0x020d,r15	
    c87c:	5e 42 0f 03 	mov.b	&0x030f,r14	
    c880:	0f 8e       	sub	r14,	r15	
    c882:	0f 93       	tst	r15		
    c884:	07 38       	jl	$+16     	;abs 0xc894
    c886:	3f 90 10 00 	cmp	#16,	r15	;#0x0010
    c88a:	02 38       	jl	$+6      	;abs 0xc890
    c88c:	3f 40 0f 00 	mov	#15,	r15	;#0x000f
    c890:	4f 4f       	mov.b	r15,	r15	
    c892:	01 3c       	jmp	$+4      	;abs 0xc896
    c894:	4f 43       	clr.b	r15		
    c896:	c2 4f 0d 02 	mov.b	r15,	&0x020d	
    c89a:	30 41       	ret			

0000c89c <vt100_cursor_forward>:
    c89c:	5f 42 0d 02 	mov.b	&0x020d,r15	
    c8a0:	5e 42 0f 03 	mov.b	&0x030f,r14	
    c8a4:	0f 5e       	add	r14,	r15	
    c8a6:	3f 90 10 00 	cmp	#16,	r15	;#0x0010
    c8aa:	02 38       	jl	$+6      	;abs 0xc8b0
    c8ac:	3f 40 0f 00 	mov	#15,	r15	;#0x000f
    c8b0:	c2 4f 0d 02 	mov.b	r15,	&0x020d	
    c8b4:	30 41       	ret			

0000c8b6 <vt100_cursor_up>:
    c8b6:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c8ba:	5e 42 0f 03 	mov.b	&0x030f,r14	
    c8be:	0f 8e       	sub	r14,	r15	
    c8c0:	0f 93       	tst	r15		
    c8c2:	07 38       	jl	$+16     	;abs 0xc8d2
    c8c4:	3f 90 10 00 	cmp	#16,	r15	;#0x0010
    c8c8:	02 38       	jl	$+6      	;abs 0xc8ce
    c8ca:	3f 40 0f 00 	mov	#15,	r15	;#0x000f
    c8ce:	4f 4f       	mov.b	r15,	r15	
    c8d0:	01 3c       	jmp	$+4      	;abs 0xc8d4
    c8d2:	4f 43       	clr.b	r15		
    c8d4:	c2 4f 0c 02 	mov.b	r15,	&0x020c	
    c8d8:	30 41       	ret			

0000c8da <vt100_cursor_down>:
    c8da:	5f 42 0c 02 	mov.b	&0x020c,r15	
    c8de:	5e 42 0f 03 	mov.b	&0x030f,r14	
    c8e2:	0f 5e       	add	r14,	r15	
    c8e4:	3f 90 10 00 	cmp	#16,	r15	;#0x0010
    c8e8:	02 38       	jl	$+6      	;abs 0xc8ee
    c8ea:	3f 40 0f 00 	mov	#15,	r15	;#0x000f
    c8ee:	c2 4f 0c 02 	mov.b	r15,	&0x020c	
    c8f2:	30 41       	ret			

0000c8f4 <vt100_cursor_position>:
    c8f4:	5f 42 0f 03 	mov.b	&0x030f,r15	
    c8f8:	7f 90 10 00 	cmp.b	#16,	r15	;#0x0010
    c8fc:	02 28       	jnc	$+6      	;abs 0xc902
    c8fe:	7f 40 0f 00 	mov.b	#15,	r15	;#0x000f
    c902:	c2 4f 0c 02 	mov.b	r15,	&0x020c	
    c906:	5f 42 10 03 	mov.b	&0x0310,r15	
    c90a:	7f 90 10 00 	cmp.b	#16,	r15	;#0x0010
    c90e:	02 28       	jnc	$+6      	;abs 0xc914
    c910:	7f 40 0f 00 	mov.b	#15,	r15	;#0x000f
    c914:	c2 4f 0d 02 	mov.b	r15,	&0x020d	
    c918:	30 41       	ret			

0000c91a <vt100_restore_cursor>:
    c91a:	30 41       	ret			

0000c91c <vt100_save_cursor>:
    c91c:	30 41       	ret			

0000c91e <vt100_get_font>:
    c91e:	7f 90 20 00 	cmp.b	#32,	r15	;#0x0020
    c922:	0c 28       	jnc	$+26     	;abs 0xc93c
    c924:	4e 4e       	mov.b	r14,	r14	
    c926:	4f 4f       	mov.b	r15,	r15	
    c928:	3f 50 e0 ff 	add	#-32,	r15	;#0xffe0
    c92c:	0d 4f       	mov	r15,	r13	
    c92e:	0d 5d       	rla	r13		
    c930:	0f 5d       	add	r13,	r15	
    c932:	0f 5f       	rla	r15		
    c934:	0f 5e       	add	r14,	r15	
    c936:	5f 4f 30 ce 	mov.b	-12752(r15),r15	;0xce30(r15)
    c93a:	30 41       	ret			
    c93c:	4f 43       	clr.b	r15		
    c93e:	30 41       	ret			

0000c940 <vt100_init>:
    c940:	b0 12 8e c4 	call	#0xc48e	
    c944:	b0 12 5a c9 	call	#0xc95a	
    c948:	6e 43       	mov.b	#2,	r14	;r3 As==10
    c94a:	5f 43       	mov.b	#1,	r15	;r3 As==01
    c94c:	b0 12 14 ca 	call	#0xca14	
    c950:	b0 12 a0 c6 	call	#0xc6a0	
    c954:	30 41       	ret			

0000c956 <__is_vt100_malfunctioning>:
    c956:	4f 43       	clr.b	r15		
    c958:	30 41       	ret			

0000c95a <vt100_led_init>:
    c95a:	f2 d0 7f 00 	bis.b	#127,	&0x0022	;#0x007f
    c95e:	22 00 
    c960:	d2 d3 21 00 	bis.b	#1,	&0x0021	;r3 As==01
    c964:	30 41       	ret			

0000c966 <vt100_load_led>:
    c966:	0b 12       	push	r11		
    c968:	5b 42 0e 03 	mov.b	&0x030e,r11	
    c96c:	5c 42 0f 03 	mov.b	&0x030f,r12	
    c970:	4e 43       	clr.b	r14		
    c972:	4d 4c       	mov.b	r12,	r13	
    c974:	21 3c       	jmp	$+68     	;abs 0xc9b8
    c976:	7c 90 05 00 	cmp.b	#5,	r12	;#0x0005
    c97a:	1d 2c       	jc	$+60     	;abs 0xc9b6
    c97c:	0f 4d       	mov	r13,	r15	
    c97e:	0f 5f       	rla	r15		
    c980:	10 4f 30 d4 	br	-11216(r15)	;0xd430(r15)
    c984:	5f 42 21 00 	mov.b	&0x0021,r15	
    c988:	7f f0 87 ff 	and.b	#-121,	r15	;#0xff87
    c98c:	12 3c       	jmp	$+38     	;abs 0xc9b2
    c98e:	5f 42 21 00 	mov.b	&0x0021,r15	
    c992:	7f d2       	bis.b	#8,	r15	;r2 As==11
    c994:	0e 3c       	jmp	$+30     	;abs 0xc9b2
    c996:	5f 42 21 00 	mov.b	&0x0021,r15	
    c99a:	7f d0 10 00 	bis.b	#16,	r15	;#0x0010
    c99e:	09 3c       	jmp	$+20     	;abs 0xc9b2
    c9a0:	5f 42 21 00 	mov.b	&0x0021,r15	
    c9a4:	7f d0 20 00 	bis.b	#32,	r15	;#0x0020
    c9a8:	04 3c       	jmp	$+10     	;abs 0xc9b2
    c9aa:	5f 42 21 00 	mov.b	&0x0021,r15	
    c9ae:	7f d0 40 00 	bis.b	#64,	r15	;#0x0040
    c9b2:	c2 4f 21 00 	mov.b	r15,	&0x0021	
    c9b6:	5e 53       	inc.b	r14		
    c9b8:	4e 9b       	cmp.b	r11,	r14	
    c9ba:	dd 23       	jnz	$-68     	;abs 0xc976
    c9bc:	3b 41       	pop	r11		
    c9be:	30 41       	ret			

0000c9c0 <vt100_param_add>:
    c9c0:	5c 42 16 03 	mov.b	&0x0316,r12	
    c9c4:	7c 90 3b 00 	cmp.b	#59,	r12	;#0x003b
    c9c8:	09 20       	jnz	$+20     	;abs 0xc9dc
    c9ca:	5f 42 0e 03 	mov.b	&0x030e,r15	
    c9ce:	5f 53       	inc.b	r15		
    c9d0:	c2 4f 0e 03 	mov.b	r15,	&0x030e	
    c9d4:	4f 4f       	mov.b	r15,	r15	
    c9d6:	cf 43 0e 03 	mov.b	#0,	782(r15);r3 As==00, 0x030e(r15)
    c9da:	18 3c       	jmp	$+50     	;abs 0xca0c
    c9dc:	7c 50 d0 ff 	add.b	#-48,	r12	;#0xffd0
    c9e0:	7c 90 0a 00 	cmp.b	#10,	r12	;#0x000a
    c9e4:	15 2c       	jc	$+44     	;abs 0xca10
    c9e6:	c2 93 0e 03 	tst.b	&0x030e	
    c9ea:	04 20       	jnz	$+10     	;abs 0xc9f4
    c9ec:	d2 43 0e 03 	mov.b	#1,	&0x030e	;r3 As==01
    c9f0:	c2 43 0f 03 	mov.b	#0,	&0x030f	;r3 As==00
    c9f4:	5d 42 0e 03 	mov.b	&0x030e,r13	
    c9f8:	5e 4d 0e 03 	mov.b	782(r13),r14	;0x030e(r13)
    c9fc:	4e 5e       	rla.b	r14		
    c9fe:	4f 4e       	mov.b	r14,	r15	
    ca00:	4f 5f       	rla.b	r15		
    ca02:	4f 5f       	rla.b	r15		
    ca04:	4f 5e       	add.b	r14,	r15	
    ca06:	4f 5c       	add.b	r12,	r15	
    ca08:	cd 4f 0e 03 	mov.b	r15,	782(r13);0x030e(r13)
    ca0c:	5f 43       	mov.b	#1,	r15	;r3 As==01
    ca0e:	30 41       	ret			
    ca10:	4f 43       	clr.b	r15		
    ca12:	30 41       	ret			

0000ca14 <vt100_param_default>:
    ca14:	04 3c       	jmp	$+10     	;abs 0xca1e
    ca16:	4d 4f       	mov.b	r15,	r13	
    ca18:	cd 4e 0e 03 	mov.b	r14,	782(r13);0x030e(r13)
    ca1c:	7f 53       	add.b	#-1,	r15	;r3 As==11
    ca1e:	c2 9f 0e 03 	cmp.b	r15,	&0x030e	
    ca22:	f9 2b       	jnc	$-12     	;abs 0xca16
    ca24:	30 41       	ret			

0000ca26 <vt100_report_parameters>:
    ca26:	5f 43       	mov.b	#1,	r15	;r3 As==01
    ca28:	c2 93 0f 03 	tst.b	&0x030f	
    ca2c:	01 24       	jz	$+4      	;abs 0xca30
    ca2e:	4f 43       	clr.b	r15		
    ca30:	4f 5f       	rla.b	r15		
    ca32:	5e 42 18 03 	mov.b	&0x0318,r14	
    ca36:	7e f0 fd ff 	and.b	#-3,	r14	;#0xfffd
    ca3a:	4e df       	bis.b	r15,	r14	
    ca3c:	c2 4e 18 03 	mov.b	r14,	&0x0318	
    ca40:	f2 40 06 00 	mov.b	#6,	&0x030e	;#0x0006
    ca44:	0e 03 
    ca46:	f2 40 03 00 	mov.b	#3,	&0x030f	;#0x0003
    ca4a:	0f 03 
    ca4c:	d2 43 10 03 	mov.b	#1,	&0x0310	;r3 As==01
    ca50:	d2 43 11 03 	mov.b	#1,	&0x0311	;r3 As==01
    ca54:	f2 40 70 00 	mov.b	#112,	&0x0312	;#0x0070
    ca58:	12 03 
    ca5a:	f2 40 10 00 	mov.b	#16,	&0x0313	;#0x0010
    ca5e:	13 03 
    ca60:	c2 43 14 03 	mov.b	#0,	&0x0314	;r3 As==00
    ca64:	4d 43       	clr.b	r13		
    ca66:	7e 40 78 00 	mov.b	#120,	r14	;#0x0078
    ca6a:	7f 40 5b 00 	mov.b	#91,	r15	;#0x005b
    ca6e:	b0 12 f0 c2 	call	#0xc2f0	
    ca72:	30 41       	ret			

0000ca74 <vt100_DSR>:
    ca74:	f2 90 05 00 	cmp.b	#5,	&0x030f	;#0x0005
    ca78:	0f 03 
    ca7a:	10 20       	jnz	$+34     	;abs 0xca9c
    ca7c:	7f 40 1b 00 	mov.b	#27,	r15	;#0x001b
    ca80:	b0 12 82 c2 	call	#0xc282	
    ca84:	b0 12 56 c9 	call	#0xc956	
    ca88:	4f 93       	tst.b	r15		
    ca8a:	03 24       	jz	$+8      	;abs 0xca92
    ca8c:	3f 40 3a d4 	mov	#-11206,r15	;#0xd43a
    ca90:	02 3c       	jmp	$+6      	;abs 0xca96
    ca92:	3f 40 3e d4 	mov	#-11202,r15	;#0xd43e
    ca96:	b0 12 da c2 	call	#0xc2da	
    ca9a:	30 41       	ret			
    ca9c:	e2 43 0e 03 	mov.b	#2,	&0x030e	;r3 As==10
    caa0:	d2 42 0c 02 	mov.b	&0x020c,&0x030f	
    caa4:	0f 03 
    caa6:	d2 42 0d 02 	mov.b	&0x020d,&0x0310	
    caaa:	10 03 
    caac:	5d 43       	mov.b	#1,	r13	;r3 As==01
    caae:	7e 40 6e 00 	mov.b	#110,	r14	;#0x006e
    cab2:	7f 40 5b 00 	mov.b	#91,	r15	;#0x005b
    cab6:	b0 12 f0 c2 	call	#0xc2f0	
    caba:	30 41       	ret			

0000cabc <vt100_identity>:
    cabc:	7f 40 1b 00 	mov.b	#27,	r15	;#0x001b
    cac0:	b0 12 82 c2 	call	#0xc282	
    cac4:	3f 40 42 d4 	mov	#-11198,r15	;#0xd442
    cac8:	b0 12 da c2 	call	#0xc2da	
    cacc:	30 41       	ret			

0000cace <vt100_print_char>:
    cace:	0b 12       	push	r11		
    cad0:	0a 12       	push	r10		
    cad2:	09 12       	push	r9		
    cad4:	08 12       	push	r8		
    cad6:	07 12       	push	r7		
    cad8:	06 12       	push	r6		
    cada:	46 4d       	mov.b	r13,	r6	
    cadc:	08 43       	clr	r8		
    cade:	49 4f       	mov.b	r15,	r9	
    cae0:	47 4e       	mov.b	r14,	r7	
    cae2:	0c 49       	mov	r9,	r12	
    cae4:	0c 5c       	rla	r12		
    cae6:	0c 5c       	rla	r12		
    cae8:	0c 5c       	rla	r12		
    caea:	0c 5c       	rla	r12		
    caec:	0c 57       	add	r7,	r12	
    caee:	1c 53       	inc	r12		
    caf0:	0c 5c       	rla	r12		
    caf2:	0a 4c       	mov	r12,	r10	
    caf4:	3a 50 0c 02 	add	#524,	r10	;#0x020c
    caf8:	0e 48       	mov	r8,	r14	
    cafa:	6f 4a       	mov.b	@r10,	r15	
    cafc:	b0 12 1e c9 	call	#0xc91e	
    cb00:	4b 4f       	mov.b	r15,	r11	
    cb02:	fa b2 01 00 	bit.b	#8,	1(r10)	;r2 As==11, 0x0001(r10)
    cb06:	0c 43       	clr	r12		
    cb08:	0c 6c       	rlc	r12		
    cb0a:	4c 93       	tst.b	r12		
    cb0c:	01 24       	jz	$+4      	;abs 0xcb10
    cb0e:	7b e3       	xor.b	#-1,	r11	;r3 As==11
    cb10:	0c 49       	mov	r9,	r12	
    cb12:	0c 5c       	rla	r12		
    cb14:	0c 5c       	rla	r12		
    cb16:	0c 5c       	rla	r12		
    cb18:	0c 5c       	rla	r12		
    cb1a:	0c 57       	add	r7,	r12	
    cb1c:	1c 53       	inc	r12		
    cb1e:	0c 5c       	rla	r12		
    cb20:	3c 50 0c 02 	add	#524,	r12	;#0x020c
    cb24:	ec b3 01 00 	bit.b	#2,	1(r12)	;r3 As==10, 0x0001(r12)
    cb28:	0c 43       	clr	r12		
    cb2a:	0c 6c       	rlc	r12		
    cb2c:	4c 93       	tst.b	r12		
    cb2e:	02 24       	jz	$+6      	;abs 0xcb34
    cb30:	7b 50 80 ff 	add.b	#-128,	r11	;#0xff80
    cb34:	0c 49       	mov	r9,	r12	
    cb36:	0c 5c       	rla	r12		
    cb38:	0c 5c       	rla	r12		
    cb3a:	0c 5c       	rla	r12		
    cb3c:	0c 5c       	rla	r12		
    cb3e:	0c 5c       	rla	r12		
    cb40:	3c 50 0e 02 	add	#526,	r12	;#0x020e
    cb44:	fc b0 20 00 	bit.b	#32,	1(r12)	;#0x0020, 0x0001(r12)
    cb48:	01 00 
    cb4a:	0a 43       	clr	r10		
    cb4c:	0a 6a       	rlc	r10		
    cb4e:	4a 93       	tst.b	r10		
    cb50:	14 24       	jz	$+42     	;abs 0xcb7a
    cb52:	4f 4b       	mov.b	r11,	r15	
    cb54:	3f b2       	bit	#8,	r15	;r2 As==11
    cb56:	03 24       	jz	$+8      	;abs 0xcb5e
    cb58:	7b 40 c0 ff 	mov.b	#-64,	r11	;#0xffc0
    cb5c:	01 3c       	jmp	$+4      	;abs 0xcb60
    cb5e:	4b 43       	clr.b	r11		
    cb60:	2f b2       	bit	#4,	r15	;r2 As==10
    cb62:	02 24       	jz	$+6      	;abs 0xcb68
    cb64:	7b d0 30 00 	bis.b	#48,	r11	;#0x0030
    cb68:	2f b3       	bit	#2,	r15	;r3 As==10
    cb6a:	02 24       	jz	$+6      	;abs 0xcb70
    cb6c:	7b d0 0c 00 	bis.b	#12,	r11	;#0x000c
    cb70:	1f f3       	and	#1,	r15	;r3 As==01
    cb72:	23 24       	jz	$+72     	;abs 0xcbba
    cb74:	7b d0 03 00 	bis.b	#3,	r11	;#0x0003
    cb78:	20 3c       	jmp	$+66     	;abs 0xcbba
    cb7a:	fc b0 40 00 	bit.b	#64,	1(r12)	;#0x0040, 0x0001(r12)
    cb7e:	01 00 
    cb80:	0c 43       	clr	r12		
    cb82:	0c 6c       	rlc	r12		
    cb84:	4c 93       	tst.b	r12		
    cb86:	19 24       	jz	$+52     	;abs 0xcbba
    cb88:	4b 93       	tst.b	r11		
    cb8a:	02 38       	jl	$+6      	;abs 0xcb90
    cb8c:	4c 43       	clr.b	r12		
    cb8e:	02 3c       	jmp	$+6      	;abs 0xcb94
    cb90:	7c 40 03 00 	mov.b	#3,	r12	;#0x0003
    cb94:	4b 4b       	mov.b	r11,	r11	
    cb96:	3b b0 40 00 	bit	#64,	r11	;#0x0040
    cb9a:	02 24       	jz	$+6      	;abs 0xcba0
    cb9c:	7c d0 0c 00 	bis.b	#12,	r12	;#0x000c
    cba0:	3b b0 20 00 	bit	#32,	r11	;#0x0020
    cba4:	02 24       	jz	$+6      	;abs 0xcbaa
    cba6:	7c d0 30 00 	bis.b	#48,	r12	;#0x0030
    cbaa:	3b f0 10 00 	and	#16,	r11	;#0x0010
    cbae:	04 24       	jz	$+10     	;abs 0xcbb8
    cbb0:	4b 4c       	mov.b	r12,	r11	
    cbb2:	7b d0 c0 ff 	bis.b	#-64,	r11	;#0xffc0
    cbb6:	01 3c       	jmp	$+4      	;abs 0xcbba
    cbb8:	4b 4c       	mov.b	r12,	r11	
    cbba:	46 93       	tst.b	r6		
    cbbc:	02 24       	jz	$+6      	;abs 0xcbc2
    cbbe:	7b 50 80 ff 	add.b	#-128,	r11	;#0xff80
    cbc2:	0c 49       	mov	r9,	r12	
    cbc4:	0c 5c       	rla	r12		
    cbc6:	0c 5c       	rla	r12		
    cbc8:	0c 5c       	rla	r12		
    cbca:	0c 5c       	rla	r12		
    cbcc:	0c 5c       	rla	r12		
    cbce:	5c 4c 0f 02 	mov.b	527(r12),r12	;0x020f(r12)
    cbd2:	3c b0 80 00 	bit	#128,	r12	;#0x0080
    cbd6:	0c 43       	clr	r12		
    cbd8:	0c 6c       	rlc	r12		
    cbda:	4c 93       	tst.b	r12		
    cbdc:	05 24       	jz	$+12     	;abs 0xcbe8
    cbde:	4f 4b       	mov.b	r11,	r15	
    cbe0:	3f d0 00 01 	bis	#256,	r15	;#0x0100
    cbe4:	b0 12 70 c1 	call	#0xc170	
    cbe8:	4f 4b       	mov.b	r11,	r15	
    cbea:	3f d0 00 01 	bis	#256,	r15	;#0x0100
    cbee:	b0 12 70 c1 	call	#0xc170	
    cbf2:	18 53       	inc	r8		
    cbf4:	38 90 06 00 	cmp	#6,	r8	;#0x0006
    cbf8:	74 23       	jnz	$-278    	;abs 0xcae2
    cbfa:	36 41       	pop	r6		
    cbfc:	37 41       	pop	r7		
    cbfe:	38 41       	pop	r8		
    cc00:	39 41       	pop	r9		
    cc02:	3a 41       	pop	r10		
    cc04:	3b 41       	pop	r11		
    cc06:	30 41       	ret			

0000cc08 <vt100_refresh>:
    cc08:	0b 12       	push	r11		
    cc0a:	0a 12       	push	r10		
    cc0c:	09 12       	push	r9		
    cc0e:	0b 43       	clr	r11		
    cc10:	49 4b       	mov.b	r11,	r9	
    cc12:	0e 4b       	mov	r11,	r14	
    cc14:	0e 5e       	rla	r14		
    cc16:	0e 5e       	rla	r14		
    cc18:	0e 5e       	rla	r14		
    cc1a:	0e 5e       	rla	r14		
    cc1c:	0e 5e       	rla	r14		
    cc1e:	0a 4e       	mov	r14,	r10	
    cc20:	3a 50 0e 02 	add	#526,	r10	;#0x020e
    cc24:	fa b0 10 00 	bit.b	#16,	1(r10)	;#0x0010, 0x0001(r10)
    cc28:	01 00 
    cc2a:	0d 43       	clr	r13		
    cc2c:	0d 6d       	rlc	r13		
    cc2e:	4d 93       	tst.b	r13		
    cc30:	2c 24       	jz	$+90     	;abs 0xcc8a
    cc32:	0f 4b       	mov	r11,	r15	
    cc34:	3f d0 b0 00 	bis	#176,	r15	;#0x00b0
    cc38:	b0 12 70 c1 	call	#0xc170	
    cc3c:	0f 43       	clr	r15		
    cc3e:	b0 12 70 c1 	call	#0xc170	
    cc42:	3f 40 18 00 	mov	#24,	r15	;#0x0018
    cc46:	b0 12 70 c1 	call	#0xc170	
    cc4a:	fa f0 ef ff 	and.b	#-17,	1(r10)	;#0xffef, 0x0001(r10)
    cc4e:	01 00 
    cc50:	4a 43       	clr.b	r10		
    cc52:	06 3c       	jmp	$+14     	;abs 0xcc60
    cc54:	4d 43       	clr.b	r13		
    cc56:	4e 4a       	mov.b	r10,	r14	
    cc58:	4f 49       	mov.b	r9,	r15	
    cc5a:	b0 12 ce ca 	call	#0xcace	
    cc5e:	5a 53       	inc.b	r10		
    cc60:	4c 4a       	mov.b	r10,	r12	
    cc62:	0d 4b       	mov	r11,	r13	
    cc64:	0d 5d       	rla	r13		
    cc66:	0d 5d       	rla	r13		
    cc68:	0d 5d       	rla	r13		
    cc6a:	0d 5d       	rla	r13		
    cc6c:	0d 5d       	rla	r13		
    cc6e:	5d 4d 0f 02 	mov.b	527(r13),r13	;0x020f(r13)
    cc72:	3d b0 80 00 	bit	#128,	r13	;#0x0080
    cc76:	0d 43       	clr	r13		
    cc78:	0d 6d       	rlc	r13		
    cc7a:	4d 93       	tst.b	r13		
    cc7c:	02 24       	jz	$+6      	;abs 0xcc82
    cc7e:	3e 42       	mov	#8,	r14	;r2 As==11
    cc80:	02 3c       	jmp	$+6      	;abs 0xcc86
    cc82:	3e 40 10 00 	mov	#16,	r14	;#0x0010
    cc86:	0c 9e       	cmp	r14,	r12	
    cc88:	e5 3b       	jl	$-52     	;abs 0xcc54
    cc8a:	1b 53       	inc	r11		
    cc8c:	3b 92       	cmp	#8,	r11	;r2 As==11
    cc8e:	c0 23       	jnz	$-126    	;abs 0xcc10
    cc90:	39 41       	pop	r9		
    cc92:	3a 41       	pop	r10		
    cc94:	3b 41       	pop	r11		
    cc96:	30 41       	ret			

0000cc98 <vt100_setting_load>:
    cc98:	30 41       	ret			

0000cc9a <vt100_setting_save>:
    cc9a:	30 41       	ret			

0000cc9c <vt100_keypad_appmode>:
    cc9c:	d2 d3 18 03 	bis.b	#1,	&0x0318	;r3 As==01
    cca0:	30 41       	ret			

0000cca2 <vt100_keypad_nummode>:
    cca2:	f2 f0 fe ff 	and.b	#-2,	&0x0318	;#0xfffe
    cca6:	18 03 
    cca8:	30 41       	ret			

0000ccaa <vt100_set_horizontal_tabulation>:
    ccaa:	30 41       	ret			

0000ccac <vt100_to_reset_state>:
    ccac:	30 41       	ret			

0000ccae <vt100_set_topbottom_margin>:
    ccae:	30 41       	ret			

0000ccb0 <vt100_invoke_confidence_test>:
    ccb0:	30 41       	ret			

0000ccb2 <__umulqihi3>:
    ccb2:	4e 4e       	mov.b	r14,	r14	
    ccb4:	4f 4f       	mov.b	r15,	r15	
    ccb6:	30 40 ba cc 	br	#0xccba	

0000ccba <__mulhi3>:
    ccba:	0d 4f       	mov	r15,	r13	
    ccbc:	0f 43       	clr	r15		
    ccbe:	0e 93       	tst	r14		
    ccc0:	07 24       	jz	$+16     	;abs 0xccd0
    ccc2:	12 c3       	clrc			
    ccc4:	0d 10       	rrc	r13		
    ccc6:	01 28       	jnc	$+4      	;abs 0xccca
    ccc8:	0f 5e       	add	r14,	r15	
    ccca:	0e 5e       	rla	r14		
    cccc:	0d 93       	tst	r13		
    ccce:	f7 23       	jnz	$-16     	;abs 0xccbe
    ccd0:	30 41       	ret			

0000ccd2 <_unexpected_>:
    ccd2:	00 13       	reti			

Disassembly of section .vectors:

0000ffe0 <__ivtbl_16>:
    ffe0:	66 c0 66 c0 66 c0 66 c0 66 c0 66 c0 66 c0 8a c0     f.f.f.f.f.f.f...
    fff0:	66 c0 c8 c7 66 c0 66 c0 66 c0 66 c0 66 c0 00 c0     f...f.f.f.f.f...
