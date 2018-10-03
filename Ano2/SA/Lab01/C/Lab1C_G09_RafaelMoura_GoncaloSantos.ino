// Entradas
const int sens_entr = 8;
const int sens_sai  = 9;

enum {
    ComCarro = 0,
    SemCarro = 1
};

// Saídas
const int semaf_verde   = 5;
const int semaf_vermelho = 4;
const int canc_entr     = 2;
const int canc_sai      = 3;

// Estado
#define NUMERO_LUGARES 5
int LugaresOcupados = 0;

enum {
    Cancela_Fechada,
    Cancela_Aberta
};
typedef struct {
    int Cancela;
    unsigned int ContagemCiclos;
} estado_cancela;

estado_cancela Entrada;
estado_cancela Saida;

#define DEBUG 1
#if DEBUG
#define WarnIfNull(Test, Message) do {if(!(Test)) Serial.println(Message);} while(0);
#else
#define WarnIfNull(Test, Message)
#endif

// Corre aquando do reset( uma unica vez)
void setup()
{
    Serial.begin(115200);

    // Definição de pinos como Entradas/Saidas.
    pinMode(semaf_verde, OUTPUT);
    pinMode(semaf_vermelho, OUTPUT);
    pinMode(canc_entr, OUTPUT);
    pinMode(canc_sai, OUTPUT);
    pinMode(sens_entr,INPUT_PULLUP);
    pinMode(sens_sai,INPUT_PULLUP);

    digitalWrite(semaf_verde, HIGH);
    digitalWrite(semaf_vermelho, HIGH);
    digitalWrite(canc_entr, HIGH);
    digitalWrite(canc_sai, HIGH);
    delay(1000);  //Espera 1000ms (1s)
    digitalWrite(semaf_verde, LOW);
    digitalWrite(semaf_vermelho, LOW);
    digitalWrite(canc_entr, LOW);
    digitalWrite(canc_sai, LOW);
}

// Sequencia de codigo que corre em ciclo
unsigned int Cycles = 0;
void loop()
{
    // NOTA: Leitura de entradas
    bool EntradaSensor = (digitalRead(sens_entr) == ComCarro); // 1 quando tem carro
    bool SaidaSensor = (digitalRead(sens_sai) == ComCarro); // 1 quando tem carro

    // NOTA: Processamento da máquina de estados
    estado_cancela EntradaAnterior = Entrada;
    estado_cancela SaidaAnterior = Saida;

    ++Entrada.ContagemCiclos;
    ++Saida.ContagemCiclos;

    if((Entrada.Cancela == Cancela_Fechada) && EntradaSensor && LugaresOcupados < NUMERO_LUGARES) {
        Entrada.Cancela = Cancela_Aberta;
        Entrada.ContagemCiclos = 0;
    }
    if((Entrada.Cancela == Cancela_Aberta) && !EntradaSensor && Entrada.ContagemCiclos >= 500) Entrada.Cancela = Cancela_Fechada;
    if((Saida.Cancela == Cancela_Fechada) && SaidaSensor && LugaresOcupados > 0) {
        Saida.Cancela = Cancela_Aberta;
        Saida.ContagemCiclos = 0;
    }
    if((Saida.Cancela == Cancela_Aberta) && !SaidaSensor && Saida.ContagemCiclos >= 500) Saida.Cancela = Cancela_Fechada;

    if((EntradaAnterior.Cancela == Cancela_Fechada) && Entrada.Cancela == Cancela_Aberta) ++LugaresOcupados;
    if((SaidaAnterior.Cancela == Cancela_Fechada) && Saida.Cancela == Cancela_Aberta) --LugaresOcupados;

    WarnIfNull(LugaresOcupados <= NUMERO_LUGARES, "Número de lugares excedido");
    WarnIfNull(LugaresOcupados >= 0, "Número de lugares ocupados < 0");

#if DEBUG
    Serial.print("Número de lugares livres: ");
    Serial.println(NUMERO_LUGARES - LugaresOcupados);
#endif

    // NOTA: Cálculo de saídas
    bool AtuadorEntrada = (Entrada.Cancela == Cancela_Aberta);
    bool AtuadorSaida = (Saida.Cancela == Cancela_Aberta);
    bool SemaforoVerde = (LugaresOcupados != NUMERO_LUGARES);
    bool SemaforoVermelho = !SemaforoVerde;

    // NOTA: Escrita de saídas
    digitalWrite(canc_entr, AtuadorEntrada ? HIGH : LOW);
    digitalWrite(canc_sai, AtuadorSaida ? HIGH : LOW);
    digitalWrite(semaf_verde, SemaforoVerde ? HIGH : LOW);
    digitalWrite(semaf_vermelho, SemaforoVermelho ? HIGH : LOW);

    ++Cycles;
    delay(10);                             // 10 ms, manter esta linha
}
