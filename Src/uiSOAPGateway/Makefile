include ../../DevEnv/commonSettings

DATASERVICE_GENSRC=gSOAP_DataService
OUTPUT= uiSOAPGateway
OBJ= gSOAP_DS_C.o gSOAP_DS_DataServiceBindingService.o CUISOAPGateway.o CDataServiceSOAPStub.o stdsoap2.o

OBJ_DIR=$(INTERMEDIATE_PATH)/$(OUTPUT)
INSTALL_PATH:=$(TARGET_PATH)/usr/bin
LINKER_INPUT= $(addprefix $(OBJ_DIR)/, $(OBJ))
LFLAGS+= -lConfiguration -lControllerInterface -lRuntime -lUCL -lLogger -lrt

default: DirStructure $(OBJ)
	$(CC) $(LINKER_INPUT) -o $(INSTALL_PATH)/$(OUTPUT) $(LFLAGS)

gSOAP_DS_C.o: $(DATASERVICE_GENSRC)/gSOAP_DS_C.cpp
	$(CC) $(CFLAGS) $(DATASERVICE_GENSRC)/gSOAP_DS_C.cpp -o$(OBJ_DIR)/gSOAP_DS_C.o

gSOAP_DS_DataServiceBindingService.o: $(DATASERVICE_GENSRC)/gSOAP_DS_DataServiceBindingService.cpp $(DATASERVICE_GENSRC)/gSOAP_DS_DataServiceBindingService.h
	$(CC) $(CFLAGS) -DWITH_PURE_VIRTUAL $(DATASERVICE_GENSRC)/gSOAP_DS_DataServiceBindingService.cpp -o$(OBJ_DIR)/gSOAP_DS_DataServiceBindingService.o

stdsoap2.o: stdsoap2.cpp stdsoap2.h
	$(CC) $(CFLAGS) stdsoap2.cpp -o$(OBJ_DIR)/stdsoap2.o

CUISOAPGateway.o: CUISOAPGateway.cpp CUISOAPGateway.h
	$(CC) $(CFLAGS) CUISOAPGateway.cpp -o$(OBJ_DIR)/CUISOAPGateway.o

CDataServiceSOAPStub.o: CDataServiceSOAPStub.cpp CDataServiceSOAPStub.h
	$(CC) $(CFLAGS) CDataServiceSOAPStub.cpp -o$(OBJ_DIR)/CDataServiceSOAPStub.o



DirStructure:
	-mkdir -p $(BIN_PATH)
	-mkdir -p $(INTERMEDIATE_PATH)
	-mkdir -p $(OBJ_DIR)
	-mkdir -p $(TARGET_PATH)
	-mkdir -p $(INSTALL_PATH)
	-mkdir -p $(VAR_RUN)	

clean:
	-rm -f $(OBJ_DIR)/*.o
	-rm -f $(INSTALL_PATH)/$(OUTPUT)
