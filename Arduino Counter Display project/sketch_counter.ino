const int SEG7_LENGTH = 8;
const int STEP = 1;
const int PATTERNS_COUNT = 10;
int patterns[PATTERNS_COUNT][SEG7_LENGTH];
int index;
int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int delayPeriod = 1000;

// int seg7_[] = {a, b, c, d, e, f, g, dp}; // LOW HIGH
int seg7_0[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int seg7_1[] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int seg7_2[] = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};
int seg7_3[] = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW};
int seg7_4[] = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW};
int seg7_5[] = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int seg7_6[] = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int seg7_7[] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int seg7_8[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int seg7_9[] = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};

int seg7_Blanck[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int seg7_segmenta[] = {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int seg7_segmentb[] = {LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW};
int seg7_segmentc[] = {LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW};
int seg7_segmentd[] = {LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW};
int seg7_segmente[] = {LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW};
int seg7_segmentf[] = {LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW};
int seg7_segmentg[] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW};
int seg7_segmentdp[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH};

void copyIntArray(int src[], int dst[], int count) {
  for(int i = 0; i < count; i++) {
    dst[i] = src[i];
  }  
}

void rotatingSignal(int interval, int totalPeriod, boolean clockWise) {
  const int ROTATING_PATTERNS_COUNT = 6;
  int localPatterns[ROTATING_PATTERNS_COUNT][SEG7_LENGTH];
  copyIntArray(seg7_segmenta, localPatterns[0], SEG7_LENGTH);
  copyIntArray(seg7_segmentb, localPatterns[1], SEG7_LENGTH);
  copyIntArray(seg7_segmentc, localPatterns[2], SEG7_LENGTH);
  copyIntArray(seg7_segmentd, localPatterns[3], SEG7_LENGTH);
  copyIntArray(seg7_segmente, localPatterns[4], SEG7_LENGTH);
  copyIntArray(seg7_segmentf, localPatterns[5], SEG7_LENGTH); 
  int stepping = clockWise? +1: -1;
  boolean moreTime = true;
  int count = 0;
  do {
    count++;
    int i = clockWise? 0: ROTATING_PATTERNS_COUNT-1; 
    while(i < ROTATING_PATTERNS_COUNT && i >= 0) {
      light7seg(localPatterns[i], pins);
      delay(interval);
      i += stepping;
    }
    moreTime = interval*ROTATING_PATTERNS_COUNT*count < totalPeriod;
  } while (moreTime);
}

void light7seg(int values[], int pins[]) {
  for(int i = 0; i < SEG7_LENGTH; i++) {
    digitalWrite(pins[i], values[i]);
  }
}

void pinsSetup() {
  for(int i = 0; i < SEG7_LENGTH; i++) {
    pinMode(pins[i], OUTPUT);
  }  
}

void setup() {
  index = (STEP > 0)? 0: PATTERNS_COUNT-1;
  pinsSetup();
  copyIntArray(seg7_0, patterns[0], SEG7_LENGTH);
  copyIntArray(seg7_1, patterns[1], SEG7_LENGTH);
  copyIntArray(seg7_2, patterns[2], SEG7_LENGTH);
  copyIntArray(seg7_3, patterns[3], SEG7_LENGTH);
  copyIntArray(seg7_4, patterns[4], SEG7_LENGTH);
  copyIntArray(seg7_5, patterns[5], SEG7_LENGTH);
  copyIntArray(seg7_6, patterns[6], SEG7_LENGTH);
  copyIntArray(seg7_7, patterns[7], SEG7_LENGTH);
  copyIntArray(seg7_8, patterns[8], SEG7_LENGTH);
  copyIntArray(seg7_9, patterns[9], SEG7_LENGTH);
}

void loop() {
  rotatingSignal(40, 0, true);
  light7seg(patterns[index], pins);
  delay(delayPeriod);
  index += STEP;
  if(index >= PATTERNS_COUNT) {
    index = 0;
  }
  if(index < 0 ) {
    index = PATTERNS_COUNT-1;
  }
}
