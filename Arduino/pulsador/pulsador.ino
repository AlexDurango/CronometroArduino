byte pul=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pul, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valor = digitalRead(pul);
  if(valor==0){
    Serial.println("AHHHHH");
    
  }

}
