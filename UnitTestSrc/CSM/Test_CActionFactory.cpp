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
}

TEST( CActionFactory, Basics)
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
