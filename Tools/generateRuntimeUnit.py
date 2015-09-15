import sys
import os

moduleName = 'defaultName'

if len(sys.argv) == 1:
	print ( 'Please enter module name' )
	moduleName = input()
elif len(sys.argv) == 2:
	moduleName = sys.argv[1]
	print ( 'Creating module ' + moduleName )

moduleDirName = '../Src/'+moduleName
moduleQueueName = moduleName+'Q'
moduleClassName = 'C'+moduleName
moduleClassHeaderFilename = moduleDirName+'/'+moduleClassName+'.h'
moduleClassImplFilename = moduleDirName+'/'+moduleClassName+'.cpp'
moduleBinaryName = moduleName.lower()
moduleMakefileFilename = moduleDirName+'/makefile'
moduleHeaderGuardDefine = ( moduleName + '_' + moduleClassName + '_h' ).upper()

#create the directory for the module
os.makedirs(moduleDirName)

#create the header file of the module
with open(moduleClassHeaderFilename,"w") as f:
	f.write('#ifndef '+ moduleHeaderGuardDefine +'\n' )
	f.write('#define '+ moduleHeaderGuardDefine +'\n'  )
	f.write('\n#include <Runtime/CRuntimeUnit.h>\n'  )
	f.write('namespace '+ moduleName  +'\n' )
	f.write('{' +'\n' )
	f.write('class '+ moduleClassName +' : public Runtime::CRuntimeUnit\n' )
	f.write('{' +'\n' )
	f.write('public:' +'\n' )
	f.write('	'+ moduleClassName+'();' +'\n' )
	f.write('	virtual ~'+ moduleClassName+'();' +'\n\n' )
	f.write('	virtual void Initialize();\n')
	f.write('private:' +'\n' )
	f.write('	'+ moduleClassName + '(const ' + moduleClassName +'&);' +'\n' )
	f.write('	'+ moduleClassName + '& operator=(const ' + moduleClassName +'&);' +'\n' )
	f.write('};\n' )
	f.write('}\n' )
	f.write('#endif //'+moduleHeaderGuardDefine +'\n' )

#create the implementation file for the module
with open(moduleClassImplFilename,"w") as f:
	f.write('#include "'+ moduleClassHeaderFilename +'"\n\n' )
	f.write('namespace '+ moduleName  +'\n' )
	f.write('{' +'\n' )
	f.write( moduleClassName +'::'+moduleClassName+'()\n')
	f.write(': Runtime::CRuntimeUnit("' + moduleName +'", "'+moduleQueueName+'")\n' )
	f.write('{' +'\n' )
	f.write('}' +'\n\n' )
	f.write( moduleClassName +'::~'+moduleClassName+'()\n')
	f.write('{' +'\n' )
	f.write('}' +'\n\n' )
	f.write( 'void '+moduleClassName +'::Initialize()\n')
	f.write('{' +'\n' )
	f.write('	// important - initialize the messenger\n')
	f.write('	CRuntimeUnit::Initialize();\n\n')
	f.write('	// important - initialize the timer manager\n')
	f.write('	InitializeTimerManager();\n\n')
	f.write('	SetBusy();\n\n\n')
	f.write('	InitDone(true);\n')
	f.write('}\n\n' )
	f.write('}\n' )

#create the makefile of the module
with open(moduleMakefileFilename,"w") as f:
	f.write('OUTPUT= '+ moduleBinaryName +'\n' )
	f.write('OBJ= '+ moduleClassName+'.o\n\n' )
	f.write('include ../../DevEnv/executableSettings\n\n' )
	f.write('LFLAGS+= -lControllerInterface -lRuntime -lUCL -lLogger\n\n' )
	f.write( moduleClassName+'.o:	'+moduleClassName+'.cpp '+moduleClassName+'.h' )
