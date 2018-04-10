// Programa : Data e hora com modulo RTC DS1302
// Alteracoes e adaptacoes : Arduino e Cia
//
// Baseado no programa original de Krodal e na biblioteca virtuabotixRTC

// Carrega a biblioteca virtuabotixRTC
#include <virtuabotixRTC.h>

// Determina os pinos ligados ao modulo
// myRTC(clock, data, rst)
virtuabotixRTC myRTC(6, 7, 8);

//LEDs de manha
int ledM1 = 14; //seg
int ledM2 = 15; //ter
int ledM3 = 16; //qua
int ledM4 = 17; //qui
int ledM5 = 18; //sex
int ledM6 = 19; //sab
int ledM7 = 20; //dom

//LEDs de noite
int ledN1 = 13; //seg
int ledN2 = 12; //ter
int ledN3 = 11; //qua
int ledN4 = 10;  //qui
int ledN5 = 9;  //sex
int ledN6 = 5;  //sab
int ledN7 = 4; //dom

//buzzer
int buzzer = 3;

//botoes
int button1 = 36;
int button2 = 2;

//flags auxiliares
int flagA = 0;
int auxD = 0;

//variaveis para armazenar o estado dos botoes
int bState1 = 0;
int bState2 = 0;

//struct criada para salvar os alarmes
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

  //configurando os pinos dos LEDs
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

  //configurando os pinos dos botoes
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  //configurando o pino do buzzer
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  // Le as informacoes do RTC
  myRTC.updateTime();

  // Imprime as informacoes no serial monitor
  Serial.print("Data : ");
  // Chama a funcao que imprime o dia da semana
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

  //desliga todos os LEDs
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

  //Vetores dos alarmes
  Alarme m[7];
  Alarme n[7];

  //alarme domingo de manha
  m[0].diaS = 1;
  m[0].hora = 10;
  m[0].minuto = 30;

  //alarme domingo de noite
  n[0].diaS = 1;
  n[0].hora = 23;
  n[0].minuto = 13;

  //alarme segunda de manha
  m[1].diaS = 2;
  m[1].hora = 10;
  m[1].minuto = 50;

  //alarme segunda de noite
  n[1].diaS = 2;
  n[1].hora = 22;
  n[1].minuto = 59;

  //alarme terca de manha
  m[2].diaS = 3;
  m[2].hora = 10;
  m[2].minuto = 30;

  //alarme terca de noite
  n[2].diaS = 3;
  n[2].hora = 19;
  n[2].minuto = 30;

  //alarme quarta de manha
  m[3].diaS = 4;
  m[3].hora = 10;
  m[3].minuto = 30;

  //alarme quarta de noite
  n[3].diaS = 4;
  n[3].hora = 19;
  n[3].minuto = 30;

  //alarme quinta de manha
  m[4].diaS = 5;
  m[4].hora = 10;
  m[4].minuto = 30;

  //alarme quinta de noite
  n[4].diaS = 5;
  n[4].hora = 19;
  n[4].minuto = 30;

  //alarme sexta de manha
  m[5].diaS = 6;
  m[5].hora = 10;
  m[5].minuto = 30;

  //alarme sexta de noite
  n[5].diaS = 6;
  n[5].hora = 19;
  n[5].minuto = 30;

  //alarme sabado de manha
  m[6].diaS = 7;
  m[6].hora = 10;
  m[6].minuto = 30;

  //alarme sabado de noite
  n[6].diaS = 7;
  n[6].hora = 19;
  n[6].minuto = 30;

  //variavel auxiliar para controle dos vetores
  auxD = myRTC.dayofweek - 1;
  if (auxD < 0) {
    auxD = 6;
  }

  //verifica se algum alarme deve ser acionado
  if (myRTC.hours > 12) {
    if ((myRTC.dayofweek == n[auxD].diaS) && (myRTC.hours == n[auxD].hora) && (myRTC.minutes == n[auxD].minuto) && (myRTC.seconds <= 5)) {
      flagA = 1; //flag indicando que um alarme deve ser acionado
    }
  } else {
    if ((myRTC.dayofweek == m[auxD].diaS) && (myRTC.hours == m[auxD].hora) && (myRTC.minutes == m[auxD].minuto) && (myRTC.seconds <= 5)) {
      flagA = 1;
    }
  }


  //le o estado do botao 1
  bState1 = digitalRead(button1);

  //acende o led do respectivo remedio de liga o alarme
  if (flagA == 1) {
    acendeLED(myRTC.dayofweek, myRTC.hours);
    tone(buzzer, 262, 1000);
    if (bState1 == HIGH) { //se o botao 1 for pressionado desliga o alarme
      flagA = 0;
    }
  }

  //le o estado do botao 2
  bState2 = digitalRead(button2);

  //se o botao 1 for pressionado acende o LED do ultimo remedio tomado
  if (bState1 == HIGH) {
    if (myRTC.hours > 12) {
      if (n[auxD].hora < myRTC.hours) {
        acendeLED(n[auxD].diaS, n[auxD].hora);
      } else if (n[auxD].hora == myRTC.hours) {
        if (n[auxD].minuto < myRTC.minutes) {
          acendeLED(n[auxD].diaS, n[auxD].hora);
        } else if (n[auxD].minuto >= myRTC.minutes) {
          acendeLED(m[auxD].diaS, m[auxD].hora);
        }
      } else if (n[auxD].hora > myRTC.hours) {
        acendeLED(m[auxD].diaS, m[auxD].hora);
      }
    } else {
      if (m[auxD].hora < myRTC.hours) {
        acendeLED(m[auxD].diaS, m[auxD].hora);
      } else if (m[auxD].hora == myRTC.hours) {
        if (m[auxD].minuto < myRTC.minutes) {
          acendeLED(m[auxD].diaS, m[auxD].hora);
        } else if (m[auxD].minuto >= myRTC.minutes) {
          auxD -= 1;
          if (auxD < 0) {
            auxD = 6;
          }
          acendeLED(n[auxD].diaS, n[auxD].hora);

        }
      } else if (m[auxD].hora > myRTC.hours) {
        auxD -= 1;
        if (auxD < 0) {
          auxD = 6;
        }
        acendeLED(n[auxD].diaS, n[auxD].hora);
      }
    }
  }

  //se o botao 2 for pressionado acendo o LED do proximo remedio a ser tomado
  if (bState2 == HIGH) {
    if (myRTC.hours > 12) {
      if (n[auxD].hora > myRTC.hours) {
        acendeLED(n[auxD].diaS, n[auxD].hora);
      } else if (n[auxD].hora == myRTC.hours) {
        if (n[auxD].minuto > myRTC.minutes) {
          acendeLED(n[auxD].diaS, n[auxD].hora);
        } else if (n[auxD].minuto <= myRTC.minutes) {
          auxD += 1;
          if (auxD > 6) {
            auxD = 0;
          }
          acendeLED(m[auxD].diaS, m[auxD].hora);
        }
      } else if (n[auxD].hora < myRTC.hours) {
        auxD += 1;
        if (auxD > 6) {
          auxD = 0;
        }
        acendeLED(m[auxD].diaS, m[auxD].hora);
      }
    } else {
      if (m[auxD].hora > myRTC.hours) {
        acendeLED(m[auxD].diaS, m[auxD].hora);
      } else if (m[auxD].hora == myRTC.hours) {
        if (m[auxD].minuto > myRTC.minutes) {
          acendeLED(m[auxD].diaS, m[auxD].hora);
        } else if (m[auxD].minuto <= myRTC.minutes) {
          acendeLED(n[auxD].diaS, n[auxD].hora);
        }
      } else if (m[auxD].hora < myRTC.hours) {
        acendeLED(n[auxD].diaS, n[auxD].hora);
      }
    }
  }

}

//funcao para imprimir por extenso os dias da semana no monitor serial
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

//funcao para acender o LED equivalente ao alarme tocado
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



