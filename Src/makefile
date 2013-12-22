all: controller exampleApp

libXMLParser:
	$(MAKE) -C XMLParser

libUCL:
	$(MAKE) -C UCL

libRuntime:
	$(MAKE) -C Runtime

libControllerInterface:
	$(MAKE) -C ControllerInterface

libConfiguration.so: libXMLParser
	$(MAKE) -C Configuration

libLogger.so:
	$(MAKE) -C Logger

controller:	libControllerInterface libRuntime libConfiguration.so libLogger.so 
	$(MAKE) -C Controller

exampleApp:	libControllerInterface libRuntime libConfiguration.so libLogger.so
	$(MAKE) -C Example
