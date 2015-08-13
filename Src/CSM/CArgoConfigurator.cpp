#include "CArgoConfigurator.h"
#include "ICSMBuilder.h"
#include <XMLParser/xmlParser.h>
#include <stdio.h>
namespace CSM
{

static const char s_constXMI[] 							= {"XMI"};
static const char s_constXMI_Content[] 			= {"XMI.content"};
static const char s_constUML_Model[] 				= {"UML:Model"};
static const char s_constUML_OwnedElement[] = {"UML:Namespace.ownedElement"};
static const char s_constUML_StateMachine[]	= {"UML:StateMachine"};
static const char s_constUML_TopState[]			= {"UML:StateMachine.top"};

static const char s_constUML_Transitions[]		= {"UML:StateMachine.transitions"};
static const char s_constUML_Transition[]			= {"UML:Transition"};
static const char s_constUML_TransitionTrigger[] 	= {"UML:Transition.trigger"};
static const char s_constUML_TransitionAction[]		= {"UML:Transition.effect"};
static const char s_constUML_TransitionSource[]		= {"UML:Transition.source"};
static const char s_constUML_TransitionTarget[]	 	= {"UML:Transition.target"};
static const char s_constUML_TransitionGuard[]		= {"UML:Transition.guard"};
static const char s_constUML_Guard[]							= {"UML:Guard"};



static const char s_constUML_CompositeState[]	= {"UML:CompositeState"};
static const char s_constUML_SimpleState[]	= {"UML:SimpleState"};
static const char s_constUML_StateVertex[]	= {"UML:CompositeState.subvertex"};

static const char s_constUML_SignalEvent[]	= {"UML:SignalEvent"};

static const char s_constUML_name[]					= {"name"};
static const char s_constUML_xmiId[]			  = {"xmi.id"};
static const char s_constUML_xmiIdRef[]			= {"xmi.idref"};

static const char s_constUML_CallAction[]		= {"UML:CallAction"};
static const char s_constUML_EntryAction[]	= {"UML:State.entry"};
static const char s_constUML_LeafAction[]		= {"UML:State.doActivity"};
static const char s_constUML_ExitAction[]		= {"UML:State.exit"};



CArgoConfigurator::CArgoConfigurator()
{
}

//------------------------------------------------------------------------------------------

CArgoConfigurator::~CArgoConfigurator()
{
}

//------------------------------------------------------------------------------------------
	
bool CArgoConfigurator::InitializeStateMachine(	const std::string& stateMachineFileName , const std::string& stateMachineName, ICSMBuilder* pBuilder )
{
	if ( 0 == pBuilder )
	{
		return false;
	}
	
	m_pCSMBuilder = pBuilder;
	
	if ( stateMachineFileName.empty() )
	{
		return false;
	}
	
	XMLNode xMainNode=XMLNode::openFileHelper(stateMachineFileName.c_str(),s_constXMI);
	
	if ( 1 !=  xMainNode.nChildNode(s_constXMI_Content) )
	{
		return false;
	}
	
	const XMLNode& contentNode = xMainNode.getChildNode( s_constXMI_Content , 0 );
	
	if (1 !=  contentNode.nChildNode(s_constUML_Model) )
	{
		return false;
	}
	
	const XMLNode& modelNode = contentNode.getChildNode( s_constUML_Model , 0 );
	
	if (1 !=  modelNode.nChildNode(s_constUML_OwnedElement) )
	{
		return false;
	}

	const XMLNode& ownedElementNode = modelNode.getChildNode( s_constUML_OwnedElement , 0 );
	
	{
		const UInt32 numberOfSignalEvents(ownedElementNode.nChildNode(s_constUML_SignalEvent));
		for ( UInt32 i = 0 ; i < numberOfSignalEvents; ++i )
		{
			const XMLNode& signalEventNode = ownedElementNode.getChildNode( s_constUML_SignalEvent , i );
			
			m_IdToNameMap.insert( tIdToNameMap::value_type( signalEventNode.getAttribute(s_constUML_xmiId) , 																												signalEventNode.getAttribute(s_constUML_name) ) );
			const std::string& name( signalEventNode.getAttribute(s_constUML_name));
			const std::string& id(signalEventNode.getAttribute(s_constUML_xmiId));			
		}
	}
	
	const UInt32 numberOfStateMachines( ownedElementNode.nChildNode(s_constUML_StateMachine) );
	
	for ( UInt32 soIndex = 0 ; soIndex < numberOfStateMachines ; ++soIndex )
	{
		const XMLNode& stateMachineNode = ownedElementNode.getChildNode( s_constUML_StateMachine , soIndex );
		
		const std::string smName = stateMachineNode.getAttribute(s_constUML_name);
		
		if ( smName == stateMachineName )
		{
			if ( 1 == stateMachineNode.nChildNode(s_constUML_TopState) )
			{
				const XMLNode& stateMachineTopNode = stateMachineNode.getChildNode( s_constUML_TopState , 0 );
				
				if (1 == stateMachineTopNode.nChildNode(s_constUML_CompositeState))
				{
					std::string noName("");
					ReadCompositeStateConfiguration(	noName, 
																						stateMachineTopNode.getChildNode( s_constUML_CompositeState, 0 ));
				
				}
			}
			
			if ( 1 == stateMachineNode.nChildNode(s_constUML_Transitions) )
			{
				const XMLNode& transitionsNode = stateMachineNode.getChildNode( s_constUML_Transitions , 0 );
				
				ConfigureTransitions( transitionsNode );
			}
			
			return true;
		}
	}
	
	return false;
}

//------------------------------------------------------------------------------------------

void CArgoConfigurator::ReadCompositeStateConfiguration ( const std::string& parentName, const XMLNode& stateConfigNode )
{
	sState stateStructure;
	stateStructure.ParentName = parentName;
	stateStructure.StateName = stateConfigNode.getAttribute(s_constUML_name);
	std::string stateId(stateConfigNode.getAttribute(s_constUML_xmiId));
	
	if ( 1 == stateConfigNode.nChildNode( s_constUML_EntryAction ) )
	{
		stateStructure.EnterActionName = ReadActionConfiguration( stateConfigNode.getChildNode( s_constUML_EntryAction , 0 ) );
	}
	
	if ( 1 == stateConfigNode.nChildNode( s_constUML_LeafAction ) )
	{
		stateStructure.LeafActionName = ReadActionConfiguration( stateConfigNode.getChildNode( s_constUML_LeafAction , 0 ) );
	}

	if ( 1 == stateConfigNode.nChildNode( s_constUML_ExitAction ) )
	{
		stateStructure.ExitActionName = ReadActionConfiguration( stateConfigNode.getChildNode( s_constUML_ExitAction , 0 ) );
	}
	
	
	if ( 1 == stateConfigNode.nChildNode( s_constUML_StateVertex ) )
	{
		const XMLNode& stateVertex = stateConfigNode.getChildNode( s_constUML_StateVertex, 0 );
		
		UInt32 internalSimpleStateCount( stateVertex.nChildNode(s_constUML_SimpleState) );
		for( UInt32 i = 0 ; i < internalSimpleStateCount ; ++i)
		{
			ReadCompositeStateConfiguration( 	stateStructure.StateName , 
																				stateVertex.getChildNode( s_constUML_SimpleState , 
																				i ));
		}
		
		UInt32 internalCompositeStateCount( stateVertex.nChildNode(s_constUML_CompositeState) );
		for( UInt32 i = 0 ; i < internalCompositeStateCount ; ++i)
		{
			ReadCompositeStateConfiguration( 	stateStructure.StateName , 
																				stateVertex.getChildNode( s_constUML_CompositeState , 
																				i ));
		}
	}

	m_statesMap.insert( tIdToState::value_type(stateId, stateStructure));
	
	m_pCSMBuilder->AddState( stateStructure.ParentName,
													 stateStructure.StateName,
													 stateStructure.EnterActionName,
													 stateStructure.LeafActionName,
													 stateStructure.ExitActionName);																						
}

//------------------------------------------------------------------------------------------

const std::string CArgoConfigurator::ReadActionConfiguration( const XMLNode& actionConfiguration )
{
	std::string actionName("");
	
	if ( 1 == actionConfiguration.nChildNode(s_constUML_CallAction) )
	{
		actionName = actionConfiguration.getChildNode( s_constUML_CallAction , 0 ).getAttribute(s_constUML_name);
	}
	
	return actionName;
}

//------------------------------------------------------------------------------------------

void CArgoConfigurator::ConfigureTransitions( const XMLNode& transitions)
{
	UInt32 noOfTransitions( transitions.nChildNode(s_constUML_Transition) );
		
	for(UInt32 i = 0 ; i < noOfTransitions ; ++i )
	{
		std::string triggerName;
		std::string sourceName;
		std::string target;
		std::string guardName;
		std::string actionName;

		const XMLNode& transitionNode = transitions.getChildNode(s_constUML_Transition , i );
		if ( 1 == transitionNode.nChildNode(s_constUML_TransitionTrigger) )
		{
			const XMLNode& triggerNode = transitionNode.getChildNode(s_constUML_TransitionTrigger);
			
			if ( 1== triggerNode.nChildNode(s_constUML_SignalEvent) )
			{
				std::string triggerId =
				triggerNode.getChildNode(s_constUML_SignalEvent).getAttribute(s_constUML_xmiIdRef);
				tIdToNameMapConstIterator cIter = m_IdToNameMap.find(triggerId);
				if (m_IdToNameMap.end() != cIter )
				{
					triggerName = cIter->second;
				}
			}
		}	
		
		if ( 1 == transitionNode.nChildNode(s_constUML_TransitionSource) )
		{
			const XMLNode& sourceNode = transitionNode.getChildNode(s_constUML_TransitionSource);
			if ( 1== sourceNode.nChildNode(s_constUML_CompositeState) )
			{
				std::string stateId =
				sourceNode.getChildNode(s_constUML_CompositeState).getAttribute(s_constUML_xmiIdRef);
				tIdToStateConstIterator cIter = m_statesMap.find(stateId);
				
				if (m_statesMap.end() != cIter )
				{
					sourceName = cIter->second.StateName;
				}
			} 
			else if ( 1== sourceNode.nChildNode(s_constUML_SimpleState) )
			{
				std::string stateId =
				sourceNode.getChildNode(s_constUML_SimpleState).getAttribute(s_constUML_xmiIdRef);
				tIdToStateConstIterator cIter = m_statesMap.find(stateId);
				
				if (m_statesMap.end() != cIter )
				{
					sourceName = cIter->second.StateName;
				}
			} 

		}
		
		if ( 1 == transitionNode.nChildNode(s_constUML_TransitionTarget) )
		{
			const XMLNode& sourceNode = transitionNode.getChildNode(s_constUML_TransitionTarget);
			if ( 1== sourceNode.nChildNode(s_constUML_CompositeState) )
			{
				std::string stateId =
				sourceNode.getChildNode(s_constUML_CompositeState).getAttribute(s_constUML_xmiIdRef);
				tIdToStateConstIterator cIter = m_statesMap.find(stateId);
				
				if (m_statesMap.end() != cIter )
				{
					target = cIter->second.StateName;
				}
			}
			else if ( 1== sourceNode.nChildNode(s_constUML_SimpleState) )
			{
				std::string stateId =
				sourceNode.getChildNode(s_constUML_SimpleState).getAttribute(s_constUML_xmiIdRef);
				tIdToStateConstIterator cIter = m_statesMap.find(stateId);
				
				if (m_statesMap.end() != cIter )
				{
					target = cIter->second.StateName;
				}
			}

		}
		
		if ( 1 == transitionNode.nChildNode(s_constUML_TransitionGuard) )
		{
			const XMLNode& guardNode = transitionNode.getChildNode(s_constUML_TransitionGuard);
			if ( 1== guardNode.nChildNode(s_constUML_Guard) )
			{
				guardName =
				guardNode.getChildNode(s_constUML_Guard).getAttribute(s_constUML_name);
			}
		}			

		if ( 1 == transitionNode.nChildNode(s_constUML_TransitionAction) )
		{
			const XMLNode& transitionAction = transitionNode.getChildNode(s_constUML_TransitionAction);
			if ( 1== transitionAction.nChildNode(s_constUML_CallAction) )
			{
				actionName =
				transitionAction.getChildNode(s_constUML_CallAction).getAttribute(s_constUML_name);
			}
		}			

		m_pCSMBuilder->AddTransition(	triggerName, 
																	sourceName,
																	target,
																	guardName,
																	actionName);
	}
}

//------------------------------------------------------------------------------------------
													
}

