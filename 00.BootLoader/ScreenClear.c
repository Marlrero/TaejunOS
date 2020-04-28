void main() {
	int i = 0;
	char* pcVideoMemory = (char*) 0xB8000; // 비디오 메모리 주소를 가리킴

	while (1) {
		pcVideoMemory[i] = 0; // 화면에 있는 문자들을 0으로 초기화 (지움)
		pcVideoMemory[i + 1] = 0x0A; // 화면에 있는 문자들의 배경색을 초록색으로 초기화

		i += 2;

		if (i >= 80 * 25 * 2) // 가로 문자 80, 세로 문자 25, 화면 크기 2 = 4000바이트이면 멈춤
			break;
	}
}

/*
 * 어셈블리 코드로 오브젝트 파일을 변환한 내용 (Intel Style)
 * 최적화 단계는 gcc 옵션에 -O2
taejun@ubuntu:~/coding/MINT64_1/00.BootLoader$ objdump -M intel -d ScreenClear.o
ScreenClear.o:     file format elf64-x86-64


Disassembly of section .text.startup:

0000000000000000 <main>:
                                // char* pcVideoMemory = (char*) 0xB8000;
   0:	b8 00 80 0b 00       	mov    eax,0xb8000              // 상수 (char*) 0xB8000를 eax 레지스터에 복사
   5:	0f 1f 00             	nop    DWORD PTR [rax]          // no-operation (CPU 동작이 없음)
   	   	   	   	   	   	   	   	   	   	   	   	                // DWORD PTR은 4바이트 단위로 접근하겠다는 의미. rax 레지스터를.
   	   	   	   	   	   	   	    // int i = 0;
   8:	c6 00 00             	mov    BYTE PTR [rax],0x0       // BYTE PTR은 1바이트 단위로 접근하겠다는 의미. rax 레지스터에 0바이트 초기화

   	   	   	   	   	   	        // i += 2;
   b:	48 83 c0 02          	add    rax,0x2

   	   	   	   	                // pcVideoMemory[i] = 0; // 화면에 있는 문자들을 0으로 초기화 (지움)
		                        // pcVideoMemory[i + 1] = 0x0A; // 화면에 있는 문자들의 배경색을 초록색으로 초기화
		                        // 컴파일러 최적화가 일어난 부분
   f:	c6 40 ff 0a          	mov    BYTE PTR [rax-0x1],0xa // rax에서 1만큼 감소한 곳에서 1바이트를 0xA로 초기화하라는 의미

   	   	   	   	   	   	   	    // 	if (i >= 80 * 25 * 2) break; // rax와 0xb8fa0
  13:	48 3d a0 8f 0b 00    	cmp    rax,0xb8fa0  // fa0 == 4000 -> 0xb8000 + 0xb8fa0 (0xb8000에서 4000 bytes)
  19:	75 ed                	jne    8 <main+0x8> // rax 레지스터의 값과 0xb8fa0 값을 비교해서, not equal이면 8번째 줄로 감
  1b:	c3                   	ret                 // return

 */
