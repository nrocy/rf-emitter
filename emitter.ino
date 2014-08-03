
#define LONG_DELAY_US 876
#define SHORT_DELAY_US 292
#define REPEAT_DELAY_MS 9000
#define REPEAT_NUM 3

#define RF433MHZ_PIN 3

#define CHANNEL_ON 0
#define CHANNEL_OFF 1

#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3
#define CH_ALL_OFF 4

byte prefix[] = {
  0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
};

byte suffix[] = { 1 };

byte channels[][3] = {
  { 0, 0, 0 },
  { 1, 0, 0 },
  { 0, 1, 0 },
  { 0, 0, 1 },
  { 1, 1, 1 }
};

void setup() {
  pinMode(RF433MHZ_PIN, OUTPUT);
}

void sendBit(byte b) {
  if (b == 0) {
    digitalWrite(RF433MHZ_PIN, HIGH);
    delayMicroseconds(LONG_DELAY_US);
    digitalWrite(RF433MHZ_PIN, LOW);
    delayMicroseconds(SHORT_DELAY_US);
  }
  else {
    digitalWrite(RF433MHZ_PIN, HIGH);
    delayMicroseconds(SHORT_DELAY_US);
    digitalWrite(RF433MHZ_PIN, LOW);
    delayMicroseconds(LONG_DELAY_US);
  }
}

void sendSequence(byte channel, byte state) {
  for (byte i = 0; i < sizeof(prefix); i++) {
    sendBit(prefix[i]);
  }

  sendBit(state);

  for (byte i =0; i < sizeof(channels[channel]); i++) {
    sendBit(channels[channel][i]);
  }

  for (byte i = 0; i < sizeof(suffix); i++) {
    sendBit(suffix[i]);
  }
}

void sendRemote(byte channel, byte state) {
  for (byte i = 0; i < REPEAT_NUM; i++) {
    sendSequence(channel, state);
    delayMicroseconds(REPEAT_DELAY_MS);
  }
}

void sendRemoteAllOff() {
  sendRemote(CH_ALL_OFF, CHANNEL_ON);
}

void loop() {
  /*
  delay(2000);
  sendRemote(CH1, CHANNEL_ON);
  delay(2000);
  sendRemote(CH1, CHANNEL_OFF);
  delay(2000);
  sendRemote(CH2, CHANNEL_ON);
  delay(2000);
  sendRemote(CH2, CHANNEL_OFF);
  delay(2000);
  sendRemote(CH3, CHANNEL_ON);
  delay(2000);
  sendRemote(CH3, CHANNEL_OFF);
  delay(2000);
  sendRemote(CH4, CHANNEL_ON);
  delay(2000);
  sendRemote(CH4, CHANNEL_OFF);

  delay(2000);
  sendRemoteAllOff();
  */
}

