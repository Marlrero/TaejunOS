void main() {
	int i = 0;
	int j = 0;
	char* pcVideoMemory = (char*)0xB8000; // 비디오 메모리 주소
	char* pcMessage = "Taejun OS Boot Loader Start~~"; // 출력할 메시지
	char cTemp;

	while (1) {
		cTemp = pcMessage[i];

		if (cTemp == 0) // 널 문자일 때까지 반복
			break;

		pcVideoMemory[j] = cTemp;

		i += 1; // 1칸씩 (문자열 상수에 대해 한 문자씩)
		j += 2; // 2칸씩 (비디오 메모리 주소에 대해)
	}
}

/*
taejun@ubuntu:~/coding/MINT64_1/00.BootLoader$ gcc -c PrintMessage.c -o PrintMessage.o -O2
taejun@ubuntu:~/coding/MINT64_1/00.BootLoader$ objdump -M intel -d PrintMessage.o

PrintMessage.o:     file format elf64-x86-64


Disassembly of section .text.startup:

0000000000000000 <main>:
   0:	48 8d 0d 00 00 00 00 	lea    rcx,[rip+0x0]        # 7 <main+0x7>
   7:	ba 00 80 0b 00       	mov    edx,0xb8000
   c:	b8 54 00 00 00       	mov    eax,0x54

  11:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

  18:	88 02                	mov    BYTE PTR [rdx],al
  1a:	0f b6 01             	movzx  eax,BYTE PTR [rcx]

  1d:	48 83 c2 02          	add    rdx,0x2
  21:	48 83 c1 01          	add    rcx,0x1
  25:	84 c0                	test   al,al
  27:	75 ef                	jne    18 <main+0x18>
  29:	c3                   	ret
taejun@ubuntu:~/coding/MINT64_1/00.BootLoader$
 */
