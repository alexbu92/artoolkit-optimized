This is an optimized version of ARToolkit v5.3.3.

The main optimization is the introduction of a downsampling algorithm to speed up marker recognition on high resolution images. The downsampled image is only used for marker reco and the results are then tracked on the original full-res image.

Markers are also now groupable by ID. For example, the markers that are used to delimit a certain area, say a table, can by grouped together and identifiable as a single entity.

Marker recognition persistence has been implemented. If a marker gets temporarily obscured, ARToolkit will continue to pretend to recognize it at its last known position for MAX_VALID_FRAMES defined in ARMarkerSquare.h.

OpenCV2 has also been integrated and is used for a more efficient convertion of frame color space from YUV420 to RGBA.

A high resolution profiling log has been integrated and is enablable by simply setting the DO_PROFILING flag in ARContoller.h
