/*
 * Protótipo de reúso da água do chuveiro para uso na caixa de descarga do vaso sanitário.
 * Universidade Federal de Goiás (UFG) / MediaLab/UFG
 * Especialização em Mídias Interativas (InMídias)
 * Polo Cavalcante - Grupo II
 * 
 * Para este projeto, fora utilizada a biblioteca do HCSR04Ultrasonic disponível para download em:
 * https://github.com/daijo/ArduinoLibraries/tree/master/HCSR04Ultrasonic
 * 
 * ----------------------------------
 * $Autor: jornalistadigital $
 * $Data: 2017-09-01 17:13:12 -0400 (Fri, 01 Sep 2017) $
 * Disponível também em: 
 * ----------------------------------
 */

#include <Ultrasonic.h>

#define TRIGGER_PIN  6 // define o pino 6 da placa de arduino para o trigger do sensor
#define ECHO_PIN     7 // define o pino 7 da placa de arduino para o echo do sensor
#define bomba 13       // define o pino 13 da placa de arduino para acionamento da bomba de água.

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);//inicializa o sensor ultrassonico

void setup()
  {
  Serial.begin(9600);//configura a taxa de comunicação em bits por segundo 
  }

void loop()
  {
  float cmMsec, inMsec;//informa que o armazenamento de dados será flutuante, ou seja, possui casas decimais. 
  long microsec = ultrasonic.timing();//lê os dados do sensor, com o tempo de retorono do sinal
  pinMode(bomba, OUTPUT);//define o pino da bomba como um pino de saída de dados.
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); //calcula a distância em centímetros
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN); //calcula a distância em polegadas
  Serial.print(" CM: "); //escreve CM na tela
  Serial.println(cmMsec); //escreve a distância em centímetros na leta e pula uma linha
  delay(1000);//determina que o delay entre as medições será de 1 segundo;
  
  
 if (cmMsec >= 19 ) // condiciona a distância máxima entre o sensor e a água. Neste exemplo, se for maior ou igual a 19cm deverá acionar a bomba
  {
    Serial.println("Distância do sensor maior que 19cm...ligando!");// imprime na tela a frase entre parentêses
    digitalWrite(bomba, HIGH);//liga a bomba
  }
  else if(cmMsec <= 10) // condiciona a distância mínima entre o sensor e a água. Neste exemplo, se for maior ou igual a 10cm deverá desligar a bomba
  {
    Serial.println("Distância dos sensor menor que 15cm...desligando!");// imprime na tela a frase entre parentêses
    digitalWrite(bomba, LOW);
  }
  
}
