#include <stdio.h>
#include "datas.h"

data corrigirData(data d)
{
    int diasMax = diasDoMes(d.mes, d.ano);
    if(d.dia > diasMax)
    {
        d.dia -= diasMax;
        ++d.mes;
        if(d.mes > 12)
        {
            d.mes = 1;
            ++d.ano;
        }

        d = corrigirData(d);
    }
    else if(d.dia < 1)
    {
        --d.mes;
        if(d.mes < 1)
        {
            d.mes = 12;
            --d.ano;
        }
        d.dia = diasDoMes(d.mes, d.ano) + d.dia;

        d = corrigirData(d);
    }

    return d;
}

/* Retorna a data correspondente ao dia seguinte da data d */
data diaSeguinte (data d){
    somaDias(d, 1);
    return d;
}

/* Retorna a data correspondente ao dia anterior à data d  */
data diaAnterior (data d){
    somaDias(d, -1);
    return d;
}


/* Retorna a data correspondente a somar k dias à data d (k pode ser negativo)  */
data somaDias (data d, int k) {
    d.dia += k;
    d = corrigirData(d);
    if(!dataValida(d))
    {
        puts("NNOOOOO");
    }
    return d;
}

int bissexto(int ano) {
  if (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))
    return 1;
  return 0;
}

int diasDoMes(int mes, int ano) {
   int ndias[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   if (bissexto(ano))
     ndias[1]++;

   return ndias[mes-1];
}

int dataValida(data d) {
    if (d.ano < 1)
      return 0;
    if (d.mes < 1 || d.mes > 12)
      return 0;
    if (d.dia < 1 || d.dia > diasDoMes(d.mes, d.ano))
      return 0;

    return 1;
}

void escreveData(char destino[], data d) {
  char meses[12][10] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
  sprintf(destino, "%02d de %s de %d", d.dia, meses[d.mes-1], d.ano);
}
