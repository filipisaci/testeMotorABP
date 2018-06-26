int contador = 0;
int media = 0;
int auxMedia = 0;
int erro = 0;
int ganho = 1;
int comandoPwm = 0;
const int divisorMedia = 20;
const int referenciaPwm = 70; //Sinal já convertido para PWM

void setup(){
  Serial.begin(9600);
}

int velocidadeRpmParaPwm(int cento, int unidade){
  int vRPM = ((cento * 100) + unidade);
  int vPWM = map(vRPM, 0, 1800, 0, 255);
  return vPWM;
}

void filtro(int sinal) {
  contador++;
  auxMedia = auxMedia + sinal;
  
  if (contador == divisorMedia) {
  	media = auxMedia / divisorMedia;
    contador = 0;
    auxMedia = 0;
    Serial.println(media);
  }
}

void loop(){
  int sinalPwm = velocidadeRpmParaPwm(0x00, 0xFF);
  erro = referenciaPwm - sinalPwm;
  comandoPwm = erro * ganho;
  
  Serial.println(comandoPwm);
}