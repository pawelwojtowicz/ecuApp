#ifndef TTS_ITTSERVICES_H
#define TTS_ITTSERVICES_H
namespace TTS
{
class ITTSServices
{
public:
	ITTSServices() {};
	virtual ~ITTSServices() {};
	
	virtual void Say(const std::string& phrase) = 0;
private:
	ITTSServices(const ITTSServices&);
	ITTSServices& operator=(const ITTSServices&);
};
}
#endif

