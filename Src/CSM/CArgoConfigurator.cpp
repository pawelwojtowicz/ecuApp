#include "CArgoConfigurator.h"
#include "ICSMBuilder.h"
#include <XMLParser/xmlParser.h>

namespace CSM
{

static const char s_constXMI[] 							= {"XMI"};
static const char s_constXMI_Content[] 			= {"XMI.content"};
static const char s_constUML_Model[] 				= {"UML:Model"};
static const char s_constUML_OwnedElement[] = {"UML:Namespace.ownedElement"};
static const char s_constUML_StateMachine[]	= {"UML:StateMachine"};
static const char s_constUML_TopState[]			= {"UML:StateMachine.top"};

CArgoConfigurator::CArgoConfigurator()
{
}

CArgoConfigurator::~CArgoConfigurator()
{
}
	
bool CArgoConfigurator::InitializeStateMachine(	const std::string& stateMachineFileName ,
																								ICSMBuilder* pBuilder )
{
	if ( 0 == pBuilder )
	{
		return false;
	}
	
	if ( stateMachineFileName.empty() )
	{
		return false;
	}
	
	XMLNode xMainNode=XMLNode::openFileHelper(stateMachineFileName.c_str(),s_constXMI);
	
	return true;
}
														
}

