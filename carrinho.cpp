//CÓDIGO PARA CARRINHO SEGUIDOR DE LINHA (3 SENSORES)
//FEITO POR: ALEXSANDRA MONTEIRO RIBEIRO
//INSTAGRAM: @alexsandra_6075

#define pinSensorDir A3  // Sensor direito
#define pinSensorCen A2 // Sensor centro
#define pinSensorEsq A1  // Sensor esquerdo

#define pinMotorD1 6    // Motor direito IN1
#define pinMotorD2 9    // Motor direito IN2
#define pinMotorE1 11   // Motor esquerdo IN4
#define pinMotorE2 10   // Motor esquerdo IN3

int velocidade = 170; //velocidade Máxima
int velocidadeReduzida = velocidade/2; //Velocidade Minima
int ultimaDirecao = 0; // 0 = reto, -1 = esquerda, 1 = direita

void setup() {
  pinMode(pinSensorDir, INPUT);
  pinMode(pinSensorCen, INPUT);
  pinMode(pinSensorEsq, INPUT);

  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);
}

void loop() { //Seguir linha preta
  bool estadoDir = digitalRead(pinSensorDir);
  bool estadoCen = digitalRead(pinSensorCen);
  bool estadoEsq = digitalRead(pinSensorEsq);
    
    /* PRIORIDADE: centro -> esquerda/direita -> rebusca -> parar
    1 = Preto  0 = Branco
    */
  if (estadoDir == 1 && estadoCen == 1 && estadoEsq == 1) { //Parar (Quando os 3 sensores detectarem preto)
    parar();
  }
  else if (estadoCen == 1 && estadoDir == 0 && estadoEsq == 0) { //Andar para frente (Quando só  o sensor do meio detectar preto)
    moverFrente(velocidade);
  }
  else if (estadoDir == 1 && estadoEsq == 0) { //Virar a direita (Quando o sensor direito detectar preto)
    virarDireita(velocidadeReduzida);
  }
  else if (estadoEsq == 1 && estadoDir == 0) { //Virar a Esquerda (Quando o sensor esquerdo detectar preto)
    virarEsquerda(velocidadeReduzida);
  }
  else {
    // Linha perdida -> rebusca pela última direção
    if (ultimaDirecao == 1) {
      virarDireita(velocidade);
    } else {
      virarEsquerda(velocidade);
    }
  }
}

void moverFrente(int vel) {
  digitalWrite(pinMotorD1, LOW);
  analogWrite(pinMotorD2, velocidade);
  digitalWrite(pinMotorE1, LOW);
  analogWrite(pinMotorE2, velocidade);
  ultimaDirecao = 0;
}

void virarDireita(int vel) {
  analogWrite(pinMotorD1, velocidade);
  digitalWrite(pinMotorD2, LOW);
  digitalWrite(pinMotorE1, LOW);
  analogWrite(pinMotorE2, velocidade);
  ultimaDirecao = 1;
}

void virarEsquerda(int vel) {
  digitalWrite(pinMotorD1, LOW);
  analogWrite(pinMotorD2, velocidade);
  analogWrite(pinMotorE1, velocidade);
  digitalWrite(pinMotorE2, LOW);
  ultimaDirecao = -1;
}

void parar() {
  digitalWrite(pinMotorD1, LOW);
  digitalWrite(pinMotorD2, LOW);
  digitalWrite(pinMotorE1, LOW);
  digitalWrite(pinMotorE2, LOW);
}