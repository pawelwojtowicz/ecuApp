#ifndef CSM_IACTION_H
#define CSM_IACTION_H

namespace CSM
{
class IAction
{
public:
	IAction() {};
	virtual ~IAction() {};
	
	virtual void Execute() = 0;
	
private:
	IAction(const IAction&);
	IAction& operator=(const IAction&);
};
}
#endif
