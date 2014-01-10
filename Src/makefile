all: controller exampleApp cgiprocessor

libXMLParser:
	$(MAKE) -C XMLParser

libUCL:
	$(MAKE) -C UCL

libRuntime:
	$(MAKE) -C Runtime

libControllerInterface:
	$(MAKE) -C ControllerInterface

libConfiguration.so: libXMLParser libUCL
	$(MAKE) -C Configuration

libLogger.so:
	$(MAKE) -C Logger

controller:	libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C Controller

exampleApp:	libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C Example

cgiprocessor: libControllerInterface libRuntime libConfiguration.so libLogger.so libUCL
	$(MAKE) -C CGIProcessor

cleanup:
	$(MAKE) -C XMLParser clean
	$(MAKE) -C UCL clean
	$(MAKE) -C Runtime clean
	$(MAKE) -C CGIProcessor
	$(MAKE) -C ControllerInterface clean
	$(MAKE) -C Configuration clean
	$(MAKE) -C Logger clean
	$(MAKE) -C Controller clean
	$(MAKE) -C Example clean
	$(MAKE) -C CGIProcessor clean
	rm -rf ../Bin

	
