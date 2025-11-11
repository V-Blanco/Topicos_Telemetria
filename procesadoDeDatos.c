#include "procesadoDeDatos.h"

// ----------------------------------- VAR. GLOBAL ---------------------------------------- //
t_fecHora fechaIni ={.tm_hour = HORA_INI_REG,
                         .tm_min = MIN_INI_REG,
                         .tm_sec = SEG_INI_REG,
                         .tm_mday = DIA_INI_REG,
                         .tm_mon = MES_INI_REG-1,
                         .tm_year = YEAR_INI_REG - 1900,

                         .tm_isdst = 0
                         };
// ----------------------------------------------------------------------------------------- //

int identificadorEncoding ()
{
    short var = 1;
    char* ini = (char*)&var;

    return (*ini == 0? 1: 0);
}

void convertidorEncoding (void* dato, size_t tamDato)
{
    int i;
    char* pOrig,
        * pDest,
         buffer;

    pOrig = (char *)dato;
    pDest = pOrig +(tamDato-1);

    for(i=0; i< (tamDato/2); i++)
    {
        buffer = *pOrig;
        *pOrig = *pDest;
        *pDest = buffer;

        pOrig++;
        pDest--;
    }
}

int validarArchivo(FILE* pArch)
{
    fseek(pArch,0L,SEEK_END);
    if((ftell(pArch) % TAM_REG) == 0)
    {
        fseek(pArch,0L,SEEK_SET);
        return 1;
    }
    else
        return 0;
}

void procesarDato(t_dato* dest, t_crudo* origen)
{
    const time_t segDesdeInicio = mktime(&fechaIni);
    time_t segAux = (time_t)origen->OBT;
    t_fecHora* fechaAux;

    segAux += segDesdeInicio;
    fechaAux = gmtime(&segAux);
    dest->fechaHora = *fechaAux;

    dest->voltajeProm = (float)CALCULO_VPROM(origen->vBatAverage);
}

int escribirRegistroTXT (FILE* dest, t_dato* dato)
{
    char cadena[20];

    strftime(cadena,sizeof(cadena),"%d/%m/%y %H:%M:%S", &dato->fechaHora);
    return fprintf(dest, "%s %.1f\n",cadena,dato->voltajeProm);
}

