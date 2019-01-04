#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STR_LEN 500000
#define LEN_ARR 5000

struct datos
{
  float valor;
}Datos[LEN_ARR];

int main(int argc, char *argv[])
{
  FILE *fp_i, *fp_o;
  char *line, *pch, str_name[STR_LEN], str_ruta[STR_LEN], str_coord[STR_LEN];
  size_t len;
  ssize_t read;
  int ix, iy, flag_name, count, numero_archivos;
  float min,max,pro,valor;
  DIR *dp;
  struct dirent *dir;

  dp = opendir("./entrada");
  numero_archivos = atoi(argv[1]);

  for(iy = 0; iy < LEN_ARR; iy++)
    Datos[iy].valor = 0;

  iy = 0;

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

	++iy;
	printf("Procesando archivo [%s]", dir->d_name);

        if(iy == numero_archivos)
	{
	  printf("[lol]");
	  sprintf(str_ruta, "./salida/%.4s.kml", dir->d_name);
	  fp_o = fopen(str_ruta, "w");
        }

        for(ix = 0, flag_name = 0, line = NULL, len = 0, count = 0, pro = 0; (read = getline(&line, &len, fp_i)) != -1; ix++)
        {

          if(strncmp(line, "<name>", 6) == 0)
          {
            if(flag_name == 0)
            {
              ++flag_name;
	      if(iy == numero_archivos)
                fprintf(fp_o, "<name>%.4s</name>\n", dir->d_name);
	      continue;
	    }

	    sscanf(line+6, "%[^<]<", str_name);
            Datos[count].valor += atof(str_name);

            if(iy == numero_archivos)
	    {
	      Datos[count].valor = Datos[count].valor/numero_archivos;
              fprintf(fp_o, "<name>%f</name>\n", Datos[count].valor);
            }

            if(flag_name == 1 && iy == numero_archivos)
            {
              max = Datos[count].valor;
	      min = Datos[count].valor;
	      ++flag_name;
            }

	    if(iy == numero_archivos)
	    {
              if(Datos[count].valor > max)
	        max = Datos[count].valor;
	      if(Datos[count].valor < min)
	        min = Datos[count].valor;
            }

	    ++count;

          }else
	  {
	    if(iy == numero_archivos)	  
	      fprintf(fp_o, "%s", line);
	  }
        }

	printf("[%d]\n", count);
	if(iy == numero_archivos)
	  printf("min [%f] max [%f]\n", min, max);
        //printf("[%d] update ndvi set ndvi_max=%f, ndvi_min=%f, ndvi_pro=%f where ndvi_preid=%s and ndvi_nombre='%.10s';\n", count, max, min, pro/count, argv[1], dir->d_name);

        fclose(fp_i);
	if(iy == numero_archivos)
	  fclose(fp_o);
      }
    }

    closedir(dp);
  }

  //printf("Termino del proceso\n");

  return 0;
}
