/* 
   M27C1001 EPROM reader (http://www.st.com/web/en/resource/technical/document/datasheet/CD00000511.pdf)
   tested on Arduino Due with M27C1001-70XF1 
   Vcc = 3.3v (Max ratings are -2/7V)
   Vpp = 3.3v or GROUND
   Vss = GROUND
   
   PIN 30-46 Address (A0-A16)
   PIN 2-9   Data (Q0-Q7)
   PIN 22    Chip Enable (active when low) (/E)
   PIN 24    Output Enable (active when low) (/G)
   
   PIN 50    Trigger (Push button)
   
   command: minicom -D /dev/ttyXXXN -b 115200 -C dump_file
 */

const int epromSize = 131071;

int startDump = 0;
int buttonStart = 50;
int ChipEnable = 22;
int OutputEnable = 24;
int AddressPins[] = {30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46};
int DataPins[] = {2,3,4,5,6,7,8,9};
int address = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  pinMode(buttonStart, INPUT);     

  for (int i=0; i<17; i++) {
    pinMode(AddressPins[i], OUTPUT);
    digitalWrite(AddressPins[i], LOW);
  }
  for (int i=0; i<8; i++) {
    pinMode(DataPins[i], INPUT);
  }
  pinMode(ChipEnable, OUTPUT);
  pinMode(OutputEnable, OUTPUT);
  digitalWrite(ChipEnable, LOW);
  digitalWrite(OutputEnable, LOW);
  
}

void loop() {
  char ret = 0x00000;

  if(digitalRead(buttonStart) == HIGH)
    startDump = 1;
  
  if(startDump == 0){
    return;
  }
  if(address >= epromSize){
    Serial.end();
    return;
  }
  
  for (int i=1, j = 0; i<=address; i=i<<1, j++)
    digitalWrite(AddressPins[j],address & i);
  
  //Address Valid to Output Valid should take only 70ns
  delayMicroseconds(1);

  for (int i=0; i<8; i++) 
    if( digitalRead(DataPins[i]) == HIGH) 
      ret |= (1<<i);
    
  Serial.write(ret);
  Serial.flush();
  address++;
}
