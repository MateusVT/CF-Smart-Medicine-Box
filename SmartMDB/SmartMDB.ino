// Programa : Data e hora com modulo RTC DS1302
// Alteracoes e adaptacoes : Arduino e Cia
//
// Baseado no programa original de Krodal e na biblioteca virtuabotixRTC

// Carrega a biblioteca virtuabotixRTC
#include <virtuabotixRTC.h>

// Determina os pinos ligados ao modulo
// myRTC(clock, data, rst)
virtuabotixRTC myRTC(6, 7, 8);
//manha
int ledM1 = 14; //seg
int ledM2 = 15; //ter
int ledM3 = 16; //qua
int ledM4 = 17; //qui
int ledM5 = 18; //sex
int ledM6 = 19; //sab
int ledM7 = 20; //dom

//noite
int ledN1 = 13; //seg
int ledN2 = 12; //ter
int ledN3 = 11; //qua
int ledN4 = 10;  //qui
int ledN5 = 9;  //sex
int ledN6 = 5;  //sab
int ledN7 = 4; //dom

int buzzer = 3;

int button2 = 2;
int button1 = 1;

struct alarme
{
  int diaS;
  int hora;
  int minuto;
};
typedef struct alarme Alarme;

void setup()
{
  Serial.begin(9600);
  // Informacoes iniciais de data e hora
  // Apos setar as informacoes, comente a linha abaixo
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  //myRTC.setDS1302Time(30, 38, 15, 7, 7, 4, 2018);
  pinMode(ledM1, OUTPUT);
  pinMode(ledM2, OUTPUT);
  pinMode(ledM3, OUTPUT);
  pinMode(ledM4, OUTPUT);
  pinMode(ledM5, OUTPUT);
  pinMode(ledM6, OUTPUT);
  pinMode(ledM7, OUTPUT);

  pinMode(ledN1, OUTPUT);
  pinMode(ledN2, OUTPUT);
  pinMode(ledN3, OUTPUT);
  pinMode(ledN4, OUTPUT);
  pinMode(ledN5, OUTPUT);
  pinMode(ledN6, OUTPUT);
  pinMode(ledN7, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

void loop()
{
  // Le as informacoes do CI
  myRTC.updateTime();

  // Imprime as informacoes no serial monitor
  Serial.print("Data : ");
  // Chama a rotina que imprime o dia da semana
  imprime_dia_da_semana(myRTC.dayofweek);
  Serial.print(", ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print("Hora : ");
  // Adiciona um 0 caso o valor da hora seja <10
  if (myRTC.hours < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos minutos seja <10
  if (myRTC.minutes < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos segundos seja <10
  if (myRTC.seconds < 10)
  {
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);

  delay(1000);

  digitalWrite(ledM1, LOW);
  digitalWrite(ledM2, LOW);
  digitalWrite(ledM3, LOW);
  digitalWrite(ledM4, LOW);
  digitalWrite(ledM5, LOW);
  digitalWrite(ledM6, LOW);
  digitalWrite(ledM7, LOW);

  digitalWrite(ledN1, LOW);
  digitalWrite(ledN2, LOW);
  digitalWrite(ledN3, LOW);
  digitalWrite(ledN4, LOW);
  digitalWrite(ledN5, LOW);
  digitalWrite(ledN6, LOW);
  digitalWrite(ledN7, LOW);

  //Vetor dos alarmes
  Alarme a[14];



  while (Serial.available() == 0);

  int dia = Serial.parseInt(); //read int or parseFloat for ..float...

  while (Serial.available() == 0);
  int hora = Serial.parseInt();

  while (Serial.available() == 0);
  int minuto = Serial.parseInt();

  switch (dia)
  {
    case 1:
      if (hora < 12) {
        a[12].diaS = dia;
        a[12].hora = hora;
        a[12].minuto = minuto;
      } else if (hora > 11) {
        a[13].diaS = dia;
        a[13].hora = hora;
        a[13].minuto = minuto;
      }
      break;
    case 2:
      if (hora < 12) {
        digitalWrite(ledM1, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN1, HIGH);
      }
      break;
    case 3:
      if (hora < 12) {
        digitalWrite(ledM2, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN2, HIGH);
      }
      break;
    case 4:
      if (hora < 12) {
        digitalWrite(ledM3, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN3, HIGH);
      }
      break;
    case 5:
      if (hora < 12) {
        digitalWrite(ledM4, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN4, HIGH);
      }
      break;
    case 6:
      if (hora < 12) {
        digitalWrite(ledM5, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN5, HIGH);
      }
      break;
    case 7:
      if (hora < 12) {
        digitalWrite(ledM6, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN6, HIGH);
      }
      break;
  }
  //  Serial.print(dia);
  //  Serial.print(" ");
  //  Serial.print(hora);
  //  Serial.print(" ");
  //  Serial.println(minuto);
  //



  //  //alarme segunda manha
  //  a[0].diaS = 2;
  //  a[0].hora = 10;
  //  a[0].minuto = 30;
  //
  //  //alarme segunda noite
  //  a[1].diaS = 2;
  //  a[1].hora = 19;
  //  a[1].minuto = 30;
  //
  //  //alarme terca manha
  //  a[2].diaS = 3;
  //  a[2].hora = 10;
  //  a[2].minuto = 30;
  //
  //  //alarme terca noite
  //  a[3].diaS = 3;
  //  a[3].hora = 19;
  //  a[3].minuto = 30;
  //
  //  //alarme quarta manha
  //  a[4].diaS = 4;
  //  a[4].hora = 10;
  //  a[4].minuto = 30;
  //
  //  //alarme quarta noite
  //  a[5].diaS = 4;
  //  a[5].hora = 19;
  //  a[5].minuto = 30;
  //
  //  //alarme quinta manha
  //  a[6].diaS = 5;
  //  a[6].hora = 10;
  //  a[6].minuto = 30;
  //
  //  //alarme quinta noite
  //  a[7].diaS = 5;
  //  a[7].hora = 19;
  //  a[7].minuto = 30;
  //
  //  //alarme sexta manha
  //  a[8].diaS = 6;
  //  a[8].hora = 10;
  //  a[8].minuto = 30;
  //
  //  //alarme sexta noite
  //  a[9].diaS = 6;
  //  a[9].hora = 19;
  //  a[9].minuto = 30;
  //
  //  //alarme sabado manha
  //  a[10].diaS = 7;
  //  a[10].hora = 10;
  //  a[10].minuto = 30;
  //
  //  //alarme sabado noite
  //  a[11].diaS = 7;
  //  a[11].hora = 19;
  //  a[11].minuto = 30;
  //
  //  //alarme domingo manha
  //  a[12].diaS = 1;
  //  a[12].hora = 10;
  //  a[12].minuto = 30;
  //
  //  //alarme domingo noite
  //  a[13].diaS = 1;
  //  a[13].hora = 19;
  //  a[13].minuto = 30;
  //



  if ((myRTC.dayofweek == a[0].diaS) && (myRTC.hours == a[0].hora) && (myRTC.minutes == a[0].minuto)) {
    acendeLED(a[0].diaS, a[0].hora);
    tone(buzzer, 262, 100);
  }

}

void imprime_dia_da_semana(int dia)
{
  switch (dia)
  {
    case 1:
      Serial.print("Domingo");
      break;
    case 2:
      Serial.print("Segunda");
      break;
    case 3:
      Serial.print("Terca");
      break;
    case 4:
      Serial.print("Quarta");
      break;
    case 5:
      Serial.print("Quinta");
      break;
    case 6:
      Serial.print("Sexta");
      break;
    case 7:
      Serial.print("Sabado");
      break;
  }
}

void acendeLED(int dia, int hora) {
  switch (dia)
  {
    case 1:
      if (hora < 12) {
        digitalWrite(ledM7, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN7, HIGH);
      }
      break;
    case 2:
      if (hora < 12) {
        digitalWrite(ledM1, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN1, HIGH);
      }
      break;
    case 3:
      if (hora < 12) {
        digitalWrite(ledM2, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN2, HIGH);
      }
      break;
    case 4:
      if (hora < 12) {
        digitalWrite(ledM3, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN3, HIGH);
      }
      break;
    case 5:
      if (hora < 12) {
        digitalWrite(ledM4, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN4, HIGH);
      }
      break;
    case 6:
      if (hora < 12) {
        digitalWrite(ledM5, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN5, HIGH);
      }
      break;
    case 7:
      if (hora < 12) {
        digitalWrite(ledM6, HIGH);
      } else if (hora > 11) {
        digitalWrite(ledN6, HIGH);
      }
      break;
  }
}


