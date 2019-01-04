#import re, math, os
#from PyQt4.QtCore import *
#from PyQt4.QtGui import *
#from qgis.utils import *
#from os import walk
#from qgis.gui import *
#from qgis.analysis import QgsRasterCalculator, QgsRasterCalculatorEntry
#from osgeo import gdal
#from osgeo.gdalconst import GDT_Float32
#import numpy as np
#import sys
#from qgis.core import *

import sys, re
from os import walk
from qgis.core import *
from PyQt4.QtGui import *

app = QApplication([], False)
QgsApplication.setPrefixPath("/usr", True)
QgsApplication.initQgis()

sys.path.append('/usr/share/qgis/python/plugins')
from processing.core.Processing import Processing
Processing.initialize()
from processing.tools import *

def corte_tiff():

    # Se establecen las expresiones regulares para los diferentes tipos de archivos
    shapere = re.compile("(.+).shp$")
    imagere = re.compile("(.+).tif$")
    images_array = []

    #Guardo el shape en la variable 'shape'
    for files in next(walk("./entrada/shp"))[2]:
        if shapere.match(files):
            shape = "./entrada/shp/" + files
    
    #Guardo las imagenes .tif en el arreglo 'images_array'
    for files in next(walk("./entrada/tiff"))[2]:
            if imagere.match(files):
                images_array.append(files)

    #Recorro el arreglo 'images_array' y se corta cada imagen con el shape guardandose en la carpeta 'salida'.
    for imagenes in range(0, len(images_array)):
        inputfile = "./entrada/tiff/" + images_array[imagenes] #imagen que se corta
        outputfile = "./salida/" + images_array[imagenes] #imagen cortada

        general.runalg("saga:clipgridwithpolygon",inputfile,shape,3,outputfile)

corte_tiff()
