#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory.h>
#include <limits>
#include <bitset>
#include <string>

#define INF 987654321

void prob()
{
	int sh, sm, eh, em, dh, dm, ch, cm;
	int s, e, d, c;
	scanf("%2d:%2d %2d:%2d %2d:%2d %2d:%2d", &sh, &sm, &eh, &em, &dh, &dm, &ch, &cm);
	s = sh * 60 + sm;
	e = eh * 60 + em;
	d = dh * 60 + dm;
	c = ch * 60 + cm;

	int min_ste;
	int min_cir;

	min_ste = (e - s) / d + 1;
	min_cir = c / d;
	if (c % d != 0)
		min_cir++;

	int min = std::min(min_ste, min_cir);

	printf("%d\n", min);
	
}

int main() {

	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		prob();
	return 0;
}