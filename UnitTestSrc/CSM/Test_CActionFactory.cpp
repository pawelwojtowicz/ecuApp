#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CActionFactory.h>
#include <CSM/CGenericAction.h>
#include <CSM/CGenericCondition.h>
#include "ITestInterface.h"

void InitializeActionFactory( CSM::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
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

TEST( CActionFactory, Actions_Found_NotFound )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );
	
	CSM::IAction* pAction = actionFactory.GetAction("OperationA");
	
	EXPECT_TRUE( 0 != pAction );

	pAction = actionFactory.GetAction("Dupa");
	
	EXPECT_TRUE( 0 == pAction );

	EXPECT_TRUE(true);
}

TEST( CActionFactory, Actions_ExecuteSequence )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );

	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationD()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);
	
	CSM::IAction* pAction = actionFactory.GetAction("OperationB");
	
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationD");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationH");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationA");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}
}

TEST( CActionFactory, Conditions_FoundNotFound )
{
	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );
	
	CSM::ICondition* pCondition = actionFactory.GetCondition( "Condition1" );
	
	EXPECT_TRUE( 0 != pCondition );
	
	pCondition = actionFactory.GetCondition( "Condition9" );

	EXPECT_TRUE( 0 == pCondition );


}

TEST( CActionFactory , Conditions_ExecutedInSequenceReturningRightValues)
{

	CSM::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );


	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, Condition8()).InSequence(executionSequence).WillOnce(Return(true));
	EXPECT_CALL(operationsMock, Condition4()).InSequence(executionSequence).WillOnce(Return(false));
	EXPECT_CALL(operationsMock, Condition2()).InSequence(executionSequence).WillOnce(Return(false));
	EXPECT_CALL(operationsMock, Condition7()).InSequence(executionSequence).WillOnce(Return(true));
	EXPECT_CALL(operationsMock, Condition8()).InSequence(executionSequence).WillOnce(Return(false));
	
	EXPECT_TRUE( actionFactory.GetCondition("Condition8")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition4")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition2")->Evaluate());
	EXPECT_TRUE( actionFactory.GetCondition("Condition7")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition8")->Evaluate());

}
