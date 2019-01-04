#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
              //4294967296
	      //631761789
              //212878420
#define LEN_ARR 1000000
#define STR_LEN 500

int main(int argc, char *argv[])
{
  FILE *fp_i, *fp_o;
  char *line, *pch, str_name[STR_LEN], str_ruta[STR_LEN], str_uno[STR_LEN], str_dos[STR_LEN], str_valor[STR_LEN],
       aux[STR_LEN];
  size_t len;
  ssize_t read;
  int flag_name, flag_coord, count;
  int ix, iy, array[LEN_ARR], pos, largo;
  DIR *dp;
  struct dirent *dir;

  dp = opendir("./entrada");
  
  //for(ix = 0; ix < LEN_ARR; ix++)
  //{
    //array[ix] = 0;
  //}

  if(dp)
  {
    while((dir = readdir(dp)) != NULL) 
    {
      if(dir->d_type == DT_REG)
      {
        for(ix = 0; ix < LEN_ARR; ix++)
	{
	  array[ix] = 0;
	}

	sprintf(str_ruta, "./entrada/%s", dir->d_name);      
	fp_i = fopen(str_ruta, "r");

	if(fp_i == NULL)
	{
	  printf("Error: al abrir el archivo [%s]\n", dir->d_name);
	  return(-1);
	}

	printf("Procesando archivo [%s]\n", dir->d_name);

	sprintf(str_ruta, "./salida/%s", dir->d_name);
	fp_o = fopen(str_ruta, "w");       

        for(ix = 0, line = NULL, len = 0; (read = getline(&line, &len, fp_i)) != -1; ix++)
        {
	  sscanf(line, "%[^,],%[^,],%[^.].", str_uno, str_dos, str_valor);
	  memset(aux, 0, sizeof(aux));
	  largo = strlen(str_valor);
	  
	  if(largo >= 4)
	  {
            strncpy(aux, str_valor, strlen(str_valor)-3);	  
            pos = atoi(aux);
	  }
	  else
	  {
	    pos = 0;
	  }

	  if(pos < 0)
          {
            //printf("negativo [%d]\n", pos);		  
	    pos = 0;
	  }

          if(array[pos] == 0)
          {
            fprintf(fp_o, "%s,%s,%d\n", str_uno, str_dos, pos);
	    ++array[pos];
	  }
	  else
          {
	    for(++pos; array[pos] != 0; pos++);
	    ++array[pos];
	    fprintf(fp_o, "%s,%s,%d\n", str_uno, str_dos, pos);
	  }
        }

        fclose(fp_i);
        fclose(fp_o);
      }
    }

    closedir(dp);
  }

  printf("Termino del proceso\n");

  return 0;
}
