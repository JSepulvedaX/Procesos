#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STR_LEN 500000

int main(int argc, char *argv[])
{
  FILE *fp_i, *fp_o;
  char *line, *pch, str_name[STR_LEN], str_ruta[STR_LEN], str_coord[STR_LEN];
  size_t len;
  ssize_t read;
  int ix, flag_name, flag_coord, count;
  float valor;
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

	printf("Procesando archivo [%s] ", dir->d_name);

	sprintf(str_ruta, "./salida/%s", dir->d_name);
	fp_o = fopen(str_ruta, "w");

        for(ix = 0, flag_name = 1, flag_coord = 0, line = NULL, len = 0, count = 0; (read = getline(&line, &len, fp_i)) != -1; ix++)
        {
          if(flag_coord)
            ++flag_coord;

          if(flag_name)
          {
            if(strncmp(line, "<Folder>", 8) == 0)
            {
	      sscanf(line+14, "%[^<]<", str_name);

              fprintf(fp_o, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<kml xmlns=\"http://earth.google.com/kml/2.2\">\n<Document>\n<name>%s</name>\n<Style id=\"style1\">\n" \
	                    "\t<LineStyle>\n\t\t<color>40000000</color>\n\t\t<width>3</width>\n\t</LineStyle>\n\t<PolyStyle>\n\t\t<color>ff1c6d84</color>\n\t\t<fill>1</fill>\n" \
		            "\t\t<outline>1</outline>\n\t</PolyStyle>\n</Style>\n", str_name);

              flag_name = 0;
              continue;
            }
          }

          if(strncmp(line, "\t\t<Si", 5) == 0)
          {
            pch = strchr(line, '>');
            valor = atof(line+(pch-line+1))/1000000;

            fprintf(fp_o, "\n<Placemark>\n<name>%f</name>\n<description></description>\n<styleUrl>#style1</styleUrl>\n<Polygon>\n\t<outerBoundaryIs>\n\t\t<LinearRing>\n\t\t\t" \
		          "<tessellate>1</tessellate>\n\t\t\t<coordinates>\n", valor);

            ++flag_coord;
            continue;
          }

          if(flag_coord == 3)
          {
            pch = strstr(line, "coordinates");
            sscanf(pch+12, "%[^<]<", str_coord);

            fprintf(fp_o, "%s\n\t\t\t</coordinates>\n\t\t</LinearRing>\n\t</outerBoundaryIs>\n</Polygon>\n</Placemark>\n", str_coord);

	    ++count;
            flag_coord = 0;
          }
        }

        fprintf(fp_o, "\n</Document>\n</kml>");
	printf("poligonos [%d]\n", count);

        fclose(fp_i);
        fclose(fp_o);
      }
    }

    closedir(dp);
  }

  printf("Termino del proceso\n");

  return 0;
}
