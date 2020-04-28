int main(int argc, char* argv[]) {
	int iTotalSectorCount = 1024;
	int iSectorNumber = 2;
	int iHeadNumber = 0;
	int iTrackNumber = 0;

	// 실제 이미지를 복사할 물리 어드레스
	char* pcTargetAddress = (char*) 0x10000;

	while (1) {
		// 전체 섹터 수를 하나씩 감소하면서 0이 될 때까지 섹터를 복사한다.
		if (iTotalSectorCount == 0) {
			break; // 종료 조건
		}

		iTotalSectorCount--;

		// 1 섹터를 읽어들여서 메모리에 복사한다.
		if (BIOSReadOneSector(iSectorNumber, iHeadNumber,
				              iTrackNumber, pcTargetAddress) == ERROR) { // BIOS의 섹터 읽기 기능을 호출하는 임의의 함수
			HandleDiskError();
		}

		// 1 섹터는 512(0x200) 바이트이므로, 복사한 섹터 수만큼 어드레스는 증가해야 함
		pcTargetAddress = pcTargetAddress + 0x200;

		// 섹터 -> 헤드 -> 트랙 순으로 번호는 증가해야 한다.
		iSectorNumber++;
		if (iSectorNumber < 19) { // 섹터는 0 ~ 18의 값을 가지는 19개의 섹터를 가진다.
			continue;
		}

		iHeadNumber = iHeadNumber ^ 0x01; // 헤드는 0과 1이 반복되므로, XOR 연산으로 이를 편리하게 처리함
		// 위 코드를 아래와 같이 바꿔도 됨
		// iHeadNumber = (iHeadNumber == 0x00) ? 0x01 : 0x00;

		if (iHeadNumber != 0) {
			continue;
		}

		iTrackNumber++;
	}

	return 0;
}

void HandleDiskError() { // 발생한 에러를 처리하는 함수
	print("Disk Error!");
	while (1);
}
