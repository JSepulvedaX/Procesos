import sys
from qgis.core import *
from PyQt4.QtGui import *
app = QApplication([], False)
QgsApplication.setPrefixPath("/usr", True)
QgsApplication.initQgis()

sys.path.append('/usr/share/qgis/python/plugins')
from processing.core.Processing import Processing
Processing.initialize()
from processing.tools import *

#layer = QgsVectorLayer('./salida/centroid/centroid.shp', 'test', 'ogr')
#print layer.isValid()
#print layer.wkbType()

#features = layer.getFeatures()
#for f in features:
    #geom = f.geometry()
    #print geom.asPoint().x()
    #print "Area:", geom.area()
    #print "Perimeter:", geom.length()

#if layer.wkbType()==QGis.WKBPoint:
    #print 'Layer is a point layer'

#if layer.wkbType()==QGis.WKBLineString:
    #print 'Layer is a line layer'

#if layer.wkbType()==QGis.WKBPolygon:
    #print 'Layer is a polygon layer'

#if layer.wkbType()==QGis.WKBMultiPolygon:
    #print 'Layer is a multi-polygon layer'

#if layer.wkbType()==100:
    #print 'Layer is a data-only layer'

general.runalg('qgis:convexhull', './entrada/predio.kml', 'test', 0, './salida/convexhull/convexhull.shp')
general.runalg('qgis:polygoncentroids', './entrada/predio.kml', './salida/centroid/centroid.shp')

layer = QgsVectorLayer('./salida/centroid/centroid.shp', 'test', 'ogr')
#print layer.isValid()
#print layer.wkbType()

x = 0
y = 0
features = layer.getFeatures()
for f in features:
    geom = f.geometry()
    x = geom.asPoint().x()
    y = geom.asPoint().y()
    break

general.runalg('saga:transformshapes', './salida/convexhull/convexhull.shp', 0, 0, 0, 1.3, 1.3, x, y, './salida/final/final.shp')
#general.alglist()

#QgsApplication.exitQgis()
#QApplication.exit()

print 'Termino'
