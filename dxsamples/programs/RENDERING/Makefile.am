## Process this file with automake to produce Makefile.in

LINKLIST = \
         FatLines.cfg\
         FatLines.net\
         Isolate.cfg\
         Isolate.net\
         SharedCamera.cfg\
         SharedCamera.net\
         TextureMapOpenGL.cfg\
         TextureMapOpenGL.net\
         UsingClipPlane.cfg\
         UsingClipPlane.net\
         UsingLights.cfg\
         UsingLights.net\
         LightingColorSelector.cfg\
         LightingColorSelector.net\
         UsingShade.cfg\
         UsingShade.net\
         VolumeRendering.cfg\
         VolumeRendering.net\
         VolumeRenderingSimple.cfg\
         VolumeRenderingSimple.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/RENDERING
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/RENDERING ; \
	done
