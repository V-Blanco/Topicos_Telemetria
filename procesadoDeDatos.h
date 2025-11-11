#ifndef PROCESADODEDATOS_H_INCLUDED
#define PROCESADODEDATOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// -------------------------------------- MACROS ------------------------------------------- //

#define TAM_REG 4000

// Subsistemas, desplzamiento y tamaños
#define INI_S_CDH 8
#define OFFSET_OBT 92
#define TAM_OBT 4

#define INI_S_PCS 1604
#define OFFSET_VBA 750
#define TAM_VBA 2

#define CALCULO_VPROM(x) ( ((x)*0.01873128)+(-38.682956) )

// Fecha y hora base para la toma de registros
#define YEAR_INI_REG 1980
#define DIA_INI_REG 06
#define MES_INI_REG 01

#define HORA_INI_REG 00
#define MIN_INI_REG 00
#define SEG_INI_REG 00

// ----------------------------------- DECLARACIONES ---------------------------------------- //

typedef uint16_t t_volt;
typedef uint32_t t_seg;

typedef struct
{
    t_seg OBT;
    t_volt vBatAverage;
}t_crudo;

typedef struct tm t_fecHora;
typedef struct
{
    t_fecHora fechaHora;
    float voltajeProm;
}t_dato;

/// Devuelve 1 si el encoding del equipo es BIG ENDIAN, caso contrario devuelve 0.
int identificadorEncoding ();

/// Realiza una conversion entre little endian y big endian y viceversa.
void convertidorEncoding (void* dato, size_t tamDato);

/// Valida si el archivo contiene registros del tamaño definido por TAM_REG
/// Devuelve 1 en caso exitoso y 0 en caso contrario.
int validarArchivo(FILE* pArch);

void procesarDato(t_dato* dest, t_crudo* origen);

int escribirRegistroTXT (FILE* dest, t_dato* dato);

#endif // PROCESADODEDATOS_H_INCLUDED
