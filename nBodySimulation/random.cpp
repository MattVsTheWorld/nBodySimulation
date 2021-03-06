#include<ctime>
#include<cstdlib>


// Function to seed the random number generator  ensures 
// unpredictable random numbers...
void start_random()
{
	static bool seeded = false;
	if (!seeded) {
		srand((unsigned)time(NULL));
		seeded = true;
	}
}

// Generate a random float in the range -1 to +1...
float rnd() {
	start_random();
	return (-1) + (float)rand() / 16384;
}

// Generate a random float in the specified range...
float rnd(float rangemin, float rangemax) {
	start_random();
	return rangemin + (float)rand()*(rangemax - rangemin) / 32768.0;
}

// Generate a random integer in the specified range(0..range-1)...
int rnd(int range) {
	start_random();
	return rand() % range;
}