#ifndef CSM_ICONDITION_H
#define CSM_ICONDITION_H

namespace CSM
{
class IConditition
{
public:
	IConditition() {};
	virtual ~IConditition() {};
	
	virtual bool Evaluate() const = 0;
	
private:
	IConditition(const IConditition&);
	IConditition& operator=(const IConditition&);
};
}
#endif
