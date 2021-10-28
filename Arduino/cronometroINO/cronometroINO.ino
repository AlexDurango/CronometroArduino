
//Display 7 Segmentos Catodo Común
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
//Display 7 Segmentos Anodo Común
// int display7a[10]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};

byte botonInicio = 0;
byte botonFinal = 1;
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

//Contadores para hacer el Temporizador
long tempor=0,contret=0;


//Función que coloca en el puerto de salida los bits comenzando
// desde el pin ini hasta el pin fin
void puerto(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}


//Función encargada de la multiplexación
void mostrar() //Rutina mostrar
{
   int dig[4];   //Declarar las variables
                 //como un entero, es decir de 8bits
   //Dígito Millar
   dig[0]=tempor/1000;
   //Dígito Centena
   dig[1]=(tempor-dig[0]*1000)/100;
   //Dígito Decena
   dig[2]=(tempor-dig[0]*1000-dig[1]*100)/10;
   //Dígito Unidad
   dig[3]=(tempor-dig[0]*1000-dig[1]*100-dig[2]*10);
   //Rutina de Multiplexación
   for(int i=t1;i<=t4;i++){ 
     //Muestra unidades
     puerto(display7c[dig[i-t1]],a,g); 
     digitalWrite(i,HIGH);  //Enciende el display de unidades
     delay(1);               //Retardo de 1 milisegundos
     digitalWrite(i,LOW);   //Apaga el display de unidades
   }                      
}

void finalizarTimer() {
	int dig[4];   //Declarar las variables
                 //como un entero, es decir de 8bits
   //Dígito Millar
   dig[0]=tempor/1000;
   //Dígito Centena
   dig[1]=(tempor-dig[0]*1000)/100;
   //Dígito Decena
   dig[2]=(tempor-dig[0]*1000-dig[1]*100)/10;
   //Dígito Unidad
   dig[3]=(tempor-dig[0]*1000-dig[1]*100-dig[2]*10);
   //Rutina de Multiplexación
   for(int i=t1;i<=t4;i++){ 
     //Muestra unidades
     puerto(display7c[dig[i-t1]],a,g); 
     digitalWrite(i,HIGH);  //Enciende el display de unidades
     delay(100);               //Retardo de 100 milisegundos para que se vea el tiempo.
     digitalWrite(i,LOW);
  
   }     
}

//Función que cuenta el tiempo que le toma al temporizador
//incrementar su cuenta
void temporizacion() 
{
   contret=50;       //Cargue con 50 la variable CONTRET
   while (contret>0) //Mientras que la variable CONTRET sea mayor que cero
   {
      mostrar();        //Llamar la rutina MOSTRAR
      contret--;        // Decremente la variable CONTRET
   }
}

//Configura todos los pines como Salidas
void setup() {

  // Configurar la entrada de los botones
  pinMode(botonInicio, INPUT);
  pinMode(botonFinal, INPUT);

  //Configura los 8 Pines digitales como SALIDAS
  for(int i=a;i<=t4;i++){
    pinMode(i,OUTPUT);
  }
}

//Programa Principal
void loop() {

	int inicioValue = analogRead(botonInicio);

	if(inicioValue == HIGH) {
		tempor=0;  //Inicializa el temporizador en Cero
    	while(tempor<9999) //mientras la variable TEMPOR es menor que 9999
    	{
			int finalValue = analogRead(botonFinal);
			if (finalValue == HIGH) {
				finalizarTimer();
				break;
			}
			else {
				temporizacion(); //Llama la Función Temporizaor
				tempor++;        //Incrementa el tempor 
			}
    	}
	}
	
}