
//Display 7 Segmentos Catodo Común
// int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

//Display 7 Segmentos Anodo Común
int display7a[10]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};

// Pin pulsador
byte pulsadorPin=0;

//Delcaración de Los Pines del Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;

// Declaración de los Pines de los Transistores
byte t1=9;
byte t2=10;
byte t3=11;
byte t4=12;
byte leds =13;

//Contadores para hacer el Temporizador
long temporM=0,temporm=0, temporS=0, tempors=0, contret=0;

// Tres estados: 0, Inicio00quieto. 1, Corriendo. 2, Parado.
int estadoCrono = 0;


//Función que coloca en el puerto de salida los bits comenzando
// desde el pin ini hasta el pin fin
void puerto(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}

//Función encargada de la multiplexación
void mostrar(){
   int dig[4];   
   dig[0]=temporM;
   dig[1]=temporm;
   dig[2]=temporS;
   dig[3]=tempors;
   
   //Rutina de Multiplexación
   for(int i=t1;i<=t4;i++){ 
     //Muestra unidades
     puerto(display7a[dig[i-t1]],a,g); 
     // Primero debe ser low y luego high por el tipo de transistor pnp
     digitalWrite(i,LOW); //ciende el display de unidades
     delay(1);               //Retardo de 1 milisegundos
     digitalWrite(i,HIGH);//paga el display de unidades
   }                      
}

//Función que cuenta el tiempo que le toma al temporizador
//incrementar su cuenta
void temporizacion() 
{
  contret=69;       
  while (contret>0) 
  {
    mostrar();
    // IMPORTANTE
    delay(10);
    contret--;
    }
}


void setup() {
  pinMode(pulsadorPin, INPUT_PULLUP); //Pin 0 en rx
  for(int i=a;i<=t4;i++){
    pinMode(i,OUTPUT);
    pinMode (leds,OUTPUT);
    }
}


void loop() {
  digitalWrite(leds,HIGH);

  // El valor del pulsador es = 0 cuando se presiona el boton
  int valorPulsador = digitalRead(pulsadorPin);

  if (estadoCrono == 0){

    while (valorPulsador != 0){
      temporizacion();
      valorPulsador = digitalRead(pulsadorPin);
      
    }
    estadoCrono = 1;
  }
  
  if(estadoCrono == 1) {
    tempors=0;  
    while(tempors<10){
      temporizacion(); 
      tempors++;
      valorPulsador = digitalRead(pulsadorPin);
      if (valorPulsador == 0){
        estadoCrono = 2;
        break;
      }       
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
  
}
