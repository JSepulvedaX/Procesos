saga_cmd io_gdal 0 -TRANSFORM 1 -RESAMPLING 3 -GRIDS "/tmp/processinge80a8e8d7cd94b6189162dbedd6b1562/ee3db7881665474a914ed3e7f8be6b7d/LC08L1TP233085201505202017040801T1LSTtif.sgrd" -FILES "./entrada/tiff/LC08_L1TP_233085_20150520_20170408_01_T1_LST.tif"
saga_cmd shapes_grid "Clip Grid with Polygon"  -INPUT "/tmp/processinge80a8e8d7cd94b6189162dbedd6b1562/ee3db7881665474a914ed3e7f8be6b7d/LC08L1TP233085201505202017040801T1LSTtif.sgrd" -POLYGONS "./entrada/shp/Shape_19n.shp" -OUTPUT "/tmp/processinge80a8e8d7cd94b6189162dbedd6b1562/24d291508ae34620b23b84eaf3937757/OUTPUT.sdat"
exit