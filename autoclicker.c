#include <stdio.h>
#include <time.h>
#include <windows.h>

int main() {
	//INPUT struct
	INPUT pInputs[2] = {};
	ZeroMemory(pInputs, sizeof(pInputs));

	pInputs[0].type = INPUT_MOUSE;
	pInputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	pInputs[1].type = INPUT_MOUSE;
	pInputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	// nanosleep
	struct timespec tim, tim2;

	printf("frequency (clicks/s)? ");
	int freq;
	scanf("%d", &freq);
	float interval = (float) 1/freq;
	tim.tv_sec = (int) interval;
	tim.tv_nsec = (interval - (int) interval) * 1000000000;	

	// prompt timer or indefinite mode 
	printf("should the autoclicker go indefinitely or be on a timer (0 for indefinite, 1 for timer)? ");
	int choice;
	scanf("%d", &choice);

	if (choice == 0) {
		// simulated lmb presses
		printf("\nstarting autoclicker, ctrl + alt + del if you want to kill early\n");
		while (1) {
			nanosleep(&tim, &tim2);
			UINT uSent = SendInput(2, pInputs, sizeof(INPUT));
		}
	} else if (choice == 1) {
		printf("how much time (seconds)? ");
		int sec;
		scanf("%d", &sec);

		// simulated lmb presses
		printf("\nstarting autoclicker, ctrl + alt + del if you want to kill early\n");
		clock_t start = clock();
		while (1) {
			nanosleep(&tim, &tim2);
			UINT uSent = SendInput(2, pInputs, sizeof(INPUT));
			if (sec <= (clock() - start) / CLOCKS_PER_SEC) {
				printf("\nbreaking...");
				break;
			}
		}
	}

	return 0;
}
