#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STR_LEN 500000

int main(int argc, char *argv[])
{
  FILE *fp_i;//, *fp_o;
  char *line, *pch, str_name[STR_LEN], str_ruta[STR_LEN], str_coord[STR_LEN];
  size_t len;
  ssize_t read;
  int ix, flag_name, count;
  float min,max,pro,valor;
  DIR *dp;
  struct dirent *dir;

  dp = opendir("./entrada");

  if(dp)
  {
    while((dir = readdir(dp)) != NULL)
    {
      if(dir->d_type == DT_REG)
      {
	sprintf(str_ruta, "./entrada/%s", dir->d_name);
	fp_i = fopen(str_ruta, "r");

	if(fp_i == NULL)
	{
	  printf("Error: al abrir el archivo [%s]\n", dir->d_name);
	  return(-1);
	}

	//printf("Procesando archivo [%s] ", dir->d_name);

        for(ix = 0, flag_name = 0, line = NULL, len = 0, count = 0, pro = 0; (read = getline(&line, &len, fp_i)) != -1; ix++)
        {

          if(strncmp(line, "<name>", 6) == 0)
          {
            if(flag_name == 0)
            {
              ++flag_name;
	      continue;
	    }

	    sscanf(line+6, "%[^<]<", str_name);
            valor = atof(str_name);

            if(flag_name == 1)
            {
              max = valor;
	      min = valor;
	      ++flag_name;
            }

            if(valor > max)
	      max = valor;
	    if(valor < min)
	      min = valor;

            pro += valor;

	    ++count;

          }
        }

        printf("update ndvi set ndvi_max=%f, ndvi_min=%f, ndvi_pro=%f where ndvi_preid=%s and ndvi_nombre='%.10s';\n", max, min, pro/count, argv[1], dir->d_name);

        fclose(fp_i);
      }
    }

    closedir(dp);
  }

  //printf("Termino del proceso\n");

  return 0;
}
