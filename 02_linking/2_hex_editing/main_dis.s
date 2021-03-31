
main:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	pushq  0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmpq *0x2f9b(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmpq *0x2fad(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <printf@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmpq *0x2f75(%rip)        # 3fd0 <printf@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    %ebp,%ebp
    1066:	49 89 d1             	mov    %rdx,%r9
    1069:	5e                   	pop    %rsi
    106a:	48 89 e2             	mov    %rsp,%rdx
    106d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1071:	50                   	push   %rax
    1072:	54                   	push   %rsp
    1073:	4c 8d 05 a6 01 00 00 	lea    0x1a6(%rip),%r8        # 1220 <__libc_csu_fini>
    107a:	48 8d 0d 2f 01 00 00 	lea    0x12f(%rip),%rcx        # 11b0 <__libc_csu_init>
    1081:	48 8d 3d c1 00 00 00 	lea    0xc1(%rip),%rdi        # 1149 <main>
    1088:	ff 15 52 2f 00 00    	callq  *0x2f52(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    108e:	f4                   	hlt    
    108f:	90                   	nop

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    0x2f72(%rip),%rax        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    %rdi,%rax
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 2e 2f 00 00 	mov    0x2f2e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    10aa:	48 85 c0             	test   %rax,%rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmpq   *%rax
    10b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10b8:	c3                   	retq   
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    %rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmpq   *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	retq   
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4010 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   %rbp
    110e:	48 83 3d e2 2e 00 00 	cmpq   $0x0,0x2ee2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    %rsp,%rbp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	callq  1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	callq  1090 <deregister_tm_clones>
    112c:	c6 05 dd 2e 00 00 01 	movb   $0x1,0x2edd(%rip)        # 4010 <__TMC_END__>
    1133:	5d                   	pop    %rbp
    1134:	c3                   	retq   
    1135:	0f 1f 00             	nopl   (%rax)
    1138:	c3                   	retq   
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmpq   10c0 <register_tm_clones>

0000000000001149 <main>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	48 83 ec 10          	sub    $0x10,%rsp
    1155:	bf 0a 00 00 00       	mov    $0xa,%edi
    115a:	e8 20 00 00 00       	callq  117f <increment>
    115f:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1162:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1165:	89 c6                	mov    %eax,%esi
    1167:	48 8d 3d 96 0e 00 00 	lea    0xe96(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    116e:	b8 00 00 00 00       	mov    $0x0,%eax
    1173:	e8 d8 fe ff ff       	callq  1050 <printf@plt>
    1178:	b8 00 00 00 00       	mov    $0x0,%eax
    117d:	c9                   	leaveq 
    117e:	c3                   	retq   

000000000000117f <increment>:
    117f:	f3 0f 1e fa          	endbr64 
    1183:	55                   	push   %rbp
    1184:	48 89 e5             	mov    %rsp,%rbp
    1187:	89 7d fc             	mov    %edi,-0x4(%rbp)
    118a:	8b 45 fc             	mov    -0x4(%rbp),%eax
    118d:	83 c0 01             	add    $0x1,%eax
    1190:	5d                   	pop    %rbp
    1191:	c3                   	retq   

0000000000001192 <decrement>:
    1192:	f3 0f 1e fa          	endbr64 
    1196:	55                   	push   %rbp
    1197:	48 89 e5             	mov    %rsp,%rbp
    119a:	89 7d fc             	mov    %edi,-0x4(%rbp)
    119d:	8b 45 fc             	mov    -0x4(%rbp),%eax
    11a0:	83 e8 01             	sub    $0x1,%eax
    11a3:	5d                   	pop    %rbp
    11a4:	c3                   	retq   
    11a5:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    11ac:	00 00 00 
    11af:	90                   	nop

00000000000011b0 <__libc_csu_init>:
    11b0:	f3 0f 1e fa          	endbr64 
    11b4:	41 57                	push   %r15
    11b6:	4c 8d 3d fb 2b 00 00 	lea    0x2bfb(%rip),%r15        # 3db8 <__frame_dummy_init_array_entry>
    11bd:	41 56                	push   %r14
    11bf:	49 89 d6             	mov    %rdx,%r14
    11c2:	41 55                	push   %r13
    11c4:	49 89 f5             	mov    %rsi,%r13
    11c7:	41 54                	push   %r12
    11c9:	41 89 fc             	mov    %edi,%r12d
    11cc:	55                   	push   %rbp
    11cd:	48 8d 2d ec 2b 00 00 	lea    0x2bec(%rip),%rbp        # 3dc0 <__do_global_dtors_aux_fini_array_entry>
    11d4:	53                   	push   %rbx
    11d5:	4c 29 fd             	sub    %r15,%rbp
    11d8:	48 83 ec 08          	sub    $0x8,%rsp
    11dc:	e8 1f fe ff ff       	callq  1000 <_init>
    11e1:	48 c1 fd 03          	sar    $0x3,%rbp
    11e5:	74 1f                	je     1206 <__libc_csu_init+0x56>
    11e7:	31 db                	xor    %ebx,%ebx
    11e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    11f0:	4c 89 f2             	mov    %r14,%rdx
    11f3:	4c 89 ee             	mov    %r13,%rsi
    11f6:	44 89 e7             	mov    %r12d,%edi
    11f9:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    11fd:	48 83 c3 01          	add    $0x1,%rbx
    1201:	48 39 dd             	cmp    %rbx,%rbp
    1204:	75 ea                	jne    11f0 <__libc_csu_init+0x40>
    1206:	48 83 c4 08          	add    $0x8,%rsp
    120a:	5b                   	pop    %rbx
    120b:	5d                   	pop    %rbp
    120c:	41 5c                	pop    %r12
    120e:	41 5d                	pop    %r13
    1210:	41 5e                	pop    %r14
    1212:	41 5f                	pop    %r15
    1214:	c3                   	retq   
    1215:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    121c:	00 00 00 00 

0000000000001220 <__libc_csu_fini>:
    1220:	f3 0f 1e fa          	endbr64 
    1224:	c3                   	retq   

Disassembly of section .fini:

0000000000001228 <_fini>:
    1228:	f3 0f 1e fa          	endbr64 
    122c:	48 83 ec 08          	sub    $0x8,%rsp
    1230:	48 83 c4 08          	add    $0x8,%rsp
    1234:	c3                   	retq   
