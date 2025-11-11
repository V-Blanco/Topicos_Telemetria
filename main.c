#include "main.h"

int main()
{
    t_crudo datoCrudo;
    t_dato datoProc;
    char nombreArchTXT[] = "voltajes.txt";
    int bigEnd;

    /// Apertura de archivos
    FILE* pArchSatelite = fopen("HKTMST.bin", "rb");
    if(!pArchSatelite)
        return -1;

    FILE* pArchTxt = fopen(nombreArchTXT, "wt");
    if(!pArchTxt)
    {
        fclose(pArchSatelite);
        return -1;
    }

    bigEnd = identificadorEncoding();

    if(validarArchivo(pArchSatelite))
    {
        do
        {
            /// Lectura de los datos
            fseek(pArchSatelite, INI_S_CDH + OFFSET_OBT, SEEK_CUR);
            fread(&datoCrudo.OBT, TAM_OBT, 1, pArchSatelite);

            fseek(pArchSatelite, INI_S_PCS+OFFSET_VBA -(INI_S_CDH+OFFSET_OBT+TAM_OBT), SEEK_CUR);
            fread(&datoCrudo.vBatAverage, TAM_VBA, 1, pArchSatelite);

            /// Procesamiento
            if(!bigEnd)
            {
                convertidorEncoding(&datoCrudo.OBT, TAM_OBT);
                convertidorEncoding(&datoCrudo.vBatAverage, TAM_VBA);
            }
            procesarDato(&datoProc, &datoCrudo);

            escribirRegistroTXT(pArchTxt, &datoProc);

            fseek(pArchSatelite, TAM_REG -(INI_S_PCS+OFFSET_VBA+TAM_VBA+1), SEEK_CUR);
            fgetc(pArchSatelite);
        }
        while(!feof(pArchSatelite));

        fclose(pArchSatelite);
        fclose(pArchTxt);

        return 0;
    }
    else
        abort();
}
