/* Contador decimal de dos Digigitos en 7 Segmentos usando multiplexacion
 Por: http://elprofegarcia.com/
 
 Conexiones:  Las conexiones entre el Arduino y el Display deben realizarse
              con una resistencia de 1K ohmio.
 Ver plano en: https://www.dropbox.com/s/7xdksbf0cy36ji8/plano%20conexion%20arduino%207seg%2000-99.jpg?dl=0
 
 ARDUINO  -    Display 7 Segmentos (catodo comun)
   2            a
   3            b
   4            c
   5            d
   6            e
   7            f
   8            g
   9            P
   
   10           COM digito izquierdo usando Transistor NPN
   11           COM digito derecho  usando Transistor NPN
 Sitio donde se compro todos los componentes: http://dinastiatecnologica.com/producto/display-7-segmentos-doble/
*/

int retardo=10;       // tiempo que dura encendido cada 7 seg (10 mili segundos)
int var=0;            // Valor del digito que se va a desplegar por el 7 seg.

int unidad=0;         // cuenta las unidades (derecha)
int decena=0;         // cuenta las decenas (izquierda)
int conmutador=0;     // multiplexacion de uno a otro 7 segmentos
int cont=0;           // contador de ciclos de espera para cambiar de numero

int estadoCrono = 0;

void cambiarEstado () {

  switch (estadoCrono) {

    case 0:
      estadoCrono = 1;
      delay(150);
      break;

    case 1:
      estadoCrono = 2;
      delay(150);
      break;

    case 2:
      estadoCrono = 0;
      var = 0;
      unidad = 0;
      decena = 0;
      delay(150);
      break;

    default:
      estadoCrono = 0;
    
    }

}

void contar() {
  cont++;                      // incrementa el contador de ciclos en Uno
 if (cont==100){              // cada cuanto tiempo (ciclos)cambia un numero
      cont=0;                 // inicializa el contador de ciclos   
    unidad=unidad+1;          // incrementa la unidad, primer 7seg
    if (unidad >= 10){        // cuando la unidad llegue a 10 incrementa la decena 
        decena=decena+1;      // incrementa la decena,  segundo 7seg
        if (unidad == 10 && decena == 10){
          unidad = 9;
          decena = 9;
          return;
          }
      unidad=0;               // regresa la unidad a cero
      if (decena>=10){        // cuando la decena llegue a 10 se inicializa a cero    
       decena=0; 
      }      
    }
 } 
  
}

void multiplexar () {
  if (conmutador == 0) {    // hace la multiplexacion conmutando entre los dos 7seg  izq y der
      digitalWrite(10, 0);    // enciende el derecho
      digitalWrite(11, 1);    // apaga el izquierdo
     
      var=unidad;             // iguala la variable que escribe el numero en el 7seg al valor de la unidad
      conmutador=1;           // cambia el conmutador para que en el siguiente ciclo cumpla la otra condicion
      
    }
    else{
     digitalWrite(10, 1);       // apaga el derecho
      digitalWrite(11, 0);      // enciende el izquierdo
      var=decena;               // iguala la variable que escribe el numero en el 7seg al valor de la decena
      conmutador=0;             // cambia el conmutador para que en el siguiente ciclo cumpla la otra condicion
      
    }
}

void mostrar() {
  switch (var) {
    case 1:                 //escribe en el 7seg el numero 1
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
     break;
    case 2:                //escribe en el 7seg el numero 2
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 1);
      digitalWrite(8, 0);
     break;      
    case 3:               //escribe en el 7seg el numero 3
       digitalWrite(2, 0);
       digitalWrite(3, 0);
       digitalWrite(4, 0);
       digitalWrite(5, 0);
       digitalWrite(6, 1);
       digitalWrite(7, 1);
       digitalWrite(8, 0);
      break;
    case 4:               //escribe en el 7seg el numero 4
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
     break;
    case 5:               //escribe en el 7seg el numero 5
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
     break;
    case 6:               //escribe en el 7seg el numero 6
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
     break;
    case 7:              //escribe en el 7seg el numero 7
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
     break;
    case 8:              //escribe en el 7seg el numero 8
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      break;
    case 9:               //escribe en el 7seg el numero 9
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
     break;
    case 0:                //escribe en el 7seg el numero 0
       digitalWrite(2, 0);
       digitalWrite(3, 0);
       digitalWrite(4, 0);
       digitalWrite(5, 0);
       digitalWrite(    6, 0);
       digitalWrite(7, 0);
       digitalWrite(8, 1);
      break;
           
    default: 
       digitalWrite(2, 1);
       digitalWrite(3, 1);
       digitalWrite(4, 1);
       digitalWrite(5, 1);
       digitalWrite(6, 1);
       digitalWrite(7, 1);
       digitalWrite(8, 1);
      
  }
}

void setup() {               
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);  //seg a
  pinMode(3, OUTPUT);  //seg b
  pinMode(4, OUTPUT);  //seg c
  pinMode(5, OUTPUT);  //seg d
  pinMode(6, OUTPUT);  //seg e
  pinMode(7, OUTPUT);  //seg f
  pinMode(8, OUTPUT);  //seg g
  
  pinMode(10, OUTPUT);  // activa digito 1 derecha (unidad)
  pinMode(11, OUTPUT);  // activa digito 2 izquierda (decena)
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  
    
}

void loop() {

  int valorBotton;

  if (estadoCrono == 0) {
    while (true) {
      valorBotton = digitalRead(0);
      delay(retardo);
      multiplexar();
      mostrar();

      if (valorBotton == 0) {
        cambiarEstado();
        //delay(10);
        break;
        }
      
      }
    
    }

  if (estadoCrono == 1) {
    while (true) {
      valorBotton = digitalRead(0);
      delay(retardo);               // tiempo que dura encendido cada 7seg antes de cambiar al otro
      contar();
      multiplexar();
      mostrar();

      if (valorBotton == 0) {
        cambiarEstado();
        //delay(10);
        break;
        }
     }    
    }

  if (estadoCrono == 2) {
    while (true) {
      valorBotton = digitalRead(0);
      delay(retardo);               // tiempo que dura encendido cada 7seg antes de cambiar al otro
      multiplexar();
      mostrar();

      if (valorBotton == 0) {
        cambiarEstado();
        //delay(10);
        break;
        }
     } 
      
   }
 
    
    
 }
