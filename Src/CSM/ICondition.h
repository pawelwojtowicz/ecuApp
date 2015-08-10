#ifndef CSM_ICONDITION_H
#define CSM_ICONDITION_H

namespace CSM
{
class ICondition
{
public:
	ICondition() {};
	virtual ~ICondition() {};
	
	virtual bool Evaluate() const = 0;
	
private:
	ICondition(const ICondition&);
	ICondition& operator=(const ICondition&);
};
}
#endif
