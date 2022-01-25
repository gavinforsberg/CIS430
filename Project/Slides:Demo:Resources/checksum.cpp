#include <iostream>
using namespace std;

unsigned short chksum(unsigned short *buf, int count) {
	unsigned long sum = 0;

	while(count--) {
		sum += *buf++;
		if(sum & 0xFFFF0000) {
			/* carry occurreed, so swap around */
			sum &= 0xFFFF;
			sum++;
		}
	}
	return ~(sum & 0xFFFF);
}

int main() {
	unsigned short input[] = {1, 2, 3, 4, 5};

	unsigned short checksum =  chksum(input, 5);

	cout << "0x" << hex << checksum << endl;

	return 0;
}
