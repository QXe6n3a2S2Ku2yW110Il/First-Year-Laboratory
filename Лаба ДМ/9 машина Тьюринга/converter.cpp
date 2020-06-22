#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::string s;
	double sum = 0;
	int cnt = 0;
	while (std::cin >> s) {
		if (s[0] == 'M' || s[0] == 'М') {
			if ('0' <= s[1] && s[1] <= '9') {
				std::cin >> s;
				int abstract;
				double real;
				std::cin >> abstract >> real;
				sum += abstract / real;
				++cnt;
			}
		}
	}

	std::cout << sum / cnt;

    return 0;
}