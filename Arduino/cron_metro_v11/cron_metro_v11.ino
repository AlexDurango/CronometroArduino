
int display7a[10]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;

byte t1=9;
byte t2=10;
byte t3=11;
byte t4=12;
int leds=13;
long temporM=0,temporm=0, temporS=0, tempors=0, contret=0;
void puerto(int bits,int ini,int fin){
for(int i=ini;i<=fin;i++)
{
digitalWrite(i,bitRead(bits,i-ini));
}
}
void mostrar( ) 
{
int dig[4];   
dig[0]=temporM;
dig[1]=temporm;
dig[2]=temporS;
dig[3]=tempors;

for(int i=t1;i<=t4;i++){ 

puerto(display7a[dig[i-t1]],a,g); 
digitalWrite(i,LOW);  
delay(1);               
digitalWrite(i,HIGH);   
}                      
}

void temporizacion() 
{
contret=69;       
while (contret>0) 
{
mostrar();
// Importante
delay(10);       
contret--;       
}
}

void setup() {

for(int i=a;i<=t4;i++){
pinMode(i,OUTPUT);
  pinMode (leds,OUTPUT);
}
}
void loop() {
  digitalWrite(leds,HIGH);
tempors=0;  
while(tempors<10)
{
temporizacion(); 
tempors++;       
}
if (tempors==10){
  tempors=0;
  temporS++;
}
if (temporS==6){
  temporS=0;
  temporm++;
}
if (temporm==10){
  temporm=0;
  temporM++;
}
}
