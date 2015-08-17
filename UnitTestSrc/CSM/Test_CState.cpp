#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CState.h>
#include <CSM/CTransition.h>
#include <CSM/CActionFactory.h>
#include <CSM/CGenericAction.h>
#include <CSM/CGenericCondition.h>
#include "ITestInterface.h"

void InitializeFactory( CSM::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
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


using ::testing::Sequence;
using ::testing::Return;

TEST( CState, SingleMatch_ConditionOK )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	CSM::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , 0 ) );
	
	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , 0 ) );

	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , 0 ) );

	stateUnderTest.AddTransition( 3 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , 0 ) );
	
	EXPECT_CALL(	operationsMock, Condition1() ).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA());

	CSM::CTransition* pTransition = stateUnderTest.GetTransition(1);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, SingleMatch_ConditionNOK )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	CSM::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , 0 ) );
	
	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , 0 ) );

	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , 0 ) );

	stateUnderTest.AddTransition( 3 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , 0 ) );
	
	EXPECT_CALL(	operationsMock, Condition1() ).WillOnce(Return(false));

	CSM::CTransition* pTransition = stateUnderTest.GetTransition(1);
	
	EXPECT_FALSE( 0 != pTransition );
}

TEST( CState, MultipleMatch_ConditionOK )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	CSM::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , 0 ) );
	
	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , 0 ) );

	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , 0 ) );

	stateUnderTest.AddTransition( 3 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , 0 ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationB());

	CSM::CTransition* pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, MultipleMatch_ConditionNOK_OK )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	CSM::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , 0 ) );
	
	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , 0 ) );

	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , 0 ) );

	stateUnderTest.AddTransition( 3 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , 0 ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition3() ).WillOnce(Return(true));

	EXPECT_CALL(	operationsMock, OperationC());

	CSM::CTransition* pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, MultipleMatch_ConditionNOK_NOK )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	CSM::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , 0 ) );
	
	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , 0 ) );

	stateUnderTest.AddTransition( 2 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , 0 ) );

	stateUnderTest.AddTransition( 3 , new CSM::CTransition( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , 0 ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition3() ).WillOnce(Return(false));

	CSM::CTransition* pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_FALSE( 0 != pTransition );
}

