all: controller exampleApp cgiprocessor tts

libXMLParser:
	$(MAKE) -C XMLParser

libUCL:
	$(MAKE) -C UCL

libCSM:
	$(MAKE) -C CSM

libRuntime:
	$(MAKE) -C Runtime

libJSON:
	$(MAKE) -C JSONLib

libControllerInterface:
	$(MAKE) -C ControllerInterface

libTTSInterface:
	$(MAKE)	-C TTSInterface

libConfiguration.so: libXMLParser libUCL
	$(MAKE) -C Configuration

libLogger.so:
	$(MAKE) -C Logger

controller:	libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL libCSM
	$(MAKE) -C Controller

exampleApp:	libControllerInterface libTTSInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C Example

cgiprocessor: libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL libJSON
	$(MAKE) -C CGIProcessor

tts: libControllerInterface libTTSInterface libRuntime libUCL libLogger.so
	$(MAKE) -C TTS

cleanup:
	$(MAKE) -C XMLParser clean
	$(MAKE) -C UCL clean
	$(MAKE) -C Runtime clean
	$(MAKE) -C ControllerInterface clean
	$(MAKE) -C Configuration clean
	$(MAKE) -C Logger clean
	$(MAKE) -C Controller clean
	$(MAKE) -C Example clean
	$(MAKE) -C CGIProcessor clean
	$(MAKE) -c TTS
	rm -rf ../Bin
