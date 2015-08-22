#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <UCL/SystemEnvironment.h>
#include <CSM/CArgoConfigurator.h>
#include <CSM/CActionFactory.h>
#include <CSM/CGenericAction.h>
#include <CSM/CGenericCondition.h>
#include <CSM/CStateMachine.h>
#include "ITestInterface.h"

using ::testing::Return;
using ::testing::Sequence;

void InitializeSMActionFactory( CSM::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
{
	actionFactory.AddAction("OperationA", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationA ));
	actionFactory.AddAction("OperationB", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationB ));
	actionFactory.AddAction("OperationC", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationC ));
	actionFactory.AddAction("OperationD", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationD ));
	actionFactory.AddAction("OperationE", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationE ));
	actionFactory.AddAction("OperationF", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationF ));
	actionFactory.AddAction("OperationG", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationG ));
	actionFactory.AddAction("OperationH", new CSM::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationH ));
	
	actionFactory.AddCondition( "Condition1", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition1));
	actionFactory.AddCondition( "Condition2", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition2));
	actionFactory.AddCondition( "Condition3", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition3));
	actionFactory.AddCondition( "Condition4", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition4));
	actionFactory.AddCondition( "Condition5", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition5));
	actionFactory.AddCondition( "Condition6", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition6));
	actionFactory.AddCondition( "Condition7", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition7));
	actionFactory.AddCondition( "Condition8", new CSM::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition8));	
}


TEST( CStateMachine, BasicTest_1)
{
	// action/condition mocks
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("SimpleActions");
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	CSM::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, OperationC());
	EXPECT_CALL(	operationsMock, OperationB());
	EXPECT_CALL(	operationsMock, OperationF());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
	
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationE());
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO_BACK"));

}

TEST( CStateMachine, Conditions_variant_1)
{
	// action/condition mocks
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("ConditionalScenario");
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	CSM::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
}

TEST( CStateMachine, Conditions_variant_2)
{
	// action/condition mocks
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("ConditionalScenario");
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	CSM::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition2()).WillOnce(Return(true));

	EXPECT_CALL(	operationsMock, OperationB());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
}


TEST( CStateMachine, DetailedActionBehaviour)
{
	// action/condition mocks
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("DetailedActionScenario");
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	CSM::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationC()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationD()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationE()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationF()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationG()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));	
}

TEST( CStateMachine, DetailedActionSpecialCase)
{
	// action/condition mocks
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("DetailedActionScenario");
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	CSM::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationC()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO_WITHIN_SUPERPARENT"));	
}
