from os import walk
from qgis.analysis import QgsRasterCalculator, QgsRasterCalculatorEntry
from osgeo import gdal
import sys, os
from qgis.core import *
from PyQt4.QtGui import *
app = QApplication([], False)
QgsApplication.setPrefixPath("/usr", True)
QgsApplication.initQgis()

sys.path.append('/usr/share/qgis/python/plugins')
from processing.core.Processing import Processing
Processing.initialize()
from processing.tools import *

# Arreglo que contiene el nombre de los archivos de la carpeta de entrada
files_array = []

print os.getcwd() + '/entrada'

# Ingresa los nombres de los archivos al arreglo
for files in next(walk(os.getcwd() + '/entrada'))[2]:
    files_array.append(files)

# Cargar imagen tiff 1 por 1
for i in range(0,len(files_array)):
    # Establezco variables a utilizar
    entries = []
    Image = QgsRasterLayer(os.getcwd() + '/entrada/' + files_array[i], "test")
    image = QgsRasterCalculatorEntry()
    image.ref = 'image@1'
    image.raster = Image
    image.bandNumber = 1
    entries.append(image)

    # Dejar todos los pixeles en 1
    calc = QgsRasterCalculator('(image@1 != 0)*1', os.getcwd() + '/salida/' + files_array[i], 'GTiff', Image.extent(), Image.width(), Image.height(), entries )
    calc.processCalculation()

    # Cierro la conexion con QGis
    QgsMapLayerRegistry.instance().removeMapLayer(Image.id())
    del Image

    # Se elimina el archivo auxiliar generado
    if os.path.exists(os.getcwd() + '/entrada/' + files_array[i] + '.aux.xml'):
        os.remove(os.getcwd() + '/entrada/' + files_array[i] + '.aux.xml')

    # Poligoniza la imagen TIF
    general.runalg('gdalogr:polygonize', os.getcwd() + '/salida/' + files_array[i], 'Value2', os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp')

    # Separa los poligonos
    general.runalg('qgis:splitvectorlayer', os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp', 'Value2', os.getcwd() + '/salida')

    # Elimina todos los archivos sobrantes
    """ if os.path.exists(os.getcwd() + '/salida/' + files_array[i]):
        os.remove(os.getcwd() + '/salida/' + files_array[i])
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shx'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shx')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.prj'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.prj')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.qpj'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.qpj')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.dbf'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.dbf')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.shp'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.shp')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.shx'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.shx')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.prj'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.prj')
    if os.path.exists(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.dbf'):
        os.remove(os.getcwd() + '/salida/' + (files_array[i])[0:len(files_array[i])-4] + '.shp_Value2_0.dbf') """

print "Termino"