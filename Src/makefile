all: controller exampleApp cgiprocessor joystick tts

libXMLParser:
	$(MAKE) -C XMLParser

libUCL:
	$(MAKE) -C UCL

libRuntime:
	$(MAKE) -C Runtime
	
libJSON:
	$(MAKE) -C JSONLib
	
libJoystickInterface:
	$(MAKE) -C JoystickInterface

libControllerInterface:
	$(MAKE) -C ControllerInterface
	
libTTSInterface:
	$(MAKE)	-C TTSInterface

libConfiguration.so: libXMLParser libUCL
	$(MAKE) -C Configuration

libLogger.so:
	$(MAKE) -C Logger

controller:	libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C Controller

exampleApp:	libControllerInterface libTTSInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C Example

cgiprocessor: libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL libJSON
	$(MAKE) -C CGIProcessor
	
joystick: libControllerInterface libJoystickInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE)	-C Joystick
	
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
	$(MAKE)	-C Joystick
	$(MAKE) -c TTS
	rm -rf ../Bin

	
